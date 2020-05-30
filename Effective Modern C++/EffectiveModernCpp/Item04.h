#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

//연역된 형식을 파악하는 방법을 알아두라

namespace Item04 {
	
	const int theAnswer = 42;

	auto x = theAnswer;		//int
	auto y = &theAnswer;	//const int *

	template<typename T>
	void f(const T& param) {
		cout << "T = " << typeid(T).name() << endl;
		cout << "param = " << typeid(param).name() << endl;
	}

	class Widget{};

	inline void RunSample() {
		cout << typeid(x).name() << endl;
		cout << typeid(y).name() << endl;

		Widget w;
		f(w);
		/*
			T = Widget
			param = Widget
		*/

		const vector<Widget> vw(1, Widget());
		f(&vw[0]);
		/*
			T = const Widget *
			param = const Widget *

		*/


		/*
			param 타입과 T 타입은 동일하게 나타난다. param의 타입은 분명 const & T 지만 const & 가 포함되지 않는다.

			정확히 말하면 두번째 예시에서 param 타입 const Widget* const & 에서 const & 가 포함되지 않는다.

			c++ 표준에 따르면 std::type_info::name 은 반드시 주어진 형식을 마치 템플릿 함수에 값 전달 매개변수로서 전달된 것처럼 취급해야 한다.
			즉 항목1 에서 템플릿 타입 연역 과정에서 참조성(&)이 무시되고, 참조를 제거한 뒤 형식이 const(혹은 volatile) 이면 const(혹은 volatile)성 역시 무시된다.

			즉 std::type_info::name 정보는 믿을 만하지 않다.

			boost의 Boost.TypeIndex를 활용하면 정확한 타입 정보를 얻을 수 있다.

		*/
	}
}
