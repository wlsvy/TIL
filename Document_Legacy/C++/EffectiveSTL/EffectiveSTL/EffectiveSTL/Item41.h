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

//ptr_fun, mem_fun, mem_fun_ref�� ���翡�� �и��� ������ �ִ�

namespace Item41 {
	using namespace std;

	/*
		ptr_fun, mem_fun, mem_fun_ref ���� c++ 11 ���� deprecated �Ǿ����� c++ 17���� �����˴ϴ�.
	*/

	/*
		f�� �̸��� �Լ��� x�� �̸��� ��ü�� �ϳ� �ֽ��ϴ�. ���⼭ x�� ���� f�� ȣ���ϰ� ������, ȣ���ϴ� ��ġ�� x�� ��� �Լ��� �ٱ����Դϴ�. �̷� ��Ȳ���� C++�� ������ �� ���� ������ �����մϴ�.
		
		#1. f(x);
		f�� ��� �Լ��� �ƴ� ���
		
		#2. x.f();
		f�� x�� ��� �Լ��̰�, x�� ��ü�̵��� ��ü�� ���� �������� ���
		
		#3. p->f();
		f�� x�� ��� �Լ��̰�, p�� x ��ü�� ���� �������� ���

	*/

	class Widget {
	public:
		void DoSomething() { cout << "DoSomething\n"; }
	};
	
	inline void RunSample() {
		/*
			for_each�� ������ ��� �˰����� ���������� ���� #1���� ����մϴ�. 
			����, �˰��� ��� �Լ��� �Ѱ��ָ�(���� #2 Ȥ�� ���� #3�� ����ؾ� �ϴ� ���), �������� ���� �ʽ��ϴ�. 

			- c++ 11 ����
			��ó�� �˰��� ��� �Լ��� �Ѱ���� �ϴ� ��Ȳ���� mem_fun_ref(���� #2)�� mem_fun(���� #3)�� ����մϴ�.

			list<Widget*> lpw;
			for_each(lpw.begin(), lpw.end(), mem_fun(&Widget::test));
		*/
		
		//c++11 ����. ������ ���� �Լ��� �ذ��ع����ô�. �����彺���� ����ʹ� �Ű澵 �ʿ� �����ϴ�.
		vector<Widget> vw(3);
		for_each(vw.begin(), vw.end(), [](auto& w) {w.DoSomething(); });
	}
}