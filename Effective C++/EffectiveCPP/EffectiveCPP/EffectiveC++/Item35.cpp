#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

//가상 함수 대신 쓸 것들도 대신 생각해 두는 자세를 시시때때로 길러 두자

namespace Item35 {
	//비가상 인터페이스 관용구(NVI)를 통한 방법
	class GameCharacter {
	public:
		int healthValue() const {	//wrapper 함수
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
		구체적인 동작(calHealthValue)은 private 가상함수로 선언하여 파생클래스에게 재정의를 할 수 있도록 제공

		사용자로 하여금 public 비가상 멤버 함수를 통해 private 가상 함수를 간접적으로 호출하게 만드는 방법
		접근 지정자가 private 이지만 가상함수를 직접 호출하지 않기 때문에 문제가 되지 않는다.
	*/
}

namespace Item35_2 {
	//함수 포인터를 활용한 전략 패턴

	class GameCharacter; //전방 선언

	int defaultHealthCalc(const GameCharacter& gc);	//방법에 따라 체력 계산 공식 변경
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
	//std::function 으로 구현한 전략 패턴

	/*
		std::function 개열의 객체는 함수호출성 개체(callable entity, 함수 포인터, 함수 객체, 멤버 함수 포인터 등)를 가질 수 있고,
		이들 개체는 주어진 시점에서 대상 시그니처(여기 예시에서는 <int(const GameCharacger&)>에 해당)와 호환되는 함수 호출성 개체를 가질 수 있다.

		호환(compatible)된다는 말은 예시에서 함수 호출성 개체의 매개변수 타입이 const GameCharacter& 로 암시적 변환이 가능하거나 해당 타입 자체이며
		반환 타입 역시 int로 암시적 변환이 가능하거나 해당 타입인 경우

		함수 호출성 개체 참조 : https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1
		추가로 함수 객체란 - operator()가 구현되어 있는 객체, 해당 객체는 괄호 연산자를 통해 마치 함수를 호출하듯 사용할 수 있다.
	*/

	class GameCharacter; //전방 선언

	int defaultHealthCalc(const GameCharacter& gc) { return 1; }
	short calcHealth(const GameCharacter& gc) { return 2; }//반환 타입이 int가 아닌 것에 주목 -> short은 int로 암시적 변환이 가능하기 때문에 호환가능한 함수호출성 개체
	struct HealthCalculator {
		int operator() (const GameCharacter&) const { return 3; }
	};
	class HealthCalculator2 {
	public:
		float calHealth(const GameCharacter&) const { return 4; }
	};

	class GameCharacter {
	public:
		//HealthCalcFunc 는 함수 호출성 개체로서, GameCharacter와 호환되는
		//어떤 것이든 넘겨받아서 호출할 수 있으며, int와 호환되는 모든 타입의 객체를 반환한다.
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

//고전적인 전략 패턴
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