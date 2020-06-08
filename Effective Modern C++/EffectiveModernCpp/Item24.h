#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//보편 참조와 오른값 참조를 구별하라

namespace Item24 {

	class Widget {
	public:
		Widget() { }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
		~Widget() { }
	};

	void f(Widget&& w) {}	//우측값 참조

	template<typename T>
	void f(std::vector<T> && param) {}	//우측값 참조

	template<typename T>
	void f(T&& param) {} //우측값 참조 아님

	template<typename T>
	void ConstF(const T&& param) {}	//우측값 참조


	

	inline void RunSample() {
		Widget&& var1 = Widget();	//우측값 참조
		auto && var2 = var1;		//우측값 참조 아님

		ConstF(std::forward<Widget>(var1));
		//ConstF(var2);				//컴파일 에러

		std::vector<int> vi;
		vi.push_back(10);
		/*
			push_back은 매개변수 타입이 T&& 이지만 형식 연역이 일어나지 않는다.
			vector 클래스의 타입 T가 결정될 때 그 멤버함수의 매개변수 타입 역시 결정되어버리기 때문.

			emplace_back 의 경우는 형식 연역이 일어난다.
		*/
	}
}