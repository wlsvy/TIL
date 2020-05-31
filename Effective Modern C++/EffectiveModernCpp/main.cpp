#include <iostream>

//헤더 파일에 함수 선언/정의를 동시에 하면 LNK2005 오류 발생 -> inline 키워드 삽입할 것.
//클래스 멤버함수를 헤더 파일에 선언/정의하면 암시적으로 inline 선언되기 때문에 inline 키워드가 없어도 문제는 없음

#include "Item07.h"
#include "Item08.h"
#include "Item09.h"

using namespace std;


int main() {
	cout << "Hello world" << endl;

	//Item01::ParamType_Function::RunSample();
	//Item07::OtherCase::RunSample();
	Item09::RunSample();

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
	~Widget() {cout<<"dtor" << endl;}

	Widget& operator=(const Widget& rhs) { *this = rhs; return *this; }

	//operator int() const { return 0; }
	//operator float() const { return 0.0f; }
};
*/