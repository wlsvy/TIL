#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>

//�������� ���� �뷮�� "�ٲ�ġ��(swap) ����"�� �Ἥ ���� ������

namespace Item17 {
	using namespace std;

	//c++11 ���� stl���� shrink_to_fit ����Լ��� �߰��Ǹ鼭 ���� �뷮�� ���� ������� ������� ���� �� �ֽ��ϴ�.

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }

		Widget& operator=(const Widget& rhs)
		{
			std::cout << "copy operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept
		{
			std::cout << "move operator =" << std::endl;
			return *this;
		}
	};

	inline void RunSample() {
		vector<Widget> v;
		v.reserve(10);

		for (int i = 0; i < 5; i++) {
			v.emplace_back();
		}

		cout << "===============" << endl;
		//���Ҵ��� �߻��Ѵٴ� ����� ����սô�.
		v.shrink_to_fit();

		cout << "===============" << endl;

	}
}