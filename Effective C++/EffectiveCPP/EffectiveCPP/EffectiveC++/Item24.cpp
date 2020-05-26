#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item24 {
	//Ÿ�� ��ȯ�� '��� �Ű�����'�� ���� ����Ǿ�� �Ѵٸ� ���� �Լ��� ��������

	class Rational {	//���� ������ �����ϴ� ������ Ŭ����
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
		result = r1 * 2;			//����	-> 2�� ������ ��ü�� �Ͻ��� ��ȯ����, ���� explicit���� ����Ǿ� �Ͻ��� ��ȯ�� �Ұ����ϸ� ������ ����
		//result = 2 * r1;			//�Ұ���	-> 2.operator*(r1) �� �����ϴ� �Լ��� �������� �ʱ� ����
	}
}

namespace Item24_2 {
	class Rational {	//��� operator* �� ���� ����
	public:
		Rational(int n = 0, int d = 1) : numerator(n), denominator(d) {}

		int Numerator() const { return numerator; }
		int Denominator() const { return denominator; }

	private:
		int numerator;
		int denominator;
	};

	const Rational operator*(const Rational& lhs, const Rational& rhs) {	//���� �Լ�
		return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
	}

	void func() {
		Rational r1(1, 8);
		Rational r2(1, 2);

		Rational result = r1 * r2;	//����
		result = r1 * 2;			//����
		result = 2 * r1;			//����	-> �����Ϸ� ������ ��� ���ڿ� ���� �Ͻ��� Ÿ�� ��ȯ�� ����
	}
}