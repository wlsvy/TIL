#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>

namespace Item15 {

	/*
		constexpr은 어떠한 값이 단지 상수일 뿐만 아니라 컴파일 시점에서 알려진다는 점을 나타낸다.
		내장형 시스템 개발자(embedded)에게 중요한 특징일 수 있다.

		constexpr이 객체에 적용될 때는 그 값이 컴파일 시간에 알려진다.
		모든 constexpr 객체는 const 지만 반대는 성립하지 않는다.
	*/

	namespace ConstexprObject {
		inline void RunSample() {

			const int csize1 = 5;
			std::array<int, csize1> arr1;	//가능

			int size = 5;
			const int csize2 = size;
			//std::array<int, csize2> arr2;	//오류 csize2 는 컴파일 시간에 결정되지 않음

			constexpr int csize3 = 5;
			std::array<int, csize3> arr3;	//가능

			//constexpr int csize4 = size;	//오류, csize4는 컴파일 시간에 결정되지 않음
		}
	}

	namespace ConstexprFunc {
		constexpr int pow(int base, int exp) noexcept {
			for (int i = 0; i < exp; ++i) {
				base *= exp;
			}
			return base;
		}

		class Widget {
		public:
			Widget() { std::cout << "default ctor" << std::endl; }
		};

		class Point {
		public:
			/*
				point의 객체의 멤버들은 double은 컴파일 시점에 알려질 수 있기 때문에, point의 생성자를 constexpr으로 선언가능하다.
			*/
			constexpr Point(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal) {}
			constexpr double xValue(void) const noexcept { return x; }
			constexpr double yValue(void) const noexcept { return y; }

			/*
				C++ 11에서 setX/setY 를 constexpr 으로 선언하기에는 두 가지 제약이 있었다.
				1. 두 함수 안에서는 객체의 멤버를 수정하지만 c++11에서는 constexpr 멤버 함수는 암묵적으로 const 로 선언된다.
				2. 이 멤버 함수들은 반환 형식이 void인데 c++11에서 void는 리터럴 형식이 아니다.

				C++14에서는 두 가지 제약이 사라졌으니 설정용 멤버함수 역시 constexpr 선언이 가능하다.
			*/
			constexpr void setX(double newX) noexcept { x = newX; }
			constexpr void setY(double newY) noexcept { y = newY; }
			
		private:
			double x, y;
		};

		constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
		{
			//constexr 멤버 함수만 호출가능하다.
			return { (p1.xValue() + p2.xValue()) / 2,    
					(p1.yValue() + p2.yValue()) / 2 };   
		}

		constexpr Point reflection(const Point& p) noexcept {
			Point result;
			result.setX(-p.xValue());
			result.setY(-p.yValue());
			return result;
		}

		inline void RunSample() {
			//constexpr Widget w;	//오류, 생성자가 constexpr이 아님
			constexpr Point p1(1.0f, 2.0f);
			constexpr Point p2(31.2f, 4.1f);
			constexpr auto mid = midpoint(p1, p2);	
			constexpr auto reflectedMid = reflection(mid);
			/*
				컴파일 시간에, 읽기 전용 메모리(Rom)에 생성한다.
				전통적으로 실행시점에 수행했던 계산들을 컴파일 시간으로 옮기는 것
			*/
		}
	}
}