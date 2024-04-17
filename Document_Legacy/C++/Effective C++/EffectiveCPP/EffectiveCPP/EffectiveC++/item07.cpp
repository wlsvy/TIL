#include <iostream>
#include <vector>
#include <string>

//�������� ���� �⺻ Ŭ���������� �Ҹ��ڸ� �ݵ�� ���� �Ҹ��ڷ� ��������
namespace Item07 {

	/*
		�������� ���� �⺻ Ŭ�������� �ݵ�� ���� �Ҹ��ڸ� �����ؾ� �մϴ�. 
		��, � Ŭ������ ���� �Լ��� �ϳ��� ���� ������, �� Ŭ������ �Ҹ��ڵ� ���� �Ҹ����̾�� �մϴ�.

		�ݴ�� �⺻ Ŭ������ ������� �ʾҰų� �������� ������ ������� ���� Ŭ�������� ���� �Ҹ��ڸ� �������� ���ƾ� �մϴ�.
	*/

	class TimeKeeper {
	public:
		TimeKeeper() {}

		/*
			�⺻ Ŭ���� �����ͷ� ��ü�� ������ ��, �Ҹ��ڰ� �����Լ��� �ƴ϶�� 
			Ŭ������ �⺻ Ŭ���� �κи� �����ϰ�, �Ļ�Ŭ���� �κ��� �������� �ʴ´�.

			�ڿ� ������ �̾��� �� �ִ�.
		*/
		//~TimeKeeper();	
							
		//�Ҹ��ڿ� virtual Ű���带 �ٿ��� �ذ�
		virtual ~TimeKeeper() {}

		virtual TimeKeeper* getTimeKeeper() { return this; }
	};

	class AtomicClock : public TimeKeeper {};
	class WaterClock : public TimeKeeper {};

	void DoSomething() {
		AtomicClock ac;

		TimeKeeper* ptk = ac.getTimeKeeper();
		delete ptk;	//�⺻ Ŭ���� �����͸� Ȱ���ؼ� �޸� ��ȯ
	}
}