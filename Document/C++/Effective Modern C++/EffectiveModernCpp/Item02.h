#pragma once
#include <iostream>
#include <vector>
#include <string>


//auto ���� ���� ��Ģ�� �����϶�

namespace Item02 {
	using namespace std;

	template<typename T>
	void f(T param) {
		cout << param.size() << endl;
	}
	template<typename T>
	void f2(initializer_list<T> param) {
		cout << param.size() << endl;
	}

	inline void someFunc(int, double) {}

	inline void RunSample() {
		auto x = 27;			//int
		const auto cx = x;		//const int
		const auto & rcx = x;	//const int&
		auto x2 = cx;			//int

		//universal reference
		auto&& uref1 = x;		//int&
		auto&& uref2 = cx;		//const int&
		auto&& uref3 = 27;		//int&&

		//array
		const char name[] = "R. N. Briggs";

		auto arr1 = name;		//const char*
		auto& arr2 = name;		//const char(&)[13]

		//function
		auto func1 = someFunc;	//void (*)(int, double)
		auto& func2 = someFunc;	//void (&)(int, double)

		//initializer
		auto x1 = 27;			//int
		auto x2(27);			//int

		//Uniform initialization ���� �ʱ�ȭ
		auto x3 = { 27 };		//std::initializer_list<int>
		auto x4{ 27 };			//std::initializer_list<int>

		//auto x5 = { 1, 2, 3.0 }; ����, ���� �Ұ�

		//Passing Initializer List
		auto v = { 1, 2, 3 };
		f(v);	//���� ����
		//f({ 1, 2, 3 }); ����, T�� ���� ������ ������ �� ����

		f2(v);
		f2({ 1, 2, 3 });

		/*
			auto ���İ� template ���� ������ �������� ���̴� 
			
			auto�� �߰�ȣ �ʱ�ġ�� std::initializer_list�� ��Ÿ���ٰ� ����������
			���ø� ������ �׷��� �ʴٴ� ��
		*/

		//lambda
		vector<int> v2;
		auto resetV =
			[&v2](const auto& newValue) { v2 = newValue; };
		resetV(vector<int>({ 1, 2, 3 }));
		//resetV({ 1, 2, 3 }); ����
	}

	

	

	/*
	�� ��

	auto createInitList() {
		return { 1, 2, 3 };
	}

	����, ��ȯ�� auto Ÿ���� ������ �� ����
		
	*/
}

