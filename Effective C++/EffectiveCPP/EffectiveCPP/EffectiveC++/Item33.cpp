#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item33 {
	//��ӵ� �̸��� ����� ���� ������

	int x = 0; //��������
	void func() {
		double x = 1;
		cout << x; 
		
		// �Լ� ���� �������� double x�� ����Ѵ�. 
		// -> �����Ϸ��� x ������ ������ ��, ���� ó���ϴ� ���� ��ȿ����(local scope)�� ���� Ž���ϰ�
		// �����ϴ� ������ �����ٸ� �ش� ������ ����Ѵ�. -> double x�� int x�� ������
		// ���� ����� ��ȿ�������� ���� Ž���Ѵٴ� ����� �߿�
	}

	class Base {
	public:
		virtual void mf1() = 0;
		virtual void mf1(int) { cout << "Base::mf1(int)\n"; }

		virtual void mf2() { cout << "Base::mf2()\n"; }

		void mf3() { cout << "Base::mf3()\n"; }
		void mf3(double) { cout << "Base::mf3(double)\n"; }
	};

	class Derived : public Base{
	public:
		virtual void mf1() { cout << "Derived::mf1()\n"; }
		void mf3() { cout << "Derived::mf3()\n"; }
		void mf4() { cout << "Derived::mf4()\n"; }
	};

	void func2() {
		Derived d;

		int value = 0;
		
		d.mf1();	//���� ���� Derived::mf1() ȣ��
		//d.mf1(value);	//���� Derived::mf1() �� Base::mf1(int)�� ������
		d.mf2();	//���� ���� Base::mf2() ȣ��
		d.mf3();	//���� ���� Derived::mf3() ȣ��
		//d.mf3(value);	//���� Derived::mf3() �� Base::mf3(double)�� ������
		d.mf4();	//���� ���� Derived::mf4() ȣ��
	}
}

//Using ������ Ȱ���� �ذ�
namespace Item33_2 {
	class Base {
	public:
		virtual void mf1() = 0;
		virtual void mf1(int) { cout << "Base::mf1(int)\n"; }

		virtual void mf2() { cout << "Base::mf2()\n"; }

		void mf3() { cout << "Base::mf3()\n"; }
		void mf3(double) { cout << "Base::mf3(double)\n"; }
	};

	class Derived : public Base {
	public:
		using Base::mf1;	//base�� �ִ� �͵� �� mf1�� mf3�� �̸����� ���� �͵��� 
		using Base::mf3;	//Derived�� ��ȿ�������� �� �� �ֵ���(�� public �����)

		virtual void mf1() { cout << "Derived::mf1()\n"; }
		void mf3() { cout << "Derived::mf3()\n"; }
		void mf4() { cout << "Derived::mf4()\n"; }
	};

	void func() {
		Derived d;

		int value = 0;

		d.mf1();	//���� ���� Derived::mf1() ȣ��
		d.mf1(value);	//���� ���� Base::mf1(int) ȣ��
		d.mf2();	//���� ���� Base::mf2() ȣ��
		d.mf3();	//���� ���� Derived::mf3() ȣ��
		d.mf3(value);	//���� ���� Base::mf3(double) ȣ��
		d.mf4();	//���� ���� Derived::mf4() ȣ��
	}
}

//private ����� ���, ���� �Լ�(forwarding function)�� Ȱ���� ���
namespace Item33_3 {
	class Base {
	public:
		virtual void mf1() { cout << "Base::mf1()\n"; }
		virtual void mf1(int) { cout << "Base::mf1(int)\n"; }
		void mf2();
	};

	class Derived : private Base {
	public:
		virtual void mf1() { Base::mf1(); }
	};

	void func() {
		Derived d;
		int value = 0;

		d.mf1();	//���� ���� Derived::mf1() -> Base::mf1() ȣ��
		//d.mf1(value);	//���� Derived::mf1() �� Base::mf1(int)�� ������

		/*
			public ��Ӱ� �޸� private ����� �� �� using �������� �ذ� �Ұ�
			using ������ ������ �� �̸��� �ش��ϴ� �͵��� ��� �Ļ� Ŭ������ ������ ������ ����
			-> private ����� �ǹ̰� �������
		*/
	}
}