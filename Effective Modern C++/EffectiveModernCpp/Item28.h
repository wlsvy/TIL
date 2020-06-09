#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//���� ��� (reference collapsing) �� �����϶�

namespace Item28 {
	/*
		���� ���(collapse)�� 

		���ø� �ν��Ͻ�ȭ, 
		auto Ÿ�� �߷�, 
		typedef�� ��Ī ������ ���� �� ���, 
		decltype�� ���� �� ���
		
		�� ���� ���ƿ��� �Ͼ��.
	*/

	class Widget {
	public:
		static Widget Create() { return Widget(); }
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
	};

	template<typename T>
	decltype(auto) f(T&& val) {
		using RefToType1 = T & ;	//Ÿ�� ��Ī ���𿡵� ���� ��� ����
		using RefToType2 = T && ;

		std::cout << typeid(T).name() << std::endl;
		return std::forward<T>(val);
	}

	inline void RunSample() {
		int x = 0;
		auto && rx = x;
		//auto& && rx2 = x;	//������ ����, ������ ���� ����

		decltype(auto) r = f(x);	//T : int&, paramType : int& && -> int& (�������)
		decltype(auto) r1 = f(3);	//T : int,  paramType : int&&
		decltype(auto) r2 = f(rx);	//T : int&, paramType : int& && -> int& (�������)
		


		Widget w;
		auto && w1 = w;		//Widget&
		/*
			auto&& => Widget& && => Widget& (�������)
		*/

		auto && w2 = Widget::Create();	//Widget&&
		/*
			auto&& => Widget&& (���� �� ������ ����)
		*/
	}

	/*
		�߰��� decltype ������ ���� ����� �߻��Ѵ�. 
		�����Ϸ��� decltype�� �����ϴ� ������ �м��ϴ� ���߿� ������ ���� ������ �߻��ϸ� ���� ����� ������ �װ��� �����Ѵ�.
	*/

	/*
		������ �� ����(�������� ������)�̹Ƿ�, ������ ���� ������ ������ ������ �� �� �����̴�
		(�������� ���� ������, �������� ���� ������, �������� ���� ������, �������� ���� ������). 
		������ ���� ������ ���Ǵ� ���ƿ��� ������ ���� ������ ���� ��Ģ�� ���� �ϳ��� ������ ���ȴ�(collapse).

		���� �� ���� �� �ϳ��� ������ �����̸� ����� ������ �����̴�. �׷��� ������(��, �� �� ������ �����̸�) ����� ������ �����̴�.
	*/

	/*
		�ٽ� Ȯ������ �� ���� ����(universal reference)�� ��ǻ� ������ �����̴�.

		1. Ÿ�� �߷п��� �������� �������� ���еȴ�. T Ÿ���� �������� Ÿ�� T&�� �߷еǰ�, T Ÿ���� �������� Ÿ�� T�� �߷еȴ�.
		2. ���� ���(collapse)�� ����ȴ�.
	*/
}