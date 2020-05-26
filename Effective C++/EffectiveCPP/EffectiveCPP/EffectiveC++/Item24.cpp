#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item24 {
	//타입 변환이 '모든 매개변수'에 대해 적용되어야 한다면 비멤버 함수를 선언하자

	class Rational {	//곱셈 연산을 지원하는 유리수 클래스
	public:
		Rational(int n = 0, int d = 1) : numerator(n), denominator(d) {}

		const Rational operator* (const Rational& rhs) const {
			return Rational(numerator * rhs.numerator, denominator * rhs.denominator);
		}
	private:
		int numerator;
		int denominator;
	};

	void func() {
		Rational r1(1, 8);
		Rational r2(1, 2);

		Rational result = r1 * r2;	//가능
		result = r1 * 2;			//가능	-> 2는 유리수 객체로 암시적 변환가능, 만약 explicit으로 선언되어 암시적 변환이 불가능하면 컴파일 에러
		//result = 2 * r1;			//불가능	-> 2.operator*(r1) 에 대응하는 함수가 존재하지 않기 때문
	}
}

namespace Item24_2 {
	class Rational {	//멤버 operator* 가 없는 버전
	public:
		Rational(int n = 0, int d = 1) : numerator(n), denominator(d) {}

		int Numerator() const { return numerator; }
		int Denominator() const { return denominator; }

	private:
		int numerator;
		int denominator;
	};

	const Rational operator*(const Rational& lhs, const Rational& rhs) {	//비멤버 함수
		return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
	}

	void func() {
		Rational r1(1, 8);
		Rational r2(1, 2);

		Rational result = r1 * r2;	//가능
		result = r1 * 2;			//가능
		result = 2 * r1;			//가능	-> 컴파일러 측에서 모든 인자에 대해 암시적 타입 변환을 수행
	}
}