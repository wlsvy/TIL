#include <iostream>
#include <vector>
#include <string>

//컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금해 버리자

namespace Item06 {
	/*
		컴파일러에서 자동으로 제공하는 기능을 허용치 않으려면, 
		대응되는 멤버 함수를 private로 선언한 후에 구현은 하지 않은 채로 두십시오.
		
		Uncopyable과 비슷한 기본 클래스를 쓰는 것도 한 방법입니다.
	*/

	class HomeForSale {
	private:
		//선언만 달랑 있습니다.
		//이 방식으로, 복사 생성자 와 대입 연산자를 사용할 수 없도록 막아버린다.
		HomeForSale(const HomeForSale&);	
		HomeForSale& operator=(const HomeForSale&);
	};

	class Uncopyable {
	protected:
		//생성과 소멸 허용
		Uncopyable() {}	
		~Uncopyable() {}
	private:
		//복사 생성, 대입은 방지한다. 링크 시점에서 에러 판정
		Uncopyable(const Uncopyable&);	
		Uncopyable& operator=(const Uncopyable);
	};

	//private 상속
	class HomeForSale2 : private Uncopyable {	
		//복사생성자, 대입 연산자를 선언조차 할 수 없다.
	};
}
