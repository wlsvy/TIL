#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//객체 생성 시 괄호 '()' 와 중괄호 '{}' 를 구분하자 

namespace Item07 {

	/*
		균일 초기화(uniform initialization)는 c++11 에서 도입되었으며,

		어디서나 사용 할 수 있고, 모든 것을 표현할 수 있는(개념상으로는) 단 한 종류의 초기화 구문이다.


		균일 초기화 구문은 
		1. 중괄호를 사용한다.
		2. 좁히기 변환(narrow conversion)을 방지한다.
	*/

	void TestNarrowConversion(){
		/*
			형변환을 할 때 기존값의 일부가 손실된다면 좁히기 변환(narrow conversion)
			Ex) float -> int : 소수점 부분이 int로 변환되면서 손실된다.

			중괄호 초기치에 있는 어떤 표현식의 값을 초기화하려는 객체의 형식으로 온전하게 표현할 수 있음이 보장되지 않으면 컴파일러는 그 사실을 보고해야 한다.
		*/

		int i0 = 0, i1 = 0, i2 = 0;
		double d0 = 0, d1 = 0, d2 = 0;

		int sum0{ i0 + i1 + i2 };
		//int sum1{ d0 + d1 + d2 };	//에러, double 에서 int로 변환할려면 축소 변환이 필요하다.

		int sum2(d0 + d1 + d2); // 문제 없음, 결과값이 int에 맞게 잘려나간다.
		int sum3 = d0 + d1 + d2; // 마찬가지
	}

	namespace DefaultCase {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(int i, bool b) { cout << "ctor (int, bool)" << endl; }
			Widget(int i, double d) { cout << "ctor (int, double)" << endl; }

		};

		inline void RunSample() {
			Widget w1(10, true);	//ctor (int, bool)
			Widget w2{ 10, true };	//ctor (int, bool)

			Widget w3(10, 5.0);		//ctor (int, double)
			Widget w4{ 10, 5.0 };	//ctor (int, double)
		}
	}

	namespace WithInitializerList {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
			Widget(Widget&& rhs) { cout << "move ctor" << endl; }
			Widget(int i, bool b) { cout << "ctor (int, bool)" << endl; }
			Widget(int i, double d) { cout << "ctor (int, double)" << endl; }
			Widget(std::initializer_list<long double>) { cout << "ctor (initializer_list<long double>)" << endl; }

			operator float() const { return 0.0f; }

		};

		inline void RunSample() {
			Widget w1(10, true);		//ctor (int, bool)
			Widget w2{ 10, true };		//ctor (initializer_list<long double>) -> 10, true 가 long double 로 전환

			Widget w3(10, 5.0);			//ctor (int, double)
			Widget w4{ 10, 5.0 };		//ctor (initializer_list<long double>)  -> 10, 5.0 가 long double 로 전환

			Widget w5(w4);				//copy ctor
			Widget w6(std::move(w4));	//move ctor

			Widget w7{ w4 };			
			Widget w8{ std::move(w4) };	
			/*
				책에는 
				ctor (initializer_list<long double>) 수행 -> w4가 float 으로 형변환 이후, 다시 long double로 변환

				라고 나와있지만 실제 실행하면 복사/이동생성자가 호출된다.

				책의 설명에 따르면 컴파일러는 중괄호 초기치를 initializer_list 로 대응시키는 경우를 최우선으로 확인하기 때문에
				복사/이동 생성자보다 ctor (initializer_list<long double>) 가 우선시되다는 것
			*/
		}
	}

	namespace OtherCase {
		class CtorWithBool {
		public:
			CtorWithBool(bool b, double d) { cout << "ctor (bool, double)" << endl; }
			CtorWithBool(std::initializer_list<bool>) { cout << "ctor (initializer_list<bool>)" << endl; }
		};

		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(int i, bool b) { cout << "ctor (int, bool)" << endl; }
			Widget(int i, double d) { cout << "ctor (int, double)" << endl; }
			Widget(std::initializer_list<string>) { cout << "ctor (initializer_list<string>)" << endl; }
		};

		inline void RunSample() {
			//CtorWithBool w{ true, 0.5 };	//에러, float -> bool로 축소변환이 발생한다.

			Widget w1(10, true);		//ctor (int, bool)
			Widget w2{ 10, true };		//ctor (int, bool)

			Widget w3(10, 5.0);			//ctor (int, double)
			Widget w4{ 10, 5.0 };		//ctor (int, double)
			/*
				int, double, bool 은 string으로 암시적변환이 불가능하기 때문에 
				ctor (initializer_list<string>) 는 고려되지 않는다.
			*/

			Widget w5;					//default ctor
			Widget w6{};				//default ctor, 비어있는 중괄호는 '인수 없음'을 의미한다
			Widget w7();				//함수 선언. 객체가 생성되지 않는다.

			//비어있는 initializer_list 전달하는 방법

			Widget w8({});				//ctor (initializer_list<string>) -> 빈 초기치 리스트를 매개변수로 전달
			Widget w9{{}};				//ctor (initializer_list<string>) -> 빈 초기치 리스트를 매개변수로 전달
			
			vector<int> v0(10, 20);		//값이 20인 원소가 10개 있는 벡터 생성
			vector<int> v1{ 10, 20 };	//값이 10, 20인 원소 2개가 있는 벡터 생성

		}
	}
}