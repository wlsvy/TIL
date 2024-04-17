#include <iostream>
#include <vector>
#include <string>
using namespace std;

//인터페이스 설계는 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게 하자
namespace Item18 {

	//예시 1 : 날짜
	struct Day {
		explicit Day(int d) : val(d) {}
		int val;
	};

	class Month {	//일년은 12개월이므로 이 점을 제약으로 활용할 수 있다.
	public:
		/*
			static 함수로 미리 정의하는 방식

			정적객체가 아닌 정적함수로 정의한 것이 특징인데  
			객체는 초기화 시점이 사용시점 보다 늦어지는 경우가 있다면 문제가 발생할 수 있기 때문(항목 4 참조)
		*/
		static Month Jan() { return Month(1); }	
		static Month Fab() { return Month(2); }	
		//....

	private:
		explicit Month(int m) : val(m) {}
		int val;
	};

	struct Year {
		explicit Year(int y) : val(y) {}
		int val;
	};

	class Date {
	public:
		/*
			이 방식은 숫자를 직접 입력하는 과정에서 실수가 발생할 수 있다.
			Date d(30, 3, 1995);	날짜에 월 값이 들어간다던지
			Date d(3, 40, 1995);	3을 4로 잘못 눌러 최대 일수(31 & 30) 을 넘긴다던지
		*/
		Date(int month, int day, int year) {}

		/*
			사용하는 입장에서 실수를 줄일 수 있게 하는 방식
			타입이 다를 경우 즉각 확인할 수 있게 구현되었다.
			Date(Month::Jan(), Day(30), Year(1995));
		*/
		Date(const Month& m, const Day& d, const Year& y) {}
	};

	//예시 2 : 타입에 const제약 부여하기
	/*
		if(a * b = c) <= 흔히 발생할 수 있는 실수를 방지하려면
		operator* 의 반환 타입에 const를 선언한다면 사용자가 위의 식에서 바로 실수를 확인할 수 있다.
	*/

	//예시 3 : 팩토리 함수
	class Investment{};

	//Investment* createInvestment();	//포인터를 반환하는 팩토리 함수

	/*
		아예 스마트 포인터를 반환하게 만들어버릴 수도 있다
		사용자가 자원 반환을 깜빡하게 만드는 경우 방지
	*/
	std::shared_ptr<Investment> createInvestment();
													

	//추가적으로 스마트포인터의 삭제자 추가
	void getRidOfInvestment(Investment* ptr) {}

	std::shared_ptr<Investment> createInvestment() {
		std::shared_ptr<Investment> retVal(static_cast<Investment*>(0), getRidOfInvestment);	
		//널 포인터와 삭제자를 가진 스마트 포인터

		//retVal 은 실체를 가리키도록 작업

		return retVal;
	}
	//삭제자를 활용한다면 포인터마다 적합한 삭제자를 적용되도록 구현할 수 있다.

	//교차 DLL 문제(cross-DLL problem)에도 대응이 가능하다
	//new/delete 짝이 하나의 DLL에 포함되어 있는게 아니라 두 개 이상의 DLL에 분리되어 있는 경우 문제가 발생하는데
	//위 방식으로는 생성하는 DLL에서 삭제자도 같이 스마트 포인터에 적용하는게 가능하므로 문제를 봉쇄할 수 있다.
}
