#include <iostream>
#include <vector>
#include <string>
using namespace std;

//타입 변환이 바람직할 경우에는 비멤버 함수를 클래스 템플릿 안에 정의해 두자

namespace Item46 {

	template<typename T>
	class Rational {
	public:
		Rational(const T& n = 0, const T& d = 1) :
			numerator(n), denominator(d) {}

		const T Numerator() const { return numerator; }
		const T Denominator() const { return denominator; }

	private:
		T numerator;
		T denominator;
	};

	template<typename T>
	const Rational<T> operator*(const Rational<T> & lhs, const Rational<T> & rhs) {
		return Rational<T>(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
	}

	void func() {
		Rational<int> oneHalf(1, 2);

		/*
			컴파일 에러, Rational<T>를 매개변수로 갖는 operator* 에서
			컴파일러는 T를 어떻게 인스턴스화해야 할 지 알 수 없다.
			첫 번째 매개 변수는 문제없지만, 두 번째 int 2 를 어떻게 Rational<T>로 변환시켜야 할지 모른다.

			int 를 Rational<T>로 암시적 변환시킬 수 있지 않을까 추측해볼 수 있지만,
			일반 함수가 아닌 템플릿 함수에서는 템플릿 인자 추론(template argument deduction) 과정에 따르는데
			여기서는 암시적 타입 변환이 고려되지 않는다.
		*/
		//Rational<int> result = oneHalf * 2;
	}
}

namespace Item46_2 {

	template<typename T>
	class Rational {
	public:
		Rational(const T& n = 0, const T& d = 1) :
			numerator(n), denominator(d) {}

		const T Numerator() const { return numerator; }
		const T Denominator() const { return denominator; }

	private:
		T numerator;
		T denominator;

		/*
			friend 키워드를 붙일 시 해당 함수는 클래스 안에 선언되어 있어도 비멤버 함수가 된다.(접근지정자 public/private에 상관없이 외부에서도 접근가능)
			위 방식으로 작성한다면 operator*는 템플릿 함수가 아니라 일반 함수로 여겨진다.
			=> 왜냐하면 템플릿이 타입마다 인스턴스화 될 때마다 operator* 함수도 타입 T에 따라 찍혀져 나오기 때문

			-> 템플릿 인자 추론 과정을 따르지 않으므로 암시적 생성자 호출이 가능하다.

			* 그리고 선언과 정의를 따로 분리하지 말것. 정의가 다른곳에 있으면 컴파일은 가능해도 링킹이 안될 수 있다.
		*/
		friend const Rational operator*(const Rational<T> & lhs, const Rational<T> & rhs) {
			return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
		}
	};

	void func() {
		Rational<int> oneHalf(1, 2);

		Rational<int> result = oneHalf * 2; //컴파일에러도 링킹에러도 없다.
	}
}

namespace Item46_3 {

	template<typename T>
	class Rational {
	public:
		Rational(const T& n = 0, const T& d = 1) :
			numerator(n), denominator(d) {}

		const T Numerator() const { return numerator; }
		const T Denominator() const { return denominator; }

	private:
		T numerator;
		T denominator;

		friend const Rational operator*(const Rational<T> & lhs, const Rational<T> & rhs) {
			/*
				비멤버 함수에서는 도우미 함수 호출 
				-> Rational<T>의 정체는 비멤버 함수가 추론하므로
				내부에서 호출되는 템플릿 함수는 매개변수의 타입을 추측할 필요가 없다.
			*/
			return doMultiply(lhs, rhs);	
		}
	};

	//도우미 함수의 활용	-> 템플릿 함수
	template<typename T>
	const Rational<T> doMultiply(const Rational<T> & lhs, const Rational<T> & rhs) {
		return Rational<T>(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
	}

	void func() {
		Rational<int> oneHalf(1, 2);

		Rational<int> result = oneHalf * 2;
	}
}