#include <iostream>

//��� ���Ͽ� �Լ� ����/���Ǹ� ���ÿ� �ϸ� LNK2005 ���� �߻� -> inline Ű���� ������ ��.
//Ŭ���� ����Լ��� ��� ���Ͽ� ����/�����ϸ� �Ͻ������� inline ����Ǳ� ������ inline Ű���尡 ��� ������ ����

#include "Item07.h"
#include "Item08.h"
#include "Item09.h"
#include "Item10.h"
#include "Item11.h"
#include "Item12.h"
#include "Item13.h"
#include "Item14.h"

using namespace std;


int main() {
	cout << "Hello world" << endl;

	//Item01::ParamType_Function::RunSample();
	//Item07::OtherCase::RunSample();
	//Item09::RunSample();
	//Item10::RunSample();
	//Item10::Scoped::RunUserInfoSample();
	//Item10::Unscoped::RunUserInfoSample();
	//Item11::RunSample();
	//Item12::RunSample();
	//Item13::RunSample();
	Item14::RunSample();

	system("pause");
	return 0;
}

/*

#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

	namespace Item00{

		inline void RunSample(){

		}
	}
*/

/*
	class Widget {
	public:
		Widget() { cout << "default ctor" << endl; }
		Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
		Widget(Widget&& rhs) { cout << "move ctor" << endl; }
		~Widget() { cout << "dtor" << endl; }

		Widget& operator=(const Widget& rhs) 
		{ 
			*this = rhs; 
			cout << "operator =" << endl;

			return *this; 
		}

		//operator int() const { return 0; }
		//operator float() const { return 0.0f; }
	};
*/