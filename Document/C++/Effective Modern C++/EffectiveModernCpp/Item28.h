#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//참조 축약 (reference collapsing) 을 숙지하라

namespace Item28 {
	/*
		참조 축약(collapse)은 

		템플릿 인스턴스화, 
		auto 타입 추론, 
		typedef와 별칭 선언의 지정 및 사용, 
		decltype의 지정 및 사용
		
		네 가지 문맥에서 일어난다.
	*/

	class Widget {
	public:
		static Widget Create() { return Widget(); }
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
	};

	template<typename T>
	decltype(auto) f(T&& val) {
		using RefToType1 = T & ;	//타입 별칭 선언에도 참조 축약 가능
		using RefToType2 = T && ;

		std::cout << typeid(T).name() << std::endl;
		return std::forward<T>(val);
	}

	inline void RunSample() {
		int x = 0;
		auto && rx = x;
		//auto& && rx2 = x;	//컴파일 오류, 참조에 대한 참조

		decltype(auto) r = f(x);	//T : int&, paramType : int& && -> int& (참조축약)
		decltype(auto) r1 = f(3);	//T : int,  paramType : int&&
		decltype(auto) r2 = f(rx);	//T : int&, paramType : int& && -> int& (참조축약)
		


		Widget w;
		auto && w1 = w;		//Widget&
		/*
			auto&& => Widget& && => Widget& (참조축약)
		*/

		auto && w2 = Widget::Create();	//Widget&&
		/*
			auto&& => Widget&& (참조 대 참조가 없다)
		*/
	}

	/*
		추가로 decltype 에서도 참조 축약이 발생한다. 
		컴파일러가 decltype에 관여하는 형식을 분석하는 도중에 참조에 대한 참조가 발생하면 참조 축약이 등장해 그것을 제거한다.
	*/

	/*
		참조는 두 종류(좌측값과 우측값)이므로, 참조에 대한 참조로 가능한 조합은 총 네 가지이다
		(좌측값에 대한 좌측값, 우측값에 대한 좌측값, 좌측값에 대한 우측값, 우측값에 대한 우측값). 
		참조에 대한 참조가 허용되는 문맥에서 참조에 대한 참조는 다음 규칙에 따라 하나의 참조로 축약된다(collapse).

		만일 두 참조 중 하나라도 좌측값 참조이면 결과는 좌측값 참조이다. 그렇지 않으면(즉, 둘 다 우측값 참조이면) 결과는 우측값 참조이다.
	*/

	/*
		다시 확인했을 때 보편 참조(universal reference)는 사실상 오른쪽 참조이다.

		1. 타입 추론에서 좌측값과 우측값이 구분된다. T 타입의 좌측값은 타입 T&로 추론되고, T 타입의 우측값은 타입 T로 추론된다.
		2. 참조 축약(collapse)이 적용된다.
	*/
}