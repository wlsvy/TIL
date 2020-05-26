#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item27 {
	//캐스팅은 절약, 또 절약! 잊지 말자

	void Func2() {
		int x = 1, y = 5;

		double d = static_cast<double>(x) / y;
		/*
			int 타입의 x를 double 타입으로 캐스팅하는 부분에서 코드가 만들어진다. 
			대부분의 컴퓨터 아키텍처에서 int의 표현구조와 double의 표현구조가 아예 다르기 때문
		*/
	}

	class Base {};
	class Derived : public Base {};

	void Func1() {
		Derived d;

		Base *pb = &d; //Derived * => Base* 로의 암시적 변환

		/*
			여기서 동일한 객체일지라도 Base 와 Derived 포인터의 주솟값은 서로 다르다. 
			포인터의 변위(offset)를 Derived* 포인터에 적용하여 실제의 Base* 포인터의 값을 구하기 때문

			하나의 객체에 대해서도 그에 해당하는 주솟값은 하나가 아닐 수 있다.
		*/
	}

	class Window {
	public:
		virtual void onResize(){}
	};

	class SpecialWindow : public Window {
	public:
		virtual void onResize() {
			static_cast<Window>(*this).onResize();	//예상치 못한 동작을 할 수 있다

			Window::onResize();						//이 방법을 권장
		}
	};

	/*
		위의 static_cast는 주의해야 하는데 캐스팅이 이루어지면서 객체의 Window(기반클래스)부분의 임시 사본이 만들어지기 때문!
		즉 현재 객체에 대해서 멤버함수가 실행되는 것이 아니라 임시 사본에서 실행되는 것. 
	*/


	/*
		dynamic_cast는 가능하면 사용하지 말 것. 수행성능에 큰 영향을 끼칠 수 있다
	*/
}