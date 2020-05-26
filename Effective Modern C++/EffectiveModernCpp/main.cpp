#include <iostream>

//헤더 파일에 함수 선언/정의를 동시에 하면 LNK2005 오류 발생 -> inline 키워드 삽입할 것.
//#include "Item01.h"

using namespace std;


int main() {
	cout << "Hello world" << endl;

	//Item01::ParamType_Function::RunSample();

	system("pause");
	return 0;
}