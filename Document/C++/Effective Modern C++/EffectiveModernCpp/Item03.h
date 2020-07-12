#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

//decltype의 작동 방식을 숙지하라.

namespace Item03 {

	/*
		decltype 은 주어진 이름이나 표현식의 형식을 알려준다.
		템플릿 추론과 auto와는 달리 decltype은 주어진 이름이나 표현식의 구체적인 형식을 그대로 말해준다.
		(참조성 및 const 특징까지)
	*/

	struct Widget{};

	const int i = 0;									//decltype(i) : const int

	bool f(const Widget & w) { return true; }			//decltype(w) : const Widget &
														//decltype(f) : bool(const Widget &)

	struct Point {
		int x, y;
	};
	//decltype(Point::x) : int
	//decltype(Point::y) : int

	Widget w;		//decltype(w) : widget
					//decltype(f(w)) : bool

	vector<int> v;	//decltype(v) : vector<int>
					//decltype(v[0]) : int &

	namespace UsingDecltype0 {
		template<typename Container, typename Index>
		auto Access(Container& c, Index i) {					//단순 auto 사용시 템플릿 타입 추론 과정에서 참조성(&)이 무시된다.
			return c[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			//Access(d, 5) = 10;	오류, 반환 타입은 int 이며 우측값이다.
		}
	}

	namespace UsingDecltype1 {
		template<typename Container, typename Index>
		auto Access(Container& c, Index i) 
			-> decltype(c[i])									//decltype(c[i])는 c, i의 선언이 필요하기 때문에 매개변수 목록 다음에 위치함
		{
			return c[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			Access(d, 5) = 10;	//반환 타입은 int & 이며 컴파일 가능
		}
	}

	namespace UsingDecltype2 {
		template<typename Container, typename Index>
		decltype(auto) Access(Container& c, Index i)			//decltype(auto) 에서 auto 는 반환 타입이 추측되어야 함을 뜻하고, decltype은 추측 과정에서 decltype 의 규칙이 적용되어야 함을 뜻한다.
		{
			return c[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			Access(d, 5) = 10;	//반환 타입은 int & 이며 컴파일 가능
		}
	}

	namespace UsingDecltype3 {
		template<typename Container, typename Index>
		decltype(auto) Access(Container&& c, Index i)			//보편 참조 활용, 좌측값과 우측값 두 가지 모두 처리할 수 있도록 구현
		{
			return std::forward<Container>(c)[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			Access(d, 5) = 10;	//반환 타입은 int & 이며 컴파일 가능

			auto createDeque = []() {return std::deque<int>({ 0, 0, 0, 0, 0, 0 }); };

			Access(createDeque(), 5) = 10;	//우측값 매개변수 적용

			decltype(auto) rValue = forward<deque<int>>(d);	//std::deque<int> &&
		}
	}
	

	/*
	
		그 외, decltype이 예상 밖의 결과를 도출하는 경우

		변수를 괄호로 감싸면, 값 형식이 아닌 좌측참조 형식을 산출한다.

	*/


	decltype(auto) f1() {
		int x = 0;
		return x;		//반환 타입 : int
	}

	decltype(auto) f2() {
		int x = 0;
		return (x);		//반환 타입 : int &
	}

}

