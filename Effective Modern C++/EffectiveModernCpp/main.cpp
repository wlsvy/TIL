#include <iostream>

//��� ���Ͽ� �Լ� ����/���Ǹ� ���ÿ� �ϸ� LNK2005 ���� �߻� -> inline Ű���� ������ ��.
//Ŭ���� ����Լ��� ��� ���Ͽ� ����/�����ϸ� �Ͻ������� inline ����Ǳ� ������ inline Ű���尡 ��� ������ ����

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