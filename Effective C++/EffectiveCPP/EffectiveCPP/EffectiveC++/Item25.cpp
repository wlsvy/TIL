#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item25 {
	//예외를 던지지 않는 swap에 대한 지원도 생각해 보자

	//Effective C++ 은 무브 시맨틱(move semantic) 이 C++에 소개되기 이전에 나온 책인것을 고려할 것
	//현재 표준 swap은 이동 생성/대입을 활용하기 때문에 복사 생성/대입을 활용하는 예전 swap과는 다름

	//일반 클래스가 복사비용이 클 경우, 사용자 정의 swap 구현
	class WidgetImpl {
	private:
		int a, b, c;
		std::vector<double> v;	//많은 데이터를 가지고 있으며 복사 비용이 높다고 가정
	};
	class Widget {
	public:
		void swap(Widget& other) {
			using std::swap;	//using 키워드를 사용하면, swap 함수를 호출할 때, 
								//현재 클래스가 속한 네임스페이스의 swap 함수를 먼저 찾은 뒤 있으면 호출하고 
								//혹시 없다면 다면 std::swap 함수를 사용하겠다는 의미	
								//-> 인자 기반 탐색(argument-dependent lookup) & 쾨니그 탐색(koenig lookyp)

			swap(pImpl, other.pImpl);
		}
	private:
		WidgetImpl *pImpl;	//실제 데이터를 가진 객체에 대한 포인터
	};
}

namespace std {
	template<>	//std::swap 의 템플릿 특수화
	void swap<Item25::Widget>(Item25::Widget& a, Item25::Widget& b) {
		a.swap(b);
	}
}
/*
	std:: 네임스페이스의 swap 템플릿 특수화 함수까지 고친 결과, 컴파일도 가능하고 STL 컨테이너와 일관성을 유지할 수 있다.
*/



namespace Item25_2 {
	template<typename T>	 //일반 클래스가 아닌 클래스 템플릿(class template)인 경우
	class WidgetImpl {
	private:
		T a, b, c;
		std::vector<T> v;
	};

	template<typename T>
	class Widget {
	public:
		void swap(Widget<T>& other) {
			using std::swap;	

			swap(pImpl, other.pImpl);
		}
	private:
		WidgetImpl<T> *pImpl;	//실제 데이터를 가진 객체에 대한 포인터
	};

	/*
		클래스가 아닌 클래스 템플릿인 경우, 

		namespace std {
			template<typename T>
			void swap<Widget<T>>(Item25_2::Widget<T>& a, Item25_2::Widget<T>& b) {
				a.swap(b);
			}
		}

		클래스에 대해서는 템플릿 부분 특수화를 허용하지만, 함수 템플릿에 대해서는 허용하지 않도록 정해져 있어서
		위 코드는 컴파일 되지 않는다.
	*/

	/*
		템플릿 부분 특수화가 아닌 함수 오버로드를 활용해보는 경우 역시

		namespace std{
			template<typename T>
			void swap(Item25_2::Widget<T>& a, Item25_2::Widget<T>& b) {
				a.swap(b);
			}
		}

		std는 조금 특별한 네임스페이스이기 때문에 다른 규칙이 적용된다.
		요컨대 std 내의 템플릿에 대한 완전 특수화는 가능하지만, 새로운 템플릿을 추가하는 것은 불가능
		(std 의 구성요소 추가와 관련해서는 전적으로 c++ 표준 위원회에 달려있다)

		std 의 템플릿 함수에 대해서 오버로딩을 추가하는 것은 미정의 결과를 초래할 수 있다.
	*/

	//비멤버 swap 함수 활용, std 네임스페이스의 일부가 아니다
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b) {
		a.swap(b);
	}

	template<typename T>
	void doSomething(T& obj1, T& obj2) {	//어떤 함수에서 swap을 사용하는 경우
		using std::swap;		//using 키워드로 std::swap을 끌어올 수 있도록 한다.

		swap(obj1, obj2);		//T 타입 전용의 swap 사용, 만약 해당 네임스페이스에 swap이 없다면 using으로 끌어온 std::swap 사용

		//std::swap(obj1, obj2); 네임 스페이스를 std::로 한정하게 되면, 다른 것은 거들떠보지도 말고 std::의 swap을 사용하라고 강제하는 꼴
								//해당 네임스페이스에 다른 swap이 존재할 지라도 컴파일러는 무조건 std::swap을 사용하게 된다.
	}
}

/*
	1. 표준에서 제공하는 swap이 사용자 정의 클래스에 대해서 납득할 만한 성능이 보인다면 그냥 아무것도 하지 말것. 
	-> 그대로 std::swap 을 호출할 수 있도록
	-> 또한 멤버 swap은 절대로 예외를 던지지 않도록 할 것

	2. 표준 swap이 기대만큼 효율적이지 않다면 (위의 Widget 예시처럼) 
		- 사용자 정의 클래스에 적합한 swap 함수를 만들되 public 멤버함수로 둘 것. -> 이 함수는 절대 예외를 던져서는 안된다
		- 사용자 정의 클래스와 동일한 네임스페이스에 비멤버 swap을 만든다. 1번에서 만든 swap 멤버 함수를 이 비멤버 함수가 호출하도록 한다.
		- 새로운 클래스(클래스 템플릿이 아니라)를 만들고 있다면, 그 클래스에 대한 std::swap의 특수화 버전을 준비해 둔다. 그리고 이 특수화 버전에서도 swap 멤버 함수를 호출하도록 한다.

	3. 사용자 입장에서 swap을 호출할 때, swap을 호출하는 함수가 std::swap을 볼 수 있도록 using 선언을 반드시 포함시킨다. 그 다음에 swap을 호출하되, 네임스페이스 한정자는 붙이지 않는다.

	멤버 swap이 절대로 예외를 던지면 안되는 이유
	 - 강력한 예외 안전성 보장(strong exception-safety guarantee) 제공 -> 어떤 연산이 실행되다가 예외가 발생하면 그 연산이 시작되기 전으로 돌릴 수 있다는 보장
	 - 비멤버 버전의 경우, 표준 swap 이 복사 생성과 복사 대입에 기반하고 있는데, 이 둘은 예외 발생이 허용되기 때문에 제약을 받지 않는다.
*/