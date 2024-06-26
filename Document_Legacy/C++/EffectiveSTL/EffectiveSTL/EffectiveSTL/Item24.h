#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>

//map::operator[]나 map::insert는 효율 문제에 주의하여 선택하자

namespace Item24 {
	using namespace std;
	/*
		c++ 11의 move semantic이 도입되기 이전의 내용임을 감안합시다.
		C++ 11이후 map에 emplace/emplace_hint 기능이 추가되었습니다. insert와 달리 삽입시 임시객체를 생성하지 않습니다.
		c++ 17이후 insert_or_assign 기능이 추가되었습니다.

		책이 쓰인 이후로 map의 기능이 최적화 된 것 같습니다. 이번 항목의 내용이 전부 맞다고 보기 어렵습니다.
	*/

	class Widget {
	public:
		Widget()						{ std::cout << "default ctor" << std::endl; }
		Widget(double)					{ std::cout << "double ctor" << std::endl; }
		~Widget()						{ std::cout << "dtor" << std::endl; }

		Widget(const Widget& rhs)		{ std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept	{ std::cout << "move ctor" << std::endl; }
		//Widget(const Widget& rhs) = delete;
		//Widget(Widget&& rhs) noexcept = delete;

		Widget& operator=(double) {
			std::cout << "double operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept {
			std::cout << "move operator =" << std::endl;
			return *this;
		}
	};

	/*
		맵에 새로운 요소를 "추가"할 경우에는 operator[]보다 insert가 효율적으로 낫습니다.
		(현재는 전부 그렇다고 보기 어렵습니다.)
	*/
	inline void AddElement() {
		map<int, Widget> m;
		/*
			다음의 표현식
			m[k] = v;

			은 우선 해당 맵에 키 k가 들어 있는지 점검합니다. 
			그렇지 않다면 k와 v가 페어로 묶여서 맵에 새로 '추가'됩니다. 
			k가 맵에 들어 있는 경우에는 k와 매핑(연관)된 값(value)이 v로 갱신됩니다.

			만약에 컨테이너 안에 해당 키에 대응하는 pair값이 없다고 해봅시다.
			operator[]는 해당 map에 지정된 값 타입(value_type)의 기본 생성자를 사용하여 pair 객체를 새로 만들고, 이 객체의 참조자를 반환합니다. 
			결과적으로, 반환된 Widget 객체의 참조자를 통해 operator=연산자 함수가 호출되어 Widget 객체에 값이 대입됩니다.

			아래의 경우 operator[]를 호춯할 때 새로운 pair를 만드는 기본 생성자가 호출되고, 그 이후 double 값 1.50에 대한 대입연산자가 호출됩니다.
			기본 생성자 -> double 대입 연산자
			(copy elision이 적용되면서 값 추가 동작이 훨씬 최적화 된 것 같습니다.)
		*/
		cout << "============ operator[] =================" << endl;
		m[1] = 1.50;

		/*
			책에서는 insert를 활용하는 것이 함수 호출 비용을 크게 줄일 수 있다고 설명되어 있고 operator[]가 임시객체를 생성하는 것이 그 이유라고 설명합니다.
			
			현재 실행해보면 operator[]는 임시 객체를 따로 생성하지 않으며 오히려 insert호출이 임시객체를 생성합니다.

			아래의 경우 만약의 Widget안에 이동생성자가 구현되어 있으면
			double 생성자(임시객체) -> 이동 생성자 -> 소멸자(임시객체) 순으로 호출되며

			이동생성자가 구현되어 있지 않다면
			double 생성자(임시객체) -> 복사 생성자 -> 소멸자(임시객체) 순으로 호출됩니다.

			insert가 더 효율적이라고 보기 어렵습니다. 
		*/
		cout << "============ Insert =================" << endl;
		m.insert({ 2, 3.0 });

		
		//C++ 11이후 map에 emplace / emplace_hint 기능이 추가되었습니다.insert와 달리 삽입시 임시객체를 생성하지 않습니다.
		//double 생성자를 단 한번 호출합니다.
		cout << "============ emplace =================" << endl;
		m.emplace(make_pair( 3, 3.0 ));

		cout << "============ Function End =================" << endl;
	}

	/*
		반면에, 맵에 저장된 요소에 대한 "갱신"을 할 경우에는 insert보다 operator[]가 효율적으로나 미(美)적으로나 낫습니다.
	*/
	inline void UpdateElement() {
		map<int, int> m;
		m[1] = 10;
		m[2] = 10;

		// operator[]를 통해 1에 매핑된 값을 11로 갱신합니다.
		m[1] = 11;
		
		//insert를 통해 2에 매핑된 값을 11로 갱신합니다. 임시객체를 생성하는 비용을 지불해야 합니다.
		auto iter = m.insert(map<int, int>::value_type(2, 9));	
		iter.first->second = 11;
	}

	template <typename MapType, typename _Key, typename _Value>  
	decltype(auto) efficientAddOrUpdate(MapType& m, const _Key& k, const _Value& v)
	{
		// k의 위치 혹은 삽입 위치를 찾습니다. lower_bound 는 항목 45 참고
		auto lb = m.lower_bound(k);          

		//값을 갱신합니다. 
		//lower_bound는 두 가지 목적을 가지고 호출한 알고리즘이기 때문에 실제로 원하는 키 값을 찾았는지 체크하는 과정이 한번 더 필요합니다.(동등성 검사 수행)
		if (lb != m.end() &&                 
			!(m.key_comp()(k, lb->first))) { 
			lb->second = v;                  
			return lb;                       
		}                                    
		else {
			//lb가 가리키는 위치에 pair(k, v)를 삽입합니다. 
			//insert에서 미리 위치를 지정해준다면 로그 시간이 아닌 상수 시간에 원소 삽입이 가능합니다.
			
			//return m.insert(lb, {k, v});        

			//c++ 11이후 emplace_hint가 추가되었습니다. 좀더 효율적으로 원소 삽입이 가능합니다.
			return m.emplace_hint(lb, k, v);
		}                                       
	}

	inline void AddOrUpdate() {
		map<int, Widget> m;
		cout << "============ efficientAddOrUpdate =================" << endl;
		cout << "============ Add =================" << endl;

		efficientAddOrUpdate(m, 1, 0.5);

		cout << "============ Update =================" << endl;

		efficientAddOrUpdate(m, 1, 1.5);

		cout << "============ Function End =================" << endl;
	}

	inline void RunSample() {
		AddElement();
		UpdateElement();
		AddOrUpdate();
	}
}
