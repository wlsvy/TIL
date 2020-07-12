#include <iostream>
#include <vector>
#include <string>

// 자원 관리에는 객체가 그만!

namespace Item13 {
	

	/*
		프로그래밍 분야에서 자원(Resource)이란,  사용을 일단 마치고 난 후엔 시스템에 돌려주어야 하는 모든 것을 일컫는다.

		스마트 포인터 활용할 것. 자원 관리 객체를 활용하여 자원을 관리하는 것이 중요합니다.
	*/

	class Investment{};

	Investment* CreateInvestment() { return new Investment(); }

	void f(){
		Investment *pInv = CreateInvestment();

		/*
			생성한 Investment 객체를 사용하는 부분

			만약 여기서 에러가 발생하거나, 
			goto, continue, break, return 등으로 인해 갑자기 스코프 밖으로 빠져나간다면

			그대로 메모리 누수로 이어진다
		*/

		delete pInv;
	}

	void f2() {
		/*
			프로그래머가 delete를 해줄 필요 없이 스코프를 빠져나갈때
			자동으로 auto_ptr 소멸자에서 메모리 반환
		*/
		std::auto_ptr<Investment> pInv(CreateInvestment());
	}

	/*
		자원 관리에 객체를 사용하는 방법의 두 가지 특징

		1. 자원을 획득한 후에 자원 관리 객체에게 넘긴다 - 
		RAII(Resource Acqusition Is Initialization) 자원 획득 시 곧바로 자원 관리 객체 초기화
		자원 획득과 자원 관리 객체 초기화가 한 문장에서 이루어지게 되는 것

		2. 자원 관리 객체는 자신의 소멸자를 사용해서 자원이 확실히 해제되도록 한다.
		유효범위를 벗어나는 경우 등 자원 관리객체의 소멸자가 호출되는 시점에 자원 해제가 자동적으로 해제되는 것

	*/
}