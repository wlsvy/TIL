#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//예외를 방출하지 않을 함수는 noexcept로 선언하라
//참고 http://ajwmain.iptime.org/programming/book_summary/%5B03%5Deffective_modern_cpp/effective_modern_cpp.html#I13

namespace Item14 {

	/*
		noexcept는 함수의 인터페이스의 일부이다. 이는 호출자가 noexcept 여부에 의존할 수 있음을 뜻한다.
		즉 noexcept 함수 안에서도 구현이 잘못되었다면 오류는 발생할 수 있는 것.

		

		c++11에서 도입되었으며, c++ 98 의 throw() 보다 최적화 여지가 더 좋다.
	*/

	// C++98 방식, f0는 예외를 방출하지 않음: 최적화 여지가 적다
	int f0(int x) throw() { return 0; }

	// C++11 방식, f1는 예외를 방출하지 않음: 최적화 여지가 크다.
	int f1(int x) noexcept { return 0; }

	/*
		C++11의 예외 지정에서는 실행시점 행동이 약간 다르다. C++11에서는 프로그램 실행이 종료되기 전에 호출 스택이 풀릴 수도 있고 풀리지 않을 수도 있다.

		noexcept 함수에서 컴파일러의 최적화기(optimizer)는 예외가 함수 바깥으로 전파될 수 있다고 해도 실행시점 스택을 풀기 가능 상태로 유지할 필요가 없다. 또한, 예외가 noexcept 함수를 벗어난다고 해도 noexcept 함수 안의 객체들을 반드시 생성의 반대 순서로 파괴해야 하는 것도 아니다.
		그러나 예외 지정이 "throw()"인 함수에는 그러한 최적화 유연성이 없으며, 예외 지정이 아예 없는 함수 역시 마찬가지로 그런 유연성이 없다.
	*/

	


	//조건부 noexcept 사용 예시, 배열/pair swap
	template <class T, size_t N>
	void swap(T(&a)[N],
		T(&b)[N]) noexcept(noexcept(swap(*a, *b)));

	template <class T1, class T2>
	struct pair {
			void swap(pair& p) noexcept(noexcept(swap(first, p.first)) &&
				noexcept(swap(second, p.second)));
	};
	/*
		위에 선언된 두 swap은 noexcept절 안의 표현식들이 noexcept인지에 의존한다.

		예를 들어 Widget 배열들에 대한 swap은 Widget들에 대한 swap이 noexcept일 때에만 noexcept인 것이다.
	*/




	/*
		소멸자의 noexcept

		noexcept로 선언하는 것이 아주 중요한 일부 함수들은 기본적으로 noexcept로 선언된다.
		기본적으로 모든 메모리 해제 함수(operator delete와 operator delete[] 등)와 모든 소멸자는 암묵적으로 noexcept이다.

		소멸자가 암묵적으로 noexcept로 선언되지 않는 유일한 경우는, 
		예외 방출 가능성을 명시적으로 밝힌(즉, noexcept(false)로 선언된) 소멸자를 가진 타입의 데이터 멤버가 클래스에 있을 때 뿐이다.
	*/


	/*
		std::vector 에서 원소가 삽입될때 벡터의 사이즈를 초과하면, 더 큰 크기의 메모리를 새로 할당한다. 
		이 경우, 기존의 원소들을 옮기는 동작을 수행해야 할 것.

		copy semantic을 활용한다면 통해 원소를 옮길 때 중간에 오류가 발생해도 큰 문제는 없으며 vector의 상태는 변하지 않는다.

		하지만 move semantic을 활용한다면, 동작 중에 에러가 발생할 시 재할당 작업이 중간에 멈추고, vector의 상태는 수정중인 상태 그대로 남아 오염되버린다.
		
		따라서 std::vector::push_back 같은 함수는 std::move_if_noexcept를 호출하는데, 
		이것은 타입의 이동 생성자의 noexcept 여부에 따라 우측값으로의 조건부 캐스팅을 수행하는, std::move의 한 변형이다
	*/
	class Widget {
	public:
		Widget() { cout << "default ctor" << endl; }
		Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
		Widget(Widget&& rhs) { cout << "move ctor" << endl; }
	};

	class Gadget {
	public:
		Gadget() noexcept { cout << "default ctor" << endl; }
		Gadget(const Gadget& rhs) noexcept  { cout << "copy ctor" << endl; }
		Gadget(Gadget&& rhs) noexcept  { cout << "move ctor" << endl; }
	};

	inline void RunSample() {

		vector<Widget> vw;
		for (int i = 0; i < 7; i++) {
			vw.push_back(Widget());
		}

		cout << "===============with noexcept=====================" << endl;

		vector<Gadget> gv;
		for (int i = 0; i < 7; i++) {
			gv.push_back(Gadget());
		}
	}

	//넓은 계약(wide contract),	좁은 계약(narrow contract)
	/*
		넓은 계약을 가진 함수는 전제조건이 없는 함수를 말한다. 
		프로그램의 상태와 무관하게 호출할 수 있으며, 호출자가 전달하는 인수들에 그 어떤 제약도 가하지 않는다. 
		넓은 계약 함수는 켤코 미정의 행동을 보이지 않는다.
		
		넓은 계약을 가진 함수가 아닌 함수들은 모두 좁은 계약을 가진 함수이다. 
		그런 함수의 경우 함수의 전제조건이 위반되면 그 결과는 미정의 행동이다.
		
		넓은 계약을 가진 함수를 작성하는 경우, 만일 그 함수가 예외를 던지지 않음을 알고 있다면 noexcept로 선언하는 것은 쉬운 일이다.
		
		좁은 계약을 가진 함수는 함수 내에서 전제조건을 위반하였음을 알리는 예외를 던질 가능성이 있다. 
		던져진 예외를 디버깅하는 것이 미정의 행동의 원인을 추적하는 것보다 더 쉽기 때문이다.
		
		이런 이유로, 넓은 계약과 좁은 계약을 구분하는 라이브러리 설계자들은 넓은 계약을 가진 함수들에 대해서만 noexcept를 사용하는 경향이 있다
	*/



	// 다음의 코드는 완벽히 적법한 코드이다.
	void setup(void) {}
	void cleanup(void) {}

	void doWork(void) noexcept
	{
		setup();        
		cleanup();      
	}

	/*
		여기서 doWork는 noexcept 함수
		setup과 cleanup은 noexcept가 아니다
		
		이는 모순된 일로 보이지만, 어쩌면
		그냥 문서화의 문제일 수도 있다.
		
		즉, setup과 cleanup이 비록 noexcept로
		선언되어 있지는 않지만, 실제로는 예외를 절대로 던지지 않을 수도 있다.
		
		이를테면, C로 작성된 라이브러리의 일부는 예외를 던지지 않음에도 noexcept 선언이 안된 경우가 있다.
		
		아니면, C++98의 예외 지정을 사용하지 않기로 결정한, 
		그리고 C++11에 맞게 갱신되지는 않은 어떤 C++98 라이브러리의 일부일 수도 있다.
		
		이처럼 noexcept 함수가 적법한 이유로 noexcept 보장이 없는 코드에 의존하는
		경우가 있으므로, C++은 이런 코드를 허용하며, 일반적으로 컴파일러는 이에 대해 경고 메시지를 표시하지 않는다.
	*/
}