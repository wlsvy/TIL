#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//������ �Լ����� override�� �����϶�

namespace Item12 {

	/*
		�����Ǹ� ���� �ʿ��� ����
		1. ��� Ŭ���� �Լ��� �ݵ�� ���� �Լ��̾�� �Ѵ�
		2. ��� �Լ��� �Ļ� �Լ��� �̸��� �ݵ�� �����ؾ� �Ѵ�
		3. ��� �Լ��� �Ļ� �Լ��� �Ű����� ���ĵ��� �ݵ�� �����ؾ� �Ѵ�.
		4. ��� �Լ��� �Ļ� �Լ��� const ���� �ݵ�� �����ؾ� �Ѵ�
		5. ��� �Լ��� �Ļ� �Լ��� ��ȯ ���İ� ���� ��(exception sepcification)�� �ݵ�� ȣȯ�Ǿ�� �Ѵ�.

		c++ 11���� �Ѱ��� �߰�
		6. ��� �Լ����� ���� ������(reference qualifier)���� �����ؾ� �Ѵ�.
	*/

	

	namespace WithoutOverride {
		//����Լ��� ������ ���� �ʴ� ���, ������ �������� ��������
		class Base {
		public:
			virtual void mf1() const {}
			virtual void mf2(int x) {}
			virtual void mf3() & {}
			void mf4() const {}
		};

		class Derived : public Base {
		public:
			virtual void mf1() {}	//const ���� ����
			virtual void mf2(unsigned int x) { }	//�Ű������� int �� �ƴ϶� unsigned int
			virtual void mf3() && {}	//���� �����ڰ� �ٸ�
			virtual void mf4() {}		//��� Ŭ������ virtual Ű���尡 ����
		};
	}

	namespace WithOverride {
		class Base {
		public:
			virtual void mf1() const {}
			virtual void mf2(int x) {}
			virtual void mf3() & {}
			void mf4() const {}
		};

		class Derived : public Base {
		public:
			/*
				c++11 ���� ���Ե� override Ű���带 ����ϸ� ������ ���� ���������� �������ش�.

				�Ʒ��� ������ �Ұ���
				virtual void mf1() override {}
				virtual void mf2(unsigned int x) override { }
				virtual void mf3() && override {}
				virtual void mf4() override {}
			*/
				
			//������ ����
			virtual void mf1() const override {}
			virtual void mf2(int x) override { }
			virtual void mf3() & override {}
		};
	}

	class Widget {
	public:
		static Widget MakeWidget() { return Widget(); }
		
		Widget() { cout << "default ctor" << endl; }
		Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
		Widget(Widget&& rhs) { cout << "move ctor" << endl; }

		//���� �����ڴ� ��ü�� ������/�������� ���� ���� ����� ���ѽ�ų �� �ִ�.

		vector<int>& GetData() & {
			cout << "Get lvalue Data" << endl; 
			return m_Data;
		}		//*this�� �������� ���� ���ȴ�.

		vector<int>&& GetData() && {
			cout << "Get rvalue Data" << endl;
			return std::move(m_Data);
		}		//*this�� �������� ���� ���ȴ�.

	private:
		vector<int> m_Data;
	};

	inline void RunSample() {
		Widget w;
		auto val1 = w.GetData();					//"Get lvalue Data"
		auto val2 = Widget::MakeWidget().GetData();	//"Get rvalue Data"
	}
}