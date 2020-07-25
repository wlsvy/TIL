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

//less<T>는 operator<의 의미임을 꼭 알아두자

namespace Item42 {
	/*
		less를 사용하겠다면 반드시 operator<의 의미를 가지게 하세요.
		C++ 프로그래머는 몇 가지 사항에 대해 아무 생각 없이 이런 가정을 합니다.

		이를테면 그들은 복사 생성자는 복사를 할 것이라고 가정합니다(항목 8에서 보이고 있듯, 이 규칙을 지키지 않으면 끔찍한 일이 생깁니다).

		그들은 객체의 주소를 받아내면 포인터가 나온다는 가정도 합니다(항목 18로 가셔서, 그렇지 않을 때 어떤 일이 생기는지 알아보세요).

		bind1st와 not2 같은 어댑터는 함수 객체에 적용될 것이라고 가정합니다(항목 40에서는 그렇지 않을 때 어떻게 산통이 깨지는지 설명하고 있습니다).

		C++ 프로그래머는 operator+는 더하기를 하고(string만 제외하고요. 하지만 문자열 잇기에 "+"를 사용하는 것은 긴 내력을 가지고 있습니다), operator-는 빼기를 하고, operator==는 비교한다고 가정하죠.

		마지막으로 less는 operator<과 다름없다고 생각해 버립니다.

		이러한 프로그래머의 기대를 져버리게 되면 쓸데없는 혼란이 생깁니다. operator+가 빼기를 한다고 생각해 보세요. 끔찍하죠?
	*/



	class Widget {
	public:
		int GetSize() const { return size; }
		int GetSpeed() const { return speed; }

		int size;
		int speed;
	};
}

namespace std {
	
	//아래는 operator < 의 의미에서 크게 벗어나지 않습니다. 괜찮습니다
	template <typename T>
	struct less<shared_ptr<T> > {
		bool operator()(const shared_ptr<T>& a, const shared_ptr<T>& b) const
		{
			return less<T>()(*a, *b);
		}
	};

	/*
		아래는 오해의 여지가 있습니다. Widget의 특정 멤버만을 비교한다면 operator < 와 닮았다고 말하기 어렵습니다.
		이러한 사정을 모르는 사람이 less<Widget>을 사용하려 할때, less<Widget>은 당연히 내부적으로 Widget의 operator<를 사용한다고 생각할 것입니다.
	*/
	template <>
	struct less<Item42::Widget> {
		bool operator()(const Item42::Widget& a, const Item42::Widget& b) const
		{
			return less<int>()(a.GetSpeed(), b.GetSpeed());
		}
	};

	/*
		less(그러니까 operator<)가 아닌 '다른' 기준을 가지고 객체를 정렬하겠다면 less라고 불리지 않는 특수한 함수자 클래스를 만드세요.
		다음 예제 코드는, 방금 전 예제 코드의 상황을 보다 바람직하게 해결한 예제 코드입니다.
	*/

	//람다를 사용할 수 있습니다.
	auto WidgetSpeedCompareLess = [](const Item42::Widget& a, const Item42::Widget& b)
	{
		return less<int>()(a.GetSpeed(), b.GetSpeed());
	};

	//함수 객체가 람다보다 체계적인 느낌을 주는 것 같습니다.(개인적인 생각)
	struct WidgetSpeedCompareGreater {
		bool operator()(const Item42::Widget& a, const Item42::Widget& b) const
		{
			return greater<int>()(a.GetSpeed(), b.GetSpeed());
		}
	};
}

namespace Item42 {
	using namespace std;

	inline void RunSample() {

		vector<shared_ptr<Widget>> vsw(5);
		generate(vsw.begin(), vsw.end(),
			[count = 0]() mutable->shared_ptr<Widget> 
		{
			auto ptr = make_shared<Widget>();
			ptr->size = count++;
			ptr->speed = count * 2 % 5;
			return ptr;
		});
		sort(vsw.begin(), vsw.end(), less<shared_ptr<Widget>>());


		vector<Widget> vw(5);
		generate(vw.begin(), vw.end(), [count = 0]() mutable->Widget {return { count++, count * 2 % 5 }; });

		sort(vw.begin(), vw.end(), WidgetSpeedCompareGreater());
		sort(vw.begin(), vw.end(), WidgetSpeedCompareLess);

		//set같은 연관 컨테이너의 비교 연산 타입을 지정할 수도 있습니다.
		set<Widget, WidgetSpeedCompareGreater> swGreater(vw.begin(), vw.end());
		/*
			람다를 활용하는 경우 살짝 복잡해집니다. 
			decltype으로 클로져 객체의 타입을 알려줘야 하며, 람다 객체는 임의로 생성할 수 없기에 생성자에 클로저 객체를 직접 넘겨줘야 합니다.

			함수 객체를 활용하는 위의 경우, 해당 타입의 새로운 객체가 생성되어 set에 바인딩되지만
			람다를 활용하는 경우, 매개변수로 넘긴 람다 객체가 그대로 set에 바인딩 됩니다.

			만일의 경우, 람다가 변수 캡쳐를 통해 외부의 값을 참조하는 경우가 있다면, 변수의 생명주기를 고려해서 사용해야 할 것입니다.
		*/
		set<Widget, decltype(WidgetSpeedCompareLess)> swGreater2(vw.begin(), vw.end(), WidgetSpeedCompareLess);

	}
}