#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//Pimpl 관용구를 사용할 때에는 특수멤버 함수들을 구현 파일에서 정의하라

namespace Item22 {

	struct Impl;	//선언만 되어 있는 불완전 형식(incomplete type) - 정의는 되어 있지 않다.

	
	
	namespace Case0 {
		class Widget {
		public:

		private:

			//std::unique_ptr<Impl> pImpl; 
			/*
			컴파일이 되지 않는다. 그 이유는
			pImpl 이 소멸되는 시점, 즉 Widget 의 소멸자가 호출되는 시점에 Impl 타입이 완전한 형식이 아니기 때문이다.

			대부분의 표준 라이브러리 구현들에서 그 삭제자 함수는 delete를 적용하기 전에,
			혹시 생 포인터가 불완전한 타입을 가리키지 않는지를 C++11의 static_assert를 이용해서 점검한다.

			여기서 소멸자는 다른 모든 특수 멤버함수처럼 암묵적으로 inline 선언되기 때문에 static assert 결과가 참이 되지 않는다.

			이를 해결하기 위해서는
			*/
		};
	}

	namespace Case1 {
		class Widget {
		public:
			Widget();
			~Widget();	//생성자 + 소멸자 본문을 cpp 파일에 구현하면 된다. cpp 파일에서 Impl 의 정의를 컴파일러가 보게 만든다면 문제없다.
		private:
			std::unique_ptr<Impl> pImpl; 
		};
	}

	namespace Case2 {
		/*
			항목 17에 나오듯이, Widget에 소멸자를 선언하면 컴파일러는 이동 연산들을 작성하지 않는다. 
			따라서 이동 연산들을 지원하려면 해당 이동 연산들을 직접 선언해야 한다. 

			복사 연산이 필요하다면 복사 연산도 직접 작성해야 한다.
		*/
		class Widget {
		public:
			Widget();
			~Widget();
			Widget(Widget&& rhs);	
			Widget& operator=(Widget&& rhs);
			/*
			이동 연산자에 대해서도 주의할 것. 객체가 이동되면서 pImpl을 파괴하는데 그 과정에서 Impl이 불완전 타입이면 다시한번 컴파일러는 에러메시지를 출력한다.
			역시 구현 파일에 정의를 선언해서 해결할 수 있다.
			*/

		private:
			std::unique_ptr<Impl> pImpl;
		};
	}

	/*
	위의 조언은 std::unique_ptr에 적용될 뿐, std::shared_ptr에는 적용되지 않는다.
	이 차이는 커스텀 삭제자를 지원하는 방식의 차이에서 비롯된 것이다.

	std::unique_ptr에서 삭제자의 타입은 해당 스마트 포인터 타입의 일부이며, 
	이 덕분에 컴파일러는 더 작은 실행시점 자료구조와 더 빠른 실행시점 코드를 만들어 낼 수 있다. 
	그 대신 컴파일러가 작성한 특수 멤버함수가 쓰이는 시점에서 피지칭 타입들이 완전한 타입들이어야 한다.

	반면 std::shared_ptr에서는 삭제자의 타입이 스마트 포인터 타입의 일부가 아니다. 
	이 때문에 실행시점 자료구조가 더 커지고 실행 코드가 다소 더 느려지지만, 
	컴파일러가 작성한 특수 멤버 함수들이 쓰이는 시점에서 피지칭 타입들이 완전한 타입이어야 한다는 요구 조건이 사라진다.
	*/

	inline void RunSample() {
		Case0::Widget w0;

		Case1::Widget w1;

		Case2::Widget w2;
		Case2::Widget w2move(std::move(w2));
	}
}