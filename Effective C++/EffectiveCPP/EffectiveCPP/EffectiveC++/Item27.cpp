#include <iostream>
#include <vector>
#include <string>
using namespace std;

//캐스팅은 절약, 또 절약! 잊지 말자

namespace Item27 {

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
		다른 방법이 가능하다면 캐스팅은 피하십시오. 
		특히 수행 성능에 민감한 코드에서 dynamic_cast는 볓 번이고 다시 생각하십시오. 
		
		설계 중에 캐스팅이 필요해졌다면, 캐스팅을 쓰지 않는 다른 방법을 시도해 보십시오.

		const_cast: 객체의 상수성을 없애는 용도로 사용됩니다.

		dynamic_cast: 안전한 다운캐스팅(safe downcasting)을 할 때 사용하는 연산자 입니다. 신경쓰일 정도로 런타임 비용이 높아 쓰지 않는 것이 좋습니다.

		reinterpret_cast: 포인터를 int로 바꾸는 등의 하부 수준 캐스팅을 위한 연산자로서, 
		이것의 작용 결과는 구현환경에 의존적입니다.(이식성이 없습니다.) 이런 캐스트는 하부 수준 코드 외에는 거의 없어야 합니다.

		static_cast: 암시적 변환[비상수 객체를 상수 객체로 바꾸거나(반대는 const_cast만 가능) int를 double로 바꾸는 등의 변환]을 강제로 진행할 때 사용합니다.
	*/
}