/*

#include <iostream>
#include <vector>
#include <string>

class TimeKeeper {
public:
	TimeKeeper();
	//~TimeKeeper();	//�⺻ Ŭ���� �����ͷ� ��ü�� ������ ��, �Ҹ��ڰ� �����Լ��� �ƴ϶�� 
						//Ŭ������ �⺻ Ŭ���� �κи� �����ϰ�, �Ļ�Ŭ���� �κ��� �������� �ʴ´�.

	virtual ~TimeKeeper();	//�Ҹ��ڿ� virtual Ű���带 �ٿ��� �ذ�

	virtual TimeKeeper* getTimeKeeper() { return this; }
};

class AtomicClock : public TimeKeeper {};
class WaterClock : public TimeKeeper {};

void DoSomething() {
	AtomicClock ac;

	TimeKeeper* ptk = ac.getTimeKeeper();
	delete ptk;	//�⺻ Ŭ���� �����͸� Ȱ���ؼ� �޸� ��ȯ
}

*/