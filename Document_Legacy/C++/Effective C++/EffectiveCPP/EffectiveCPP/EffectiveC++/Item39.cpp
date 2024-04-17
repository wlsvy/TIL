#include <iostream>
#include <vector>
#include <string>
#include <functional>

//private ����� �ɻ�����ؼ� ��������

namespace Item39 {
	using namespace std;

	class Person{};

	class Student : private Person {}; //private ���

	void eat(const Person& p) { cout << "eat\n"; }
	void study(const Student& s) { cout << "study\n"; }

	void func() {
		Person p;
		Student s;

		eat(p);
		//eat(s);	// ���� : Student �� Person �� is - a ���迡 �ش���� �ʴ´�.
	}

	/*
		Private ����� �⺻������ is-implemented-in-terms-of �� ����. 
		��� Ŭ�������� �� �� �ִ� ��ɵ� �� ���� Ȱ���� �������� �� �ൿ����, 
		��� Ŭ������ �Ļ� Ŭ���� ���̿� � ������ ���谡 �־ �� �ൿ�� �ƴϴ�.

		�� �������̸� private ��Ӻ��ٴ� ��ü �ռ��� ����ϵ� �� �ʿ��� ��쿡�� private ����� ����սô�.
	*/

	class Timer {
	public:
		explicit Timer(int tickFrequency) {}
		virtual void onTick() const {}	//���� �ֱ�� ȣ��Ǵ� �޼ҵ�
	};

	/*
		onTick() �� ���� �ֱ⸶�� �ڵ������� ȣ��Ǵ� �Ļ�Ŭ���� ������ ȣ���� �� ������ �� �ʿ䰡 �ִ�.
		public ����� ���� ����̶�� ���� ��ƴ�. ����� ������ �� �Լ��� ���� ȣ���ص� ���ٰ� ������ �� �ִ�.
	*/

	class Widget : private Timer {
	private:
		virtual void onTick() const override {}	//public �޼ҵ尡 private����
	};

	/*
		���� Ŭ���� & public ����� �̿��� �ٸ� ���
		Widget Ŭ������ �����ϴ� �� �־ �Ļ��� �����ϰ� �ϵ�
		�Ļ� Ŭ�������� onTick�� �������� �� ������ ���� �������� ����
	*/

	class Widget2 {
	private:
		class WidgetTimer : public Timer {
		public:
			virtual void onTick() const {}
		};

		//��� ������ private �̹Ƿ� �Ļ�Ŭ�������� ���� �Ұ� -> onTick�� ���� �Ұ���
		WidgetTimer timer;	
	};

	/*
		�� ����� ������ ������ ���� ���� �� �ִ�.
		���� ����� �ϸ� Timer�� ��� ������ ���Խ��Ѿ� ������
		�� ������δ� WidgetTimer�� ���� �صΰ�, ��� ������ ������ ó���Ѵٸ� ������ �������� ���� �� �ִ�.
	*/


	/*
		���� �⺻ Ŭ���� ����ȭ(EBO : empty base optimization)

		���ǵ� �����Ͱ� ���� ���� Ŭ����. ������ ��ü�� ũ��� 0�� �ƴϴ�
		���� ����(freestanding)�� ��ü�� �ݵ�� ũ�Ⱑ 0�� �Ѿ�� �Ѵ� -> c++ ��Ģ
	*/
	class Empty{};

	/*
		�̷������� int�� ������ �޸𸮸� ������ ���������, �׺��� �� �����Ѵ�
		sizeof(HoldsAnInt) > sizeof(int)
	*/
	class HoldsAnInt {	
	private:
		int x;
		Empty e;
	};	

	/*
		EBO ���� �⺻ Ŭ���� ����ȭ�� ���� Ŭ������ ��ӵǾ��� ��, �����Ϸ��� ���� Ŭ���� �޸𸮸� ����ȭ�ϴ� ���
		sizeof(HoldsAnInt2) = sizeof(int)
	*/
	class HoldsAnInt2 : private Empty {
	private:
		int x;
	};
	
}