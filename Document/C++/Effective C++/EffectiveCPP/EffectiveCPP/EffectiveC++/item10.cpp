#include <iostream>
#include <vector>
#include <string>

//대입 연산자는 *this 의 참조자를 반환하게 하자
namespace Item10 {

	/*
		이것은 단순 대입형 연산자 뿐만 아니라, 모든 형태의 대입 연산자(예를 들어 +=)에서 지켜져야 합니다. 
		
		이러한 관례를 따르지 않아도 컴파일은 되지만, 관례를 따르는 편이 여러 모로 좋습니다. 
		헷갈린다면, int(기본 제공 타입)의 작동 원리대로 만드세요.
	*/

	class Widget {
	public:
		//대입 연산자는 *this의 참조자를 반환하게 하자

		//반환 타입은 현재의 클래스에 대한 참조자
		Widget& operator= (const Widget& rhs) {	
			//....

			//좌변 객체(의 참조자)를 반환
			return *this;	
		}

		//다른 연산자(+=,-=, *= 등)에도 동일한 규약 적용
		Widget& operator+=(const Widget& rhs) {	
			//....
			return *this;
		}

		//매개변수 타입이 다르더라도 동일한 규약 적용
		Widget& operator=(int rhs) {	
			//....
			return *this;
		}
	};
}
