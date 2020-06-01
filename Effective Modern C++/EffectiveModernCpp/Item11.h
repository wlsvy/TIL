#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//정의되지 않은 비공개 함수보다 삭제된 함수를 선호하라

namespace Item11 {

	namespace Case1 {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }

		private:
			Widget(const Widget& rhs); //c++ 98 에서 함수를 호출하지 못하도록 막는 방법, private 지정 후 정의를 빼버린다.
		};
	}
	
	namespace Case2 {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(const Widget& rhs) = delete;
			/*
				c++ 11 부터 도입된 함수 삭제 방법

				컴파일러에 따라 함수 삭제 여부를 확인하는 방법에 차이가 있어서, 접근지정자를 public으로 선언하는것이 관례.
				private 경우 접근 불가능하다고 오류를 보고하는 컴파일러가 있다.
			*/
		};
	}

	namespace Case3 {
		//오버로딩에도 적용가능
		bool IsLucky(int) { return true; }
		bool IsLucky(bool) = delete;
		bool IsLucky(char) = delete;
		bool IsLucky(double) = delete;	//double과 float(형 변환 시 double) 을 배제
	}

	namespace Case4{
		//템플릿에도 적용가능
		class Widget {
		public:
			template<typename T>
			void processPointer(T* ptr) { 
				cout << typeid(T*).name() << endl; 
			}

			template<>
			void processPointer<void>(void*) = delete;
			template<>
			void processPointer<const void>(const void*) = delete;

		private:
			/*
				책에서는 c++ 98 방식으로 멤버함수 템플릿 호출을 막으려 할때 컴파일 에러가 발생한다고 언급되지만
				실제 여기서는 컴파일 가능

				템플릿 특수화는 클래스 범위 공간이 아닌 네임스페이스 범위 공간에서 작성해야 하기 때문에 에러가 발생한다고 설명되었다.
			*/
			template<>
			void processPointer<char>(char*);
		};
	}

	inline void RunSample() {
		Case2::Widget w;
		//Case2::Widget w2 = w;					//삭제된 함수는 호출 불가능

		bool l0 = Case3::IsLucky(10);
		//bool l1 = Case3::IsLucky(false);		//삭제된 함수는 호출 불가능
		//bool l2 = Case3::IsLucky('A');		//삭제된 함수는 호출 불가능
		//bool l3 = Case3::IsLucky(0.5f);		//삭제된 함수는 호출 불가능
		//bool l4 = Case3::IsLucky(3.0);		//삭제된 함수는 호출 불가능

		Case4::Widget g;
		g.processPointer(static_cast<int*>(nullptr));
		g.processPointer(static_cast<float*>(nullptr));
		g.processPointer(static_cast<double*>(nullptr));
		//g.processPointer(static_cast<char*>(nullptr));	//비공개 함수 호출 불가능
		//g.processPointer(static_cast<void*>(nullptr));	//삭제된 함수는 호출 불가능
	}
}