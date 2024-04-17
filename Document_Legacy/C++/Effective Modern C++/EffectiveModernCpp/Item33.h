#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//std::forward를 통해서 전달할 auto&& 매개변수에는 decltype을 사용하라

namespace Item33 {

	/*
		이 표현식은

		auto f = [](auto x){ return normalize(x); };

		아래처럼 변환된다.

		class 컴파일러가_만든_어떤_클래스_이름 {
		public:
			template <typename T>          
			auto operator()(T x) const { return normalize(x); }     //const가 여기 붙는다.
		};
			
	*/

	

	inline void f() { std::cout << "Void" << std::endl; }
	//inline void f(int) { std::cout << "int" << std::endl; }
	inline void f(int&) { std::cout << "int&" << std::endl; }
	inline void f(int&&) { std::cout << "int&&" << std::endl; }

	template <typename T>                      
	void fwd(T&& param)  
	{
		f(std::forward<T>(param));
	}
	/*
		만약 람다로 완벽전달을 구현할려면?

		auto f = [](auto&& x)
		{ return normalize(std::forward<???>(x)); };
	*/

	inline void RunSample() {

		auto fwdLambda = [](auto && param)
		{
			f(std::forward<decltype(param)>(param));
		};

		int i = 0;
		int& ri = i;
		fwdLambda(i);
		fwdLambda(ri);
		fwdLambda(3);
	}
}