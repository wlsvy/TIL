#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//���� ������ ������ ������ �����϶�

namespace Item24 {

	class Widget {
	public:
		Widget() { }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
		~Widget() { }
	};

	void f(Widget&& w) {}	//������ ����

	template<typename T>
	void f(std::vector<T> && param) {}	//������ ����

	template<typename T>
	void f(T&& param) {} //������ ���� �ƴ�

	template<typename T>
	void ConstF(const T&& param) {}	//������ ����


	

	inline void RunSample() {
		Widget&& var1 = Widget();	//������ ����
		auto && var2 = var1;		//������ ���� �ƴ�

		ConstF(std::forward<Widget>(var1));
		//ConstF(var2);				//������ ����

		std::vector<int> vi;
		vi.push_back(10);
		/*
			push_back�� �Ű����� Ÿ���� T&& ������ ���� ������ �Ͼ�� �ʴ´�.
			vector Ŭ������ Ÿ�� T�� ������ �� �� ����Լ��� �Ű����� Ÿ�� ���� �����Ǿ������ ����.

			emplace_back �� ���� ���� ������ �Ͼ��.
		*/
	}
}