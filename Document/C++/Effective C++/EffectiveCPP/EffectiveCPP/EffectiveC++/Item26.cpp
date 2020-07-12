#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���� ���Ǵ� ���� �� �ִ� ������ ���ߴ� �ټ��� ��������

namespace Item26 {

	//���� 1 - ��й�ȣ�� ����� �� �� �ش� ��й�ȣ�� ��ȣȭ�ϴ� �Լ�

	void encrypt(std::string& s) {} // ��й�ȣ ��ȣȭ

	//Before
	std::string encryptPassword_0(const std::string &password) {
		std::string encrypted;	//��� �ñ⺸�� ���� ����
		const int MininmumPasswordLength = 7;

		if (password.length() < MininmumPasswordLength) {
			throw logic_error("Password is Too Short");
		}

		encrypted = password;	//���� �� ���� �����ϱ⺸�� ������ ���ÿ� ���� ������ �� �ִ�
		encrypt(encrypted);

		return encrypted;
	}

	//After
	std::string encryptPassword_1(const std::string &password) {
		const int MininmumPasswordLength = 7;

		if (password.length() < MininmumPasswordLength) {
			throw logic_error("Password is Too Short");
		}

		std::string encrypted(password);
		encrypt(encrypted);

		return encrypted;
	}

	//���� 2 - ����(for)��
	class Widget{
	public:
		Widget() {}
		Widget(int i) {}
		const Widget& operator=(const int& i) { return *this; }
	};

	void Loop() {
		const int n = 10;

		//A ���
		Widget w1;	//���� �ٱ��ʿ� �����ϴ� ���
		for (int i = 0; i < n; i++) {
			w1 = i;
		}

		//B ���
		for (int i = 0; i < n; i++) {
			Widget w2(i);	//���� ���ʿ� �����ϴ� ���
		}

		/*
			A��� : ������ 1�� + �Ҹ��� 1�� + ���� n ��
			B��� : ������ n�� + �Ҹ��� n��

			A����� ���� ���� �ٱ��� ����� ���� ��ȿ������ B ��� ���� �о����� ������ ������������ ������ ��ĥ �� �ִ�.
			���ɿ� ũ�� ������ ��ġ�� �ʴ´ٸ� B ����� ����.
		*/
	}
}