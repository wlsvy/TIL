#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Ÿ�� ��ȯ�� �ٶ����� ��쿡�� ���� �Լ��� Ŭ���� ���ø� �ȿ� ������ ����

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
			������ ����, Rational<T>�� �Ű������� ���� operator* ����
			�����Ϸ��� T�� ��� �ν��Ͻ�ȭ�ؾ� �� �� �� �� ����.
			ù ��° �Ű� ������ ����������, �� ��° int 2 �� ��� Rational<T>�� ��ȯ���Ѿ� ���� �𸥴�.

			int �� Rational<T>�� �Ͻ��� ��ȯ��ų �� ���� ������ �����غ� �� ������,
			�Ϲ� �Լ��� �ƴ� ���ø� �Լ������� ���ø� ���� �߷�(template argument deduction) ������ �����µ�
			���⼭�� �Ͻ��� Ÿ�� ��ȯ�� ������� �ʴ´�.
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
			friend Ű���带 ���� �� �ش� �Լ��� Ŭ���� �ȿ� ����Ǿ� �־ ���� �Լ��� �ȴ�.(���������� public/private�� ������� �ܺο����� ���ٰ���)
			�� ������� �ۼ��Ѵٸ� operator*�� ���ø� �Լ��� �ƴ϶� �Ϲ� �Լ��� ��������.
			=> �ֳ��ϸ� ���ø��� Ÿ�Ը��� �ν��Ͻ�ȭ �� ������ operator* �Լ��� Ÿ�� T�� ���� ������ ������ ����

			-> ���ø� ���� �߷� ������ ������ �����Ƿ� �Ͻ��� ������ ȣ���� �����ϴ�.

			* �׸��� ����� ���Ǹ� ���� �и����� ����. ���ǰ� �ٸ����� ������ �������� �����ص� ��ŷ�� �ȵ� �� �ִ�.
		*/
		friend const Rational operator*(const Rational<T> & lhs, const Rational<T> & rhs) {
			return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
		}
	};

	void func() {
		Rational<int> oneHalf(1, 2);

		Rational<int> result = oneHalf * 2; //�����Ͽ����� ��ŷ������ ����.
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
				���� �Լ������� ����� �Լ� ȣ�� 
				-> Rational<T>�� ��ü�� ���� �Լ��� �߷��ϹǷ�
				���ο��� ȣ��Ǵ� ���ø� �Լ��� �Ű������� Ÿ���� ������ �ʿ䰡 ����.
			*/
			return doMultiply(lhs, rhs);	
		}
	};

	//����� �Լ��� Ȱ��	-> ���ø� �Լ�
	template<typename T>
	const Rational<T> doMultiply(const Rational<T> & lhs, const Rational<T> & rhs) {
		return Rational<T>(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
	}

	void func() {
		Rational<int> oneHalf(1, 2);

		Rational<int> result = oneHalf * 2;
	}
}