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

//ptr_fun, mem_fun, mem_fun_ref의 존재에는 분명한 이유가 있다

namespace Item41 {
	using namespace std;

	/*
		ptr_fun, mem_fun, mem_fun_ref 전부 c++ 11 이후 deprecated 되었으며 c++ 17이후 삭제됩니다.
	*/

	/*
		f란 이름의 함수와 x란 이름의 객체가 하나 있습니다. 여기서 x에 대해 f를 호출하고 싶으며, 호출하는 위치는 x의 멤버 함수의 바깥쪽입니다. 이런 상황에서 C++는 다음의 세 가지 문법을 제공합니다.
		
		#1. f(x);
		f가 멤버 함수가 아닌 경우
		
		#2. x.f();
		f가 x의 멤버 함수이고, x는 객체이든지 객체에 대한 참조자인 경우
		
		#3. p->f();
		f가 x의 멤버 함수이고, p는 x 객체에 대한 포인터인 경우

	*/

	class Widget {
	public:
		void DoSomething() { cout << "DoSomething\n"; }
	};
	
	inline void RunSample() {
		/*
			for_each를 포함한 모든 알고리즘은 내부적으로 문법 #1만을 사용합니다. 
			따라서, 알고리즘에 멤버 함수를 넘겨주면(문법 #2 혹은 문법 #3을 사용해야 하는 경우), 컴파일이 되지 않습니다. 

			- c++ 11 이전
			이처럼 알고리즘에 멤버 함수를 넘겨줘야 하는 상황에서 mem_fun_ref(문법 #2)나 mem_fun(문법 #3)을 사용합니다.

			list<Widget*> lpw;
			for_each(lpw.begin(), lpw.end(), mem_fun(&Widget::test));
		*/
		
		//c++11 이후. 간단한 람다 함수로 해결해버립시다. 거추장스러운 어댑터는 신경쓸 필요 없습니다.
		vector<Widget> vw(3);
		for_each(vw.begin(), vw.end(), [](auto& w) {w.DoSomething(); });
	}
}