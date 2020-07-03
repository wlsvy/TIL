#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�Լ����� ��ü�� ��ȯ�ؾ� �� ��쿡 �����ڸ� ��ȯ�Ϸ��� ���� ����

namespace Item21 {
	
	class Rational {
	public:
		Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}
	private:
		int n, d;

		friend const Rational operator* (const Rational& rhs, const Rational& lhs);
		//const ��ü�� ��ȯ�ϴ� ������ a * b = c ���� ��츦 �����ϱ� ����.

		/*
			��ü�� ��ȯ Ÿ���� �������� �ʿ�� ����. 
			�Լ� ������ ������ ��ü�� ���ÿ� �ӽ������� ������ ���̰�
			�Լ��� �������ö� ������� ������, �����ڷ� �Ѱ��� �ּҴ� �ǹ̰� ���� �Ǵ� ��

			�Լ� �� ��ü ������ �Ҹ꿡 ���� ����� �Ű澲�� �� ������,
			��κ��� �����Ϸ������� operator �Լ� �� ������ �Ҹ��� ��뿡 ���ؼ� ����ȭ ��Ŀ������ ���õǾ� �ִ�.
			����� �Ƚ��ϰ� ����� �� �ִ� ����
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

			�Ǵ� 

			Rational *result = new Rational(...);
			return *result;
		}
	*/
	/*
		���� ���, ������ ������ ���ϰ� ������� ��Ÿ���� ��ü�� ��ȯ�Ϸ� �� ��, ��ȯ ��ü�� ���ÿ� �Ҵ��ϰ�, ���� �Ҵ��ϰ� ������ �����.
		������ ��� ���������� ������ �Լ��� ���������� ���� �����������,
		�� �Ҵ��� ���, new �� �Ҵ��� �޸𸮸� ���� delete ����� ���� å���� ���� �� ����.
	*/

}