#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//재정의 함수들을 override로 선언하라

namespace Item12 {

	/*
		재정의를 위해 필요한 조건
		1. 기반 클래스 함수가 반드시 가상 함수이어야 한다
		2. 기반 함수와 파생 함수의 이름이 반드시 동일해야 한다
		3. 기반 함수와 파생 함수의 매개변수 형식들이 반드시 동일해야 한다.
		4. 기반 함수와 파생 함수의 const 성이 반드시 동일해야 한다
		5. 기반 함수와 파생 함수의 반환 형식과 예외 명세(exception sepcification)가 반드시 호환되어야 한다.

		c++ 11에서 한가지 추가
		6. 멤버 함수들의 참조 한정자(reference qualifier)들이 동일해야 한다.
	*/

	

	namespace WithoutOverride {
		//멤버함수가 재정의 되지 않는 경우, 하지만 컴파일은 문제없다
		class Base {
		public:
			virtual void mf1() const {}
			virtual void mf2(int x) {}
			virtual void mf3() & {}
			void mf4() const {}
		};

		class Derived : public Base {
		public:
			virtual void mf1() {}	//const 선언 없음
			virtual void mf2(unsigned int x) { }	//매개변수가 int 가 아니라 unsigned int
			virtual void mf3() && {}	//참조 한정자가 다름
			virtual void mf4() {}		//기반 클래스에 virtual 키워드가 없음
		};
	}

	namespace WithOverride {
		class Base {
		public:
			virtual void mf1() const {}
			virtual void mf2(int x) {}
			virtual void mf3() & {}
			void mf4() const {}
		};

		class Derived : public Base {
		public:
			/*
				c++11 에서 도입된 override 키워드를 사용하면 재정의 관련 문제점들을 지적해준다.

				아래는 컴파일 불가능
				virtual void mf1() override {}
				virtual void mf2(unsigned int x) override { }
				virtual void mf3() && override {}
				virtual void mf4() override {}
			*/
				
			//컴파일 가능
			virtual void mf1() const override {}
			virtual void mf2(int x) override { }
			virtual void mf3() & override {}
		};
	}

	class Widget {
	public:
		static Widget MakeWidget() { return Widget(); }
		
		Widget() { cout << "default ctor" << endl; }
		Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
		Widget(Widget&& rhs) { cout << "move ctor" << endl; }

		//참조 한정자는 객체가 좌측값/우측값일 때에 따라 사용을 제한시킬 수 있다.

		vector<int>& GetData() & {
			cout << "Get lvalue Data" << endl; 
			return m_Data;
		}		//*this가 좌측값일 때만 사용된다.

		vector<int>&& GetData() && {
			cout << "Get rvalue Data" << endl;
			return std::move(m_Data);
		}		//*this가 우측값일 때만 사용된다.

	private:
		vector<int> m_Data;
	};

	inline void RunSample() {
		Widget w;
		auto val1 = w.GetData();					//"Get lvalue Data"
		auto val2 = Widget::MakeWidget().GetData();	//"Get rvalue Data"
	}
}