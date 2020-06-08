#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//std::move �� std::forward�� �����϶�

namespace Item23 {

	/*
		std::move�� ������������ ������ ĳ������ �����Ѵ�. std::move ��ü�� �ƹ��͵� �̵����� �ʴ´�.
		std::forward�� �־��� �μ��� �������� ���� ��쿡�� �װ��� ���������� ĳ�����Ѵ�.
		std::move�� std::forward �� ��, ������������� �ƹ� �ϵ� ���� �ʴ´�.
	*/

	namespace Case0 {
		/*
			�̵� �������� �Ű������� const�� �������� �� ��. �̵��� �ƴ� ���� �����ڸ� ȣ���Ѵ�. <= ���� ������� ���� �̵������ڰ� ȣ��Ǳ� �Ѵ�. ���� ��������� �������� ��������

			�̵� �����ڴ� �����δ� �ƹ��͵� �̵���Ű�� ���� �Ӹ� �ƴ϶�
			ĳ���� �Ǵ� ��ü�� �̵� �ڰ��� ���߰� �ȴٴ� ���嵵 �������� �ʴ´�.
		*/
		class Widget {
		public:
			Widget() { }
			Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
			Widget(const Widget&& rhs) { std::cout << "move ctor" << std::endl; }
			~Widget() { }
		};
	}

	namespace Case1 {
		class Widget {
		public:
			Widget() { }
			Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
			Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
			~Widget() { }
		};

		inline void Process(const Widget & w) {
			std::cout << "Lvalue Param" << std::endl;
		}
		inline void Process(Widget && w) {
			std::cout << "Rvalue Param" << std::endl;
		}
		template<typename T>
		inline void LogType(T&& param) {
			std::cout << "Type == " << typeid(decltype(param)).name() << std::endl;
			Process(param);	//�׻� ������ ����
			Process(std::forward<T>(param));	//������ ������ ����������, ������ ������ ����������
		}
	}

	



	inline void RunSample() {
		Case0::Widget w0;
		Case0::Widget w0_moveTest(std::move(w0));	//��������� ȣ��

		std::cout << "===================" << std::endl;


		Case1::Widget w1;
		Case1::Widget w1_moved(std::move(w1));

		Case1::LogType(w1);
		Case1::LogType(std::move(w1));
	}
}