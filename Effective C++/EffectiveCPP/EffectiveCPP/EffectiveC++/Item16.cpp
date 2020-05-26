#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item16 {
	//new �� delete�� ����� ���� ���¸� �ݵ�� ������

	void Func() {
		std::string *stringArr = new std::string[100];

		delete stringArr; // �迭 �߿��� �� ó�� string �� ��ȯ�ǰ� ������ 99���� �״�� ��ġ�� ���ɼ��� ũ��!!
	}

	void Func2() {
		std::string *stringPtr1 = new std::string;
		std::string *stringPtr2 = new std::string[100];

		delete stringPtr1;	//��ü �� �� ����	
		delete[] stringPtr2;//��ü�� �迭 ����

		/*
			[] �����ڸ� ������� ��, delete�� ���� �迭�� ũ�⸦ ���� �а�
			(�����Ϸ� ���� �ٸ����� ���� �迭�� �� �պκп� ��ġ�Ѵٰ� �Ѵ�)

			�迭 ũ�⿡ �ش��ϴ� Ƚ����ŭ �Ҹ��ڸ� ȣ���Ѵ�.
			��, [] �����ڷ� ¦�� ������ �ʴ´ٸ� ������ ������ �߻��Ѵ�.
		*/
	}

	void Func3() {
		//������ ��
		using AddressLines = std::string[4];

		std::string *pal = new AddressLines;	//��� �迭 ������ �ƴ�����
		delete[] pal;	//pal�� ����Ű�� ��ü�� �迭��ü�̴�.
	}
}