#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item20 {
	//'���� ���� ����' ���ٴ� '�����ü �����ڿ� ���� ����' ����� ���ϴ� ���� �밳 ����
	
	class Person {
	public:
		string name;
		string address;
	};
	class Student : public Person {
	public:
		string schoolName;
		string schoolAddress;
	};

	bool validateStudent(Student s); //���� ���� ���� -> 
	//student �� �����ϴ� string ��ü 4��, �׸��� student,person �� ������ �Ҹ��� ����� �߰��� �δ��ؾ� �Ѵ�.

	bool validateStudent2(const Student& s);	//������ ���� ����. �ܼ��� ��ü�� �ּҸ� �����Ѵ�.
												//*���� ��ü�� ������ �������� �ʰڴٴ� �ǹ̿��� Ÿ�� �տ� const�� ���δ�

	/*
		Ÿ�� ũ�⸸ ������ '���� ���� ����' �� �����ϴٴ� ������ Ʋ�� ����
		�⺻ ���� Ÿ��, STL �ݺ���, �Լ� ��ü Ÿ�� �� �� ������ �ƴϸ� ���� ���� ������ �ٽ� �����ؾ� �Ѵ�.

		�����Ϸ� �߿����� �Ϻ� �⺻���� Ÿ�԰� ����� ���� Ÿ���� ������ �ٸ��� �ٷ�� ��찡 �ִ�.
		�̸��׸� double Ÿ���� �������Ϳ� �־�������, double ��� �ϳ��� ������ ����� ���� Ÿ���� �������Ϳ� ���� ���� �� �ִ� ��
		���� ���������� Ȯ���ϴ�. �ּڰ��� �������Ϳ� Ȯ���� ����.
	*/

	bool validateStudent(Student s) { return false; }
	bool validateStudent2(const Student& s) { return false; }

}