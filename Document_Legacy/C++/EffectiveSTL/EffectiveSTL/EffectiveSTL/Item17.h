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

//쓸데없이 남은 용량은 "바꿔치기(swap) 묘수"를 써서 없애 버리자

namespace Item17 {
	using namespace std;

	//c++11 이후 stl에는 shrink_to_fit 멤버함수가 추가되면서 남은 용량을 좀더 명시적인 방법으로 줄일 수 있습니다.

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }

		Widget& operator=(const Widget& rhs)
		{
			std::cout << "copy operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept
		{
			std::cout << "move operator =" << std::endl;
			return *this;
		}
	};

	inline void RunSample() {
		vector<Widget> v;
		v.reserve(10);

		for (int i = 0; i < 5; i++) {
			v.emplace_back();
		}

		cout << "===============" << endl;
		//재할당이 발생한다는 사실을 기억합시다.
		v.shrink_to_fit();

		cout << "===============" << endl;

	}
}