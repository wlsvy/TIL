#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

//���� �Լ� ��� �� �͵鵵 ��� ������ �δ� �ڼ��� �ýö����� �淯 ����

namespace Item35 {
	//�񰡻� �������̽� ���뱸(NVI)�� ���� ���
	class GameCharacter {
	public:
		int healthValue() const {	//wrapper �Լ�
			return calHealthValue();
		}

	private:
		virtual int calHealthValue() const { return 0; }
	};

	class GameCharacterDerived : public GameCharacter {
	private:
		int calHealthValue() const override { return 1; }
	};

	/*
		��ü���� ����(calHealthValue)�� private �����Լ��� �����Ͽ� �Ļ�Ŭ�������� �����Ǹ� �� �� �ֵ��� ����

		����ڷ� �Ͽ��� public �񰡻� ��� �Լ��� ���� private ���� �Լ��� ���������� ȣ���ϰ� ����� ���
		���� �����ڰ� private ������ �����Լ��� ���� ȣ������ �ʱ� ������ ������ ���� �ʴ´�.
	*/
}

namespace Item35_2 {
	//�Լ� �����͸� Ȱ���� ���� ����

	class GameCharacter; //���� ����

	int defaultHealthCalc(const GameCharacter& gc);	//����� ���� ü�� ��� ���� ����
	int loseHealthQuickly(const GameCharacter& gc);
	int loseHealthSlowly(const GameCharacter& gc);

	class GameCharacter {
	public:
		typedef int(*HealthCalcFunc) (const GameCharacter&);
		explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
		int healthValue() const { return healthFunc(*this); }
	private:
		HealthCalcFunc healthFunc;
	};

	class EvilBadGuy : public GameCharacter {
	public:
		explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc) : GameCharacter::GameCharacter(hcf) {}
	};

	void func() {
		EvilBadGuy ebg1(loseHealthQuickly);
		EvilBadGuy ebg2(loseHealthSlowly);
	}

	int defaultHealthCalc(const GameCharacter& gc) { return 0; }
	int loseHealthQuickly(const GameCharacter& gc) { return 1; }
	int loseHealthSlowly(const GameCharacter& gc) { return 2; }
}

namespace Item35_3 {
	//std::function ���� ������ ���� ����

	/*
		std::function ������ ��ü�� �Լ�ȣ�⼺ ��ü(callable entity, �Լ� ������, �Լ� ��ü, ��� �Լ� ������ ��)�� ���� �� �ְ�,
		�̵� ��ü�� �־��� �������� ��� �ñ״�ó(���� ���ÿ����� <int(const GameCharacger&)>�� �ش�)�� ȣȯ�Ǵ� �Լ� ȣ�⼺ ��ü�� ���� �� �ִ�.

		ȣȯ(compatible)�ȴٴ� ���� ���ÿ��� �Լ� ȣ�⼺ ��ü�� �Ű����� Ÿ���� const GameCharacter& �� �Ͻ��� ��ȯ�� �����ϰų� �ش� Ÿ�� ��ü�̸�
		��ȯ Ÿ�� ���� int�� �Ͻ��� ��ȯ�� �����ϰų� �ش� Ÿ���� ���

		�Լ� ȣ�⼺ ��ü ���� : https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1
		�߰��� �Լ� ��ü�� - operator()�� �����Ǿ� �ִ� ��ü, �ش� ��ü�� ��ȣ �����ڸ� ���� ��ġ �Լ��� ȣ���ϵ� ����� �� �ִ�.
	*/

	class GameCharacter; //���� ����

	int defaultHealthCalc(const GameCharacter& gc) { return 1; }
	short calcHealth(const GameCharacter& gc) { return 2; }//��ȯ Ÿ���� int�� �ƴ� �Ϳ� �ָ� -> short�� int�� �Ͻ��� ��ȯ�� �����ϱ� ������ ȣȯ������ �Լ�ȣ�⼺ ��ü
	struct HealthCalculator {
		int operator() (const GameCharacter&) const { return 3; }
	};
	class HealthCalculator2 {
	public:
		float calHealth(const GameCharacter&) const { return 4; }
	};

	class GameCharacter {
	public:
		//HealthCalcFunc �� �Լ� ȣ�⼺ ��ü�μ�, GameCharacter�� ȣȯ�Ǵ�
		//� ���̵� �Ѱܹ޾Ƽ� ȣ���� �� ������, int�� ȣȯ�Ǵ� ��� Ÿ���� ��ü�� ��ȯ�Ѵ�.
		typedef std::function<int(const GameCharacter&)> HealthCalcFunc;

		explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
		int healthValue() const { return healthFunc(*this); }
	private:
		HealthCalcFunc healthFunc;
	};

	void func() {
		HealthCalculator2 hc;

		GameCharacter gc1(calcHealth);
		GameCharacter gc2(HealthCalculator());
		GameCharacter gc3 = GameCharacter(std::bind(&HealthCalculator2::calHealth, hc, gc3));
	}
}

//�������� ���� ����
namespace Item35_4 {
	class GameCharacter;

	class HealthCalcFunc {
	public:
		virtual int calc(const GameCharacter& gc) const { return 0; }
	};

	HealthCalcFunc defaultHealthCalc;

	class GameCharacter {
	public:
		explicit GameCharacter(HealthCalcFunc *hcf = &defaultHealthCalc) : healthFunc(hcf) {}
		int healthValue() const { return healthFunc->calc(*this); }
	private:
		HealthCalcFunc *healthFunc;
	};
}