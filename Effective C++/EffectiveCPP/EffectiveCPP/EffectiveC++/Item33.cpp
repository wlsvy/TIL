#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item33 {
	//상속된 이름을 숨기는 일을 피하자

	int x = 0; //전역변수
	void func() {
		double x = 1;
		cout << x; 
		
		// 함수 내부 지역변수 double x를 사용한다. 
		// -> 컴파일러는 x 변수를 만났을 때, 현재 처리하는 지역 유효범위(local scope)를 먼저 탐색하고
		// 만족하는 변수를 만난다면 해당 변수를 사용한다. -> double x가 int x를 가린다
		// 가장 가까운 유효범위에서 부터 탐색한다는 사실이 중요
	}

	class Base {
	public:
		virtual void mf1() = 0;
		virtual void mf1(int) { cout << "Base::mf1(int)\n"; }

		virtual void mf2() { cout << "Base::mf2()\n"; }

		void mf3() { cout << "Base::mf3()\n"; }
		void mf3(double) { cout << "Base::mf3(double)\n"; }
	};

	class Derived : public Base{
	public:
		virtual void mf1() { cout << "Derived::mf1()\n"; }
		void mf3() { cout << "Derived::mf3()\n"; }
		void mf4() { cout << "Derived::mf4()\n"; }
	};

	void func2() {
		Derived d;

		int value = 0;
		
		d.mf1();	//문제 없음 Derived::mf1() 호출
		//d.mf1(value);	//에러 Derived::mf1() 이 Base::mf1(int)을 가린다
		d.mf2();	//문제 없음 Base::mf2() 호출
		d.mf3();	//문제 없음 Derived::mf3() 호출
		//d.mf3(value);	//에러 Derived::mf3() 이 Base::mf3(double)을 가린다
		d.mf4();	//문제 없음 Derived::mf4() 호출
	}
}

//Using 선언을 활용한 해결
namespace Item33_2 {
	class Base {
	public:
		virtual void mf1() = 0;
		virtual void mf1(int) { cout << "Base::mf1(int)\n"; }

		virtual void mf2() { cout << "Base::mf2()\n"; }

		void mf3() { cout << "Base::mf3()\n"; }
		void mf3(double) { cout << "Base::mf3(double)\n"; }
	};

	class Derived : public Base {
	public:
		using Base::mf1;	//base에 있는 것들 중 mf1과 mf3을 이름으로 가진 것들을 
		using Base::mf3;	//Derived의 유효범위에서 볼 수 있도록(또 public 멤버로)

		virtual void mf1() { cout << "Derived::mf1()\n"; }
		void mf3() { cout << "Derived::mf3()\n"; }
		void mf4() { cout << "Derived::mf4()\n"; }
	};

	void func() {
		Derived d;

		int value = 0;

		d.mf1();	//문제 없음 Derived::mf1() 호출
		d.mf1(value);	//문제 없음 Base::mf1(int) 호출
		d.mf2();	//문제 없음 Base::mf2() 호출
		d.mf3();	//문제 없음 Derived::mf3() 호출
		d.mf3(value);	//문제 없음 Base::mf3(double) 호출
		d.mf4();	//문제 없음 Derived::mf4() 호출
	}
}

//private 상속의 경우, 전달 함수(forwarding function)을 활용한 방법
namespace Item33_3 {
	class Base {
	public:
		virtual void mf1() { cout << "Base::mf1()\n"; }
		virtual void mf1(int) { cout << "Base::mf1(int)\n"; }
		void mf2();
	};

	class Derived : private Base {
	public:
		virtual void mf1() { Base::mf1(); }
	};

	void func() {
		Derived d;
		int value = 0;

		d.mf1();	//문제 없음 Derived::mf1() -> Base::mf1() 호출
		//d.mf1(value);	//에러 Derived::mf1() 이 Base::mf1(int)을 가린다

		/*
			public 상속과 달리 private 상속을 할 시 using 선언으로 해결 불가
			using 선언을 내리면 그 이름에 해당하는 것들이 모두 파생 클래스로 내려가 버리기 때문
			-> private 상속의 의미가 사라진다
		*/
	}
}