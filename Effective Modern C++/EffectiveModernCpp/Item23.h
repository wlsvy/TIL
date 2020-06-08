#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//std::move 와 std::forward를 숙지하라

namespace Item23 {

	/*
		std::move는 우측값으로의 무조건 캐스팅을 수행한다. std::move 자체는 아무것도 이동하지 않는다.
		std::forward는 주어진 인수가 우측값에 묶인 경우에만 그것을 우측값으로 캐스팅한다.
		std::move와 std::forward 둘 다, 실행시점에서는 아무 일도 하지 않는다.
	*/

	namespace Case0 {
		/*
			이동 생성자의 매개변수는 const로 선언하지 말 것. 이동이 아닌 복사 생성자를 호출한다. <= 실제 실행시켜 보니 이동생성자가 호출되긴 한다. 물론 멤버변수는 변경하지 못하지만

			이동 생성자는 실제로는 아무것도 이동시키지 않을 뿐만 아니라
			캐스팅 되는 객체가 이동 자격을 갖추게 된다는 보장도 제공하지 않는다.
		*/
		class Widget {
		public:
			Widget() { }
			Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
			Widget(const Widget&& rhs) { std::cout << "move ctor" << std::endl; }
			~Widget() { }
		};
	}

	namespace Case1 {
		class Widget {
		public:
			Widget() { }
			Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
			Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
			~Widget() { }
		};

		inline void Process(const Widget & w) {
			std::cout << "Lvalue Param" << std::endl;
		}
		inline void Process(Widget && w) {
			std::cout << "Rvalue Param" << std::endl;
		}
		template<typename T>
		inline void LogType(T&& param) {
			std::cout << "Type == " << typeid(decltype(param)).name() << std::endl;
			Process(param);	//항상 좌측값 전달
			Process(std::forward<T>(param));	//좌측값 참조는 좌측값으로, 우측값 참조는 우측값으로
		}
	}

	



	inline void RunSample() {
		Case0::Widget w0;
		Case0::Widget w0_moveTest(std::move(w0));	//복사생성자 호출

		std::cout << "===================" << std::endl;


		Case1::Widget w1;
		Case1::Widget w1_moved(std::move(w1));

		Case1::LogType(w1);
		Case1::LogType(std::move(w1));
	}
}