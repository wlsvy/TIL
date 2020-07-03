#include <iostream>
#include <vector>
#include <string>
using namespace std;

//변수 정의는 늦출 수 있는 데까지 늦추는 근성을 발휘하자

namespace Item26 {

	//예시 1 - 비밀번호가 충분히 길 때 해당 비밀번호를 암호화하는 함수

	void encrypt(std::string& s) {} // 비밀번호 암호화

	//Before
	std::string encryptPassword_0(const std::string &password) {
		std::string encrypted;	//사용 시기보다 일찍 선언
		const int MininmumPasswordLength = 7;

		if (password.length() < MininmumPasswordLength) {
			throw logic_error("Password is Too Short");
		}

		encrypted = password;	//생성 후 값을 대입하기보다 생성과 동시에 값을 대입할 수 있다
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

	//예시 2 - 루프(for)문
	class Widget{
	public:
		Widget() {}
		Widget(int i) {}
		const Widget& operator=(const int& i) { return *this; }
	};

	void Loop() {
		const int n = 10;

		//A 방법
		Widget w1;	//루프 바깥쪽에 정의하는 방법
		for (int i = 0; i < n; i++) {
			w1 = i;
		}

		//B 방법
		for (int i = 0; i < n; i++) {
			Widget w2(i);	//루프 안쪽에 정의하는 방법
		}

		/*
			A방법 : 생성자 1번 + 소멸자 1번 + 대입 n 번
			B방법 : 생성자 n번 + 소멸자 n번

			A방법을 쓰면 루프 바깥에 선언된 변수 유효범위가 B 방법 보다 넓어지기 때문에 유지보수성에 영향을 끼칠 수 있다.
			성능에 크게 영향을 끼치지 않는다면 B 방법이 좋다.
		*/
	}
}