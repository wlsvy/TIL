#include <iostream>
#include <vector>

class Rational {};

const Rational operator* (const Rational& lhs, const Rational& rhs);	//반환 값을 const 로 선언한 이유는

void DoSomething() {
	Rational a, b, c;

	//(a * b) = c;	//여기서 a*b의 결과에 두고 operator = 을 호출하는 것을 막기 위해
					//const 라서 값 변경 불가능
}

class TextBlock {
public:
	TextBlock(std::string str) : text(str) {}

	//const char& operator[](std::size_t position) const { return text[position]; }	//상수 객체에 대한 operator[]
	//char & operator[](std::size_t position) { return text[position]; }				//비상수 객체에 대한 operator[]
	const char& operator[](std::size_t position) const { return text[position]; }
	char & operator[] (std::size_t position) {				//코드 중복 대처 요령(비상수 버전이 상수 버전 호출)
		return const_cast<char&>(							//c++ 에서 캐스팅은 썩 좋지 못한 아이디어지만, 코드 중복도 쉽게 넘길 순 없다.
			static_cast<const TextBlock&>(*this)[position]	//상수 버전 operator[]를 호출, *this에 const를 붙이고, 반환 타입에서 const를 뗀다.
			);												//operator[]속에서 operator[] 를 호출하면 재귀적으로 계속 호출하게 되니,
	}														//const operator[]를 호출하기 위한 방법으로 *this 에 const 를 붙인다.(탁월한 방법은 아니지만 차선책)			

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

class CTextBlock {
public:
	CTextBlock(char * str) : pText(str) {}
	char & operator[] (std::size_t position) const { return pText[position]; }	//부적절한 
																				//(그러나 비트수준 상수성이 있어서 허용되는) -> 참조자를 반환하되 pText의 값을 고치는 부분이 없으니
																				//operator[] 의 선언
	std::size_t Length() const;
private:
	char *pText;
	mutable std::size_t textLength;		//이 데이터 멤버들은 어떤 순간에도 수정 가능
	mutable bool lengthIsValid;			//심지어 상수 멤버함수 안이라도 가능
};

void DoSomething3() {
	const CTextBlock cctb((char*)"Hello");	//상수 객체 선언
	char *pc = &cctb[0];					//상수 버전의 operator[]를 호출하여 cctb의
											//내부 데이터에 대한 포인터를 얻습니다.
	*pc = 'j';		//cctb는 이제 jello 라는 값을 갖습니다. -> 분명 상수 객체임에도 내부 멤버 변수가 변경되었다.
}

std::size_t CTextBlock::Length() const {
	if (!lengthIsValid) {
		textLength = std::strlen(pText);	//상수 멤버 함수안에서는 일반적으로 안되지만
		lengthIsValid = true;				//mutable 키워드가 붙어서 가능
	}

	return textLength;
}
