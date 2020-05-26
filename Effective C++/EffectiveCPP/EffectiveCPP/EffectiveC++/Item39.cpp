#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

//private 상속은 심사숙고해서 구사하자

namespace Item39 {

	class Person{};

	class Student : private Person {}; //private 상속

	void eat(const Person& p) { cout << "eat\n"; }
	void study(const Student& s) { cout << "study\n"; }

	void func() {
		Person p;
		Student s;

		eat(p);
		//eat(s);	// 에러 : Student 는 Person 과 is - a 관계에 해당되지 않는다.
	}

	/*
		Private 상속은 기본적으로 is-implemented-in-terms-of 의 일종. 
		기반 클래스에서 쓸 수 있는 기능들 몇 개를 활용할 목적으로 한 행동이지, 
		기반 클래스와 파생 클래스 사이에 어떤 개념적 관계가 있어서 한 행동이 아니다.
	*/

	class Timer {
	public:
		explicit Timer(int tickFrequency) {}
		virtual void onTick() const {}	//일정 주기로 호출되는 메소드
	};

	/*
		onTick() 이 일정 주기마다 자동적으로 호출되니 파생클래스 측에서 호출할 수 없도록 할 필요가 있다.
		public 상속은 좋은 방법이라고 보기 어렵다. 사용자 측에서 이 함수는 따로 호출해도 좋다고 오해할 수 있다.
	*/

	class Widget : private Timer {
	private:
		virtual void onTick() const override {}	//public 메소드가 private으로
	};

	/*
		내부 클래스 & public 상속을 이용한 다른 방법
		Widget 클래스를 설계하는 데 있어서 파생은 가능하게 하되
		파생 클래스에서 onTick을 재정의할 수 없도록 설계 차원에서 방지
	*/

	class Widget2 {
	private:
		class WidgetTimer : public Timer {
		public:
			virtual void onTick() const {}
		};

		WidgetTimer timer;	//멤버 변수가 private 이니 파생클래스에서 접근 불가 -> onTick에 접근 불가능
	};

	/*
		위 방법은 컴파일 의존성 또한 낮출 수 있다.
		직접 상속을 하면 Timer의 헤더 파일을 포함시켜야 하지만
		위 방법으로는 WidgetTimer를 선언만 해두고선, 멤버 변수를 포인터 처리한다면 컴파일 의존성을 피할 수 있다.
	*/


	//공백 기본 클래스 최적화(EBO : empty base optimization)
	class Empty{};	//정의된 데이터가 없는 공백 클래스. 하지만 객체의 크기는 0이 아니다
					//독립 구조(freestanding)의 객체는 반드시 크기가 0이 넘어야 한다 -> c++ 규칙

	class HoldsAnInt {	//이론적으로 int를 저장할 메모리만 있으면 충분하지만, 그보다 더 차지한다
	private:
		int x;
		Empty e;
	};	//sizeof(HoldsAnInt) > sizeof(int)

	class HoldsAnInt2 : private Empty {
	private:
		int x;
	};	//sizeof(HoldsAnInt2) = sizeof(int)
	/*
		EBO 공백 기본 클래스 최적화란 공백 클래스가 상속되었을 시, 컴파일러가 공백 클래스 메모리를 최적화하는 기법
	*/
}