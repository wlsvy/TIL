#include <iostream>
#include <vector>
#include <string>

//다형성을 가진 기본 클래스에서는 소멸자를 반드시 가상 소멸자로 선언하자
namespace Item07 {

	/*
		다형성을 가진 기본 클래스에는 반드시 가상 소멸자를 선언해야 합니다. 
		즉, 어떤 클래스가 가상 함수를 하나라도 갖고 있으면, 이 클래스의 소멸자도 가상 소멸자이어야 합니다.

		반대로 기본 클래스로 설계되지 않았거나 다형성을 갖도록 설계되지 않은 클래스에는 가상 소멸자를 선언하지 말아야 합니다.
	*/

	class TimeKeeper {
	public:
		TimeKeeper() {}

		/*
			기본 클래스 포인터로 객체를 삭제할 때, 소멸자가 가상함수가 아니라면 
			클래스의 기본 클래스 부분만 삭제하고, 파생클래스 부분은 삭제되지 않는다.

			자원 누수로 이어질 수 있다.
		*/
		//~TimeKeeper();	
							
		//소멸자에 virtual 키워드를 붙여서 해결
		virtual ~TimeKeeper() {}

		virtual TimeKeeper* getTimeKeeper() { return this; }
	};

	class AtomicClock : public TimeKeeper {};
	class WaterClock : public TimeKeeper {};

	void DoSomething() {
		AtomicClock ac;

		TimeKeeper* ptk = ac.getTimeKeeper();
		delete ptk;	//기본 클래스 포인터를 활용해서 메모리 반환
	}
}