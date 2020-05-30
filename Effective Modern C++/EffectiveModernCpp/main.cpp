#include <iostream>

//헤더 파일에 함수 선언/정의를 동시에 하면 LNK2005 오류 발생 -> inline 키워드 삽입할 것.
//클래스 멤버함수를 헤더 파일에 선언/정의하면 암시적으로 inline 선언되기 때문에 inline 키워드가 없어도 문제는 없음

#include "Item05.h"

using namespace std;


int main() {
	cout << "Hello world" << endl;

	//Item01::ParamType_Function::RunSample();
	Item05::WithAuto::RunSample();

	system("pause");
	return 0;
}

/*
	namespace Item00{

		inline void RunSample(){

		}
	}
*/