/*

#include <iostream>
#include <vector>
#include <string>

class TimeKeeper {
public:
	TimeKeeper();
	//~TimeKeeper();	//기본 클래스 포인터로 객체를 삭제할 때, 소멸자가 가상함수가 아니라면 
						//클래스의 기본 클래스 부분만 삭제하고, 파생클래스 부분은 삭제되지 않는다.

	virtual ~TimeKeeper();	//소멸자에 virtual 키워드를 붙여서 해결

	virtual TimeKeeper* getTimeKeeper() { return this; }
};

class AtomicClock : public TimeKeeper {};
class WaterClock : public TimeKeeper {};

void DoSomething() {
	AtomicClock ac;

	TimeKeeper* ptk = ac.getTimeKeeper();
	delete ptk;	//기본 클래스 포인터를 활용해서 메모리 반환
}

*/