#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Ÿ�� ��ȯ�� '��� �Ű�����'�� ���� ����Ǿ�� �Ѵٸ� ���� �Լ��� ��������

namespace Item24 {

	/*
		� �Լ��� ���� ��� �Ű�����(this �����Ͱ� ����Ű�� ��ü�� �����ؼ�)�� ���� Ÿ�� ��ȯ�� �� �� �ʿ䰡 �ִٸ�, �� �Լ��� �����̾�� �մϴ�.
	*/

	namespace Case0 {

		//���� ������ �����ϴ� ������ Ŭ����
		class Rational {
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

			Rational result = r1 * r2;	//����
			result = r1 * 2;	//����	-> 2�� ������ ��ü�� �Ͻ��� ��ȯ����, ���� explicit���� ����Ǿ� �Ͻ��� ��ȯ�� �Ұ����ϸ� ������ ����
			//result = 2 * r1;	//�Ұ���	-> 2.operator*(r1) �� �����ϴ� �Լ��� �������� �ʱ� ����
		}
	}
	
	namespace Case1 {
		//��� operator* �� ���� ����
		class Rational {	
		public:
			Rational(int n = 0, int d = 1) : numerator(n), denominator(d) {}

			int Numerator() const { return numerator; }
			int Denominator() const { return denominator; }

		private:
			int numerator;
			int denominator;
		};

		//���� �Լ�
		const Rational operator*(const Rational& lhs, const Rational& rhs) {	
			return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
		}

		void func() {
			Rational r1(1, 8);
			Rational r2(1, 2);

			Rational result = r1 * r2;	//����
			result = r1 * 2;	//����
			result = 2 * r1;	//����	-> �����Ϸ� ������ ��� ���ڿ� ���� �Ͻ��� Ÿ�� ��ȯ�� ����
		}
	}
}
