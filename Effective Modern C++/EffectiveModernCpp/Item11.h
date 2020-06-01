#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ǵ��� ���� ����� �Լ����� ������ �Լ��� ��ȣ�϶�

namespace Item11 {

	namespace Case1 {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }

		private:
			Widget(const Widget& rhs); //c++ 98 ���� �Լ��� ȣ������ ���ϵ��� ���� ���, private ���� �� ���Ǹ� ��������.
		};
	}
	
	namespace Case2 {
		class Widget {
		public:
			Widget() { cout << "default ctor" << endl; }
			Widget(const Widget& rhs) = delete;
			/*
				c++ 11 ���� ���Ե� �Լ� ���� ���

				�����Ϸ��� ���� �Լ� ���� ���θ� Ȯ���ϴ� ����� ���̰� �־, ���������ڸ� public���� �����ϴ°��� ����.
				private ��� ���� �Ұ����ϴٰ� ������ �����ϴ� �����Ϸ��� �ִ�.
			*/
		};

		//�����ε����� ���밡��
		bool IsLucky(int num) { return true; }
		bool IsLucky(bool) = delete;
		bool IsLucky(char) = delete;
		bool IsLucky(double) = delete;	//double�� float(�� ��ȯ �� double) �� ����
	}

	namespace Case3{
		//���ø����� ���밡��
		class Widget {
		public:
			template<typename T>
			void processPointer(T* ptr) { 
				cout << typeid(T*).name() << endl; 
			}

			template<>
			void processPointer<void>(void*) = delete;
			template<>
			void processPointer<const void>(const void*) = delete;

		private:
			/*
				å������ c++ 98 ������� ����Լ� ���ø� ȣ���� ������ �Ҷ� ������ ������ �߻��Ѵٰ� ��޵�����
				���� ���⼭�� ������ ����

				���ø� Ư��ȭ�� Ŭ���� ���� ������ �ƴ� ���ӽ����̽� ���� �������� �ۼ��ؾ� �ϱ� ������ ������ �߻��Ѵٰ� ����Ǿ���.
			*/
			template<>
			void processPointer<char>(char*);
		};
	}

	inline void RunSample() {

		bool l0 = Case2::IsLucky(10);
		//bool l1 = Case2::IsLucky(false);		//������ �Լ��� ȣ�� �Ұ���
		//bool l2 = Case2::IsLucky('A');		//������ �Լ��� ȣ�� �Ұ���
		//bool l3 = Case2::IsLucky(0.5f);		//������ �Լ��� ȣ�� �Ұ���
		//bool l4 = Case2::IsLucky(3.0);		//������ �Լ��� ȣ�� �Ұ���

		Case3::Widget g;
		g.processPointer(static_cast<int*>(nullptr));
		g.processPointer(static_cast<float*>(nullptr));
		g.processPointer(static_cast<double*>(nullptr));
		//g.processPointer(static_cast<char*>(nullptr));	//����� �Լ� ȣ�� �Ұ���
		//g.processPointer(static_cast<void*>(nullptr));	//������ �Լ��� ȣ�� �Ұ���
	}
}