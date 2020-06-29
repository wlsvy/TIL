#include <iostream>
#include <vector>

//낌새만 보이면 const를 들이대 보자!
namespace Item03 {
	using namespace std;

	/*
		const를 붙여 선언하면 컴파일러가 사용상의 에러를 잡아내는 데 도움을 줍니다. 

		const는 어떤 유효범위에 있는 객체에도 붙을 수 있으며, 
		함수 매개변수 및 반환 타입에도 붙을 수 있으며, 
		멤버 함수에도 붙을 수 있습니다.

		const를 통해 상수 값을 선언할 수 있다.

		상수 포인터
		STL 의 const_iterator 
		const 멤버 함수 선언
	*/

	class Rational {};

	//함수 반환 값을 상수로 정해 주면, 안전성이나 효율을 포기하지 않고도 사용자측의 에러 돌발 상황을 줄이는 효과를 꽤 자주 볼 수 있게 된다
	const Rational operator* (const Rational& lhs, const Rational& rhs);

	void DoSomething() {
		Rational a, b, c;

		/*
			여기서 a*b의 결과에 두고 operator = 을 호출하는 것을 방지.
			const 객체는 값 변경이 불가능해서 아래 코드는 컴파일 오류
		*/
		//(a * b) = c;
	}

	class TextBlock {
	public:
		TextBlock(std::string str) : text(str) {}

		//상수 객체에 대한 operator[]
		//const char& operator[](std::size_t position) const { return text[position]; }	
		
		//비상수 객체에 대한 operator[]
		//char & operator[](std::size_t position) { return text[position]; }				

		//상수 멤버 및 비상수 멤버 함수에서 코드 중복을 피하는 방법.
		/*
			비상수 버전이 상수 버전을 호출한다.

			c++ 에서 캐스팅은 썩 좋지 못한 아이디어지만, 코드 중복도 쉽게 넘길 순 없다.

			상수 버전 operator[]를 호출, *this에 const를 붙이고, 반환 타입에서 const를 뗀다.
			operator[]속에서 operator[] 를 호출하면 재귀적으로 계속 호출하게 되니,
			const operator[]를 호출하기 위한 방법으로 *this 에 const 를 붙인다.(탁월한 방법은 아니지만 차선책)	
		*/
		const char& operator[](std::size_t position) const { return text[position]; }
		char & operator[] (std::size_t position) {				
			return const_cast<char&>(							
				static_cast<const TextBlock&>(*this)[position]	
				);												
		}																

	private:
		std::string text;
	};

	void DoSomething2() {
		TextBlock tb("Hello");
		std::cout << tb[0];	//비상수 멤버 호출

		const TextBlock ctb("World");
		std::cout << ctb[0];	//상수 멤버 호출

		tb[0] = 'x'; //문제 없음
		//ctb[0] = 'x'; // 컴파일 에러
	}

	void print(const TextBlock& ctb) {
		std::cout << ctb[0];	//상수 멤버 호출
	}

	/*
		비트수준 상수성bitwise constness : 다른 말로 물리적 상수성이라고도 한다. 
		
		어떤 멤버 함수가 그 객체의 어떤 데이터 멤버도 건드리지 않아야(정적 멤버 제외) 그 멤버 함수가 'const' 임을 인정하는 개념. 
		즉 그 객체를 구성하는 비트들 중 어떤 것도 바꾸면 안 된다는 것.

		논리적 상수성이란 상수 멤버 함수라고 해서 객체의 한 비트도 수정할 수 없는 것이 아니라 일부 몇 비트 정도는 바꿀 수 있되, 
		그것을 사용자측에서 알아채지 못하게만 하면 상수 멤버 자격이 있다는 것
	*/

	class CTextBlock {
	public:
		CTextBlock(char * str) : pText(str) {}

		/*
			부적절하지만 비트수준 상수성이 있어서 허용된다.
			 -> 참조자를 반환하되 pText의 값을 고치는 부분은 없어서 가능하다.
			operator[] 의 선언
		*/
		char & operator[] (std::size_t position) const { return pText[position]; }	
																					
																					
		std::size_t Length() const;
	private:
		char *pText;
		
		//mutable 키워드가 붙은 멤버함수는 const 멤버 함수 내부에서도 수정이 가능하다.
		mutable std::size_t textLength;	
		mutable bool lengthIsValid;		
	};

	void DoSomething3() {
		/*
			상수 객체에 대해서 operator[]를 호출한 뒤 내부 데이터의 포인터를 획득한다.
		*/
		const CTextBlock cctb((char*)"Hello");
		char *pc = &cctb[0];					
		
		//cctb는 이제 jello 라는 값을 갖는다. -> 분명 상수 객체임에도 내부 멤버 변수가 변경되었다.
		*pc = 'j';		

		/*
			논리적 상수성이란 이런 황당한 상황을 보완하는 개념으로 등장하였다.

			논리적 상수성이란 상수 멤버 함수라고 해서 객체의 한 비트도 수정할 수 없는 것이 아니라 일부 몇 비트 정도는 바꿀 수 있되,
			그것을 사용자측에서 알아채지 못하게만 하면 상수 멤버 자격이 있다는 것
		*/
	}

	std::size_t CTextBlock::Length() const {
		//상수 멤버 함수 내부이지만 mutable 키워드가 붙은 멤버는 수정 가능
		if (!lengthIsValid) {
			textLength = std::strlen(pText);
			lengthIsValid = true;			
		}

		return textLength;
	}
}