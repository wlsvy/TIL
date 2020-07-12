#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

//������ ������ �ľ��ϴ� ����� �˾Ƶζ�

namespace Item04 {
	
	const int theAnswer = 42;

	auto x = theAnswer;		//int
	auto y = &theAnswer;	//const int *

	template<typename T>
	void f(const T& param) {
		cout << "T = " << typeid(T).name() << endl;
		cout << "param = " << typeid(param).name() << endl;
	}

	class Widget{};

	inline void RunSample() {
		cout << typeid(x).name() << endl;
		cout << typeid(y).name() << endl;

		Widget w;
		f(w);
		/*
			T = Widget
			param = Widget
		*/

		const vector<Widget> vw(1, Widget());
		f(&vw[0]);
		/*
			T = const Widget *
			param = const Widget *

		*/


		/*
			param Ÿ�԰� T Ÿ���� �����ϰ� ��Ÿ����. param�� Ÿ���� �и� const & T ���� const & �� ���Ե��� �ʴ´�.

			��Ȯ�� ���ϸ� �ι�° ���ÿ��� param Ÿ�� const Widget* const & ���� const & �� ���Ե��� �ʴ´�.

			c++ ǥ�ؿ� ������ std::type_info::name �� �ݵ�� �־��� ������ ��ġ ���ø� �Լ��� �� ���� �Ű������μ� ���޵� ��ó�� ����ؾ� �Ѵ�.
			�� �׸�1 ���� ���ø� Ÿ�� ���� �������� ������(&)�� ���õǰ�, ������ ������ �� ������ const(Ȥ�� volatile) �̸� const(Ȥ�� volatile)�� ���� ���õȴ�.

			�� std::type_info::name ������ ���� ������ �ʴ�.

			boost�� Boost.TypeIndex�� Ȱ���ϸ� ��Ȯ�� Ÿ�� ������ ���� �� �ִ�.

		*/
	}
}
