#include <iostream>
#include <vector>
#include <string>
using namespace std;

//함수에서 객체를 반환해야 할 경우에 참조자를 반환하려고 들지 말자

namespace Item21 {
	
	class Rational {
	public:
		Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}
	private:
		int n, d;

		friend const Rational operator* (const Rational& rhs, const Rational& lhs);
		//const 객체를 반환하는 이유는 a * b = c 같은 경우를 방지하기 위함.

		/*
			객체의 반환 타입이 참조자일 필요는 없다. 
			함수 내에서 생성된 객체는 스택에 임시적으로 존재할 뿐이고
			함수를 빠져나올때 사라지기 때문에, 참조자로 넘겨진 주소는 의미가 없게 되는 것

			함수 내 객체 생성과 소멸에 따른 비용이 신경쓰일 수 있지만,
			대부분의 컴파일러에서는 operator 함수 내 생성과 소멸의 비용에 대해서 최적화 매커니즘이 마련되어 있다.
			충분히 안심하고 사용할 수 있는 수준
		*/

		friend const Rational operator*(const Rational& rhs, const Rational& lhs) {
			return Rational();
		}

		friend const Rational  operator* (const Rational& rhs, const Rational& lhs);

	};

	/*
		const Rational & operator* (const Rational & lhs, const Rational & rhs) {
			Rational result(lhs.n * rhs.n, lhs.d * rhs.d); 
			return result;

			또는 

			Rational *result = new Rational(...);
			return *result;
		}
	*/
	/*
		위의 경우, 유리수 곱셈을 행하고 결과값을 나타내는 객체를 반환하려 할 때, 반환 객체를 스택에 할당하건, 힙에 할당하건 문제가 생긴다.
		스택의 경우 지역변수기 때문에 함수를 빠져나오는 순간 사라져버리고,
		힙 할당의 경우, new 로 할당할 메모리를 누가 delete 해줘야 할지 책임을 정할 수 없다.
	*/

}