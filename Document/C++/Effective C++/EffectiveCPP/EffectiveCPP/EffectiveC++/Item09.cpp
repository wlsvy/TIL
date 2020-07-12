#include <iostream>
#include <vector>
#include <string>

//객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자.
namespace Item09 {

	/*
		 기본클래스가 생성되는 시점에, 파생클래스는 아직 만들어지지 않은 상태다. 
		 이때 가상함수를 실행하게 되면 파생클래스의 함수는 실행할 수 없는게 당연하다. 

		소멸자의 경우도 마찬가지, 파생클래스가 소멸된 시점에 기본클래스의 소멸자 내부에 가상함수에 있다면 프로그래머가 원하는 동작을 하지 않을 수 있다.

		파생클래스 객체의 기본 클래스 부분이 생성되는 동안은 그 객체의 타입은 전부 기본 클래스로 결정되므로, 
		가상함수를 포함해서 dynamic_cast / typeid 를 사용할 때 영향을 끼친다.
	*/

	class Transaction {
	public:
		Transaction()
		{
			logTransaction();
		}
		virtual void logTransaction() const { std::cout << "Transaction" << std::endl; }
	};

	class BuyTransaction : public Transaction {
	public:
		virtual void logTransaction() const { std::cout << "BuyTransaction" << std::endl; }
	};

	void RunSample() {
		BuyTransaction tr;		//BuyTransaction 가 아닌 Transaction 출력
	}
}

