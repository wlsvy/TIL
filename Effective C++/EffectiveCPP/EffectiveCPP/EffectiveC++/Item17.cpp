#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item17 {
	//new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자

	class Widget{};

	void ProcessWidget(std::shared_ptr<Widget> pw, int priority) {}	//동적으로 생성된 Widget에 대해 우선순위에 따라 처리하는 함수
	int priority(); //처리 우선순위를 알려주는 함수

	void Func() {
		//ProcessWidget(new Widget, priority());	컴파일 X, 
													//shared_ptr 생성자는 explicit 선언이 되어있어
													//new Widget이 반환하는 포인터로 암시적 변환이 불가능하다.

		ProcessWidget(std::shared_ptr<Widget>(new Widget), priority());	//이 문장은 자원을 흘릴 가능성이 있다
		/*
			컴파일러는 ProcessWidget 호출 코드를 만들기 전에 매개변수로 넘겨지는 인자를 평가한다.

			std::shared_ptr<Widget>(new Widget) 이 문장은
			new Widget 표현식 실행 -> std::shared_ptr<Widget>의 생성자 호출  의 순서로 이루어진다.

			즉 ProcessWidget 함수가 호출되기 전에
			priority() 호출 -> new Widget 호출 -> std::shared_ptr<Widget> 생성자 호출
			순으로 이루어져야 할 것

			하지만 컴파일러마다 또 다른 경우가 있는데 연산 실행 순서가 다른 경우가 있다.
			new Widget 호출 -> priority() 호출 ->  std::shared_ptr<Widget> 생성자 호출
			요렇게 될 수 있으며, priority()의 경우 세번째로 실행 될 수도 있는 것.

			하지만 만약에 priority가 중간에서 호출될 때 priority 안에서 예외가 발생한다면??
			new Widget으로 만들어진 자원은 shared_ptr에 저장되지 못하고 그대로 잃어버리게 된다.
		*/
	}

	void Func2() {
		std::shared_ptr<Widget> pw(new Widget);	//문제를 피하기 위해서 
												//new로 만든 객체를 스마트 포인터에 담는 과정을 따로 한 문장으로 만들 것 
												//이 방식은 컴파일러의 재조정을 받을 여지가 적기 때문에 자원 누출 가능성을 차단한다.

		ProcessWidget(pw, priority());
	}


	int priority() {
		return 0;
	}
}
