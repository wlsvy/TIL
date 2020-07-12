#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//��ü ���� �� ��ȣ '()' �� �߰�ȣ '{}' �� �������� 

namespace Item07 {

	/*
		���� �ʱ�ȭ(uniform initialization)�� c++11 ���� ���ԵǾ�����,

		��𼭳� ��� �� �� �ְ�, ��� ���� ǥ���� �� �ִ�(��������δ�) �� �� ������ �ʱ�ȭ �����̴�.


		���� �ʱ�ȭ ������ 
		1. �߰�ȣ�� ����Ѵ�.
		2. ������ ��ȯ(narrow conversion)�� �����Ѵ�.
	*/

	void TestNarrowConversion(){
		/*
			����ȯ�� �� �� �������� �Ϻΰ� �սǵȴٸ� ������ ��ȯ(narrow conversion)
			Ex) float -> int : �Ҽ��� �κ��� int�� ��ȯ�Ǹ鼭 �սǵȴ�.

			�߰�ȣ �ʱ�ġ�� �ִ� � ǥ������ ���� �ʱ�ȭ�Ϸ��� ��ü�� �������� �����ϰ� ǥ���� �� ������ ������� ������ �����Ϸ��� �� ����� �����ؾ� �Ѵ�.
		*/

		int i0 = 0, i1 = 0, i2 = 0;
		double d0 = 0, d1 = 0, d2 = 0;

		int sum0{ i0 + i1 + i2 };
		//int sum1{ d0 + d1 + d2 };	//����, double ���� int�� ��ȯ�ҷ��� ��� ��ȯ�� �ʿ��ϴ�.

		int sum2(d0 + d1 + d2); // ���� ����, ������� int�� �°� �߷�������.
		int sum3 = d0 + d1 + d2; // ��������
	}

	namespace DefaultCase {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(int i, bool b) { cout << "ctor (int, bool)" << endl; }
			Widget(int i, double d) { cout << "ctor (int, double)" << endl; }

		};

		inline void RunSample() {
			Widget w1(10, true);	//ctor (int, bool)
			Widget w2{ 10, true };	//ctor (int, bool)

			Widget w3(10, 5.0);		//ctor (int, double)
			Widget w4{ 10, 5.0 };	//ctor (int, double)
		}
	}

	namespace WithInitializerList {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
			Widget(Widget&& rhs) { cout << "move ctor" << endl; }
			Widget(int i, bool b) { cout << "ctor (int, bool)" << endl; }
			Widget(int i, double d) { cout << "ctor (int, double)" << endl; }
			Widget(std::initializer_list<long double>) { cout << "ctor (initializer_list<long double>)" << endl; }

			operator float() const { return 0.0f; }

		};

		inline void RunSample() {
			Widget w1(10, true);		//ctor (int, bool)
			Widget w2{ 10, true };		//ctor (initializer_list<long double>) -> 10, true �� long double �� ��ȯ

			Widget w3(10, 5.0);			//ctor (int, double)
			Widget w4{ 10, 5.0 };		//ctor (initializer_list<long double>)  -> 10, 5.0 �� long double �� ��ȯ

			Widget w5(w4);				//copy ctor
			Widget w6(std::move(w4));	//move ctor

			Widget w7{ w4 };			
			Widget w8{ std::move(w4) };	
			/*
				å���� 
				ctor (initializer_list<long double>) ���� -> w4�� float ���� ����ȯ ����, �ٽ� long double�� ��ȯ

				��� ���������� ���� �����ϸ� ����/�̵������ڰ� ȣ��ȴ�.

				å�� ���� ������ �����Ϸ��� �߰�ȣ �ʱ�ġ�� initializer_list �� ������Ű�� ��츦 �ֿ켱���� Ȯ���ϱ� ������
				����/�̵� �����ں��� ctor (initializer_list<long double>) �� �켱�õǴٴ� ��
			*/
		}
	}

	namespace OtherCase {
		class CtorWithBool {
		public:
			CtorWithBool(bool b, double d) { cout << "ctor (bool, double)" << endl; }
			CtorWithBool(std::initializer_list<bool>) { cout << "ctor (initializer_list<bool>)" << endl; }
		};

		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(int i, bool b) { cout << "ctor (int, bool)" << endl; }
			Widget(int i, double d) { cout << "ctor (int, double)" << endl; }
			Widget(std::initializer_list<string>) { cout << "ctor (initializer_list<string>)" << endl; }
		};

		inline void RunSample() {
			//CtorWithBool w{ true, 0.5 };	//����, float -> bool�� ��Һ�ȯ�� �߻��Ѵ�.

			Widget w1(10, true);		//ctor (int, bool)
			Widget w2{ 10, true };		//ctor (int, bool)

			Widget w3(10, 5.0);			//ctor (int, double)
			Widget w4{ 10, 5.0 };		//ctor (int, double)
			/*
				int, double, bool �� string���� �Ͻ�����ȯ�� �Ұ����ϱ� ������ 
				ctor (initializer_list<string>) �� ������� �ʴ´�.
			*/

			Widget w5;					//default ctor
			Widget w6{};				//default ctor, ����ִ� �߰�ȣ�� '�μ� ����'�� �ǹ��Ѵ�
			Widget w7();				//�Լ� ����. ��ü�� �������� �ʴ´�.

			//����ִ� initializer_list �����ϴ� ���

			Widget w8({});				//ctor (initializer_list<string>) -> �� �ʱ�ġ ����Ʈ�� �Ű������� ����
			Widget w9{{}};				//ctor (initializer_list<string>) -> �� �ʱ�ġ ����Ʈ�� �Ű������� ����
			
			vector<int> v0(10, 20);		//���� 20�� ���Ұ� 10�� �ִ� ���� ����
			vector<int> v1{ 10, 20 };	//���� 10, 20�� ���� 2���� �ִ� ���� ����

		}
	}
}