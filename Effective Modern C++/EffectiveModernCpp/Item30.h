#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//완벽 전달이 실패하는 경우들을 잘 알아두라

namespace Item30 {

	/*
		완벽 전달은 단순히 객체들을 전달하는 것이 아니라 그 객체들의 주요 특징,
		즉 그 형식, 왼값 또는 오른값 여부, const 나 volatile 여부까지도 전달하는 것을 말한다.

		전달함수는 그냥 템플릿 함수가 아니라 가변 인수 템플릿(variadic template), 즉 임의의 형식과 개수의 인수들을 받는 템플릿이어야 한다.
	*/
	inline void f()									{ std::cout << "Void" << std::endl; }
	inline void f(int)								{ std::cout << "int" << std::endl; }
	inline void f(std::size_t)						{ std::cout << "std::size_t" << std::endl; }
	inline void f(std::initializer_list<int>)		{ std::cout << "initializer_list<int>" << std::endl; }
	inline void f(void*)							{ std::cout << "void *" << std::endl; }
	//inline void f(int(*)(int))						{ std::cout << "int(*)(int)" << std::endl; }

	template <typename... Ts>
	void fwd(Ts&&... params)               
	{
		f(std::forward<Ts>(params)...);    
	}

	/*
		f( 표현식 );
		fwd( 표현식 );
		
		대상 함수 f와 전달 함수 fwd 있다고 할 때, 어던 인수로 f를 호출했을 때 동작과, fwd를 호출했을 때 동작이 다르다면 완벽전달은 실패한 것이다.

		Ex)
		1. fwd의 매개변수들 중 하나 이상에 대해 컴파일러가 타입을 추론하지 못한다. 이 경우 코드는 컴파일되지 않는다.
		2. fwd의 매개변수들 중 하나 이상에 대해 컴파일러가 타입을 잘못 추론한다.  "잘못된" 타입 추론 때문에 fwd에서 호출되는 f가 f를 직접 호출했을 때 선택되는 오버로딩된 함수와 다른 경우 존재
	*/

	namespace Case0 {
		//중괄호 초기치
		/*
			항목 2에서 설명하듯이, 템플릿 타입 추론은 중괄호 초기치를 추론하지 못한다. 
			중괄호 초기치의 타입 추론이 실패하므로 중괄호 초기치의 완벽 전달도 실패한다.
		*/

		inline void RunSample() {
			//fwd({ 1, 2, 3 });	//컴파일 에러

			//우회책
			auto il = { 1, 2, 3 };
			fwd(il);	// initializer_list<int>
		}
	}

	namespace Case1 {
		//nullptr
		/*
			0 및 NULL 을 주의하자, nullptr을 사용할 것
		*/

		inline void RunSample() {
			int* i0 = 0, *i1 = NULL;
			fwd(i0);		// void*
			fwd(i1);		// void*

			fwd(0);			// int
			fwd(NULL);		// int

			fwd(nullptr);	// void*
		}
	}

	namespace Case2 {
		//선언만 된 정수 static const 및 constexpr 데이터 멤버
		/*
			일반적인 규칙으로, 정수 static const 데이터 멤버와 정수 static constexpr 데이터 멤버는 클래스 안에서 정의할 필요가 없다. 
			선언만 하면 된다. 이는 그런 멤버의 값에 대해 컴파일러가 const 전파(const propagation)를 적용해서, 
			그런 멤버의 값을 위한 메모리를 따로 마련할 필요가 없어지기 때문이다.

			하지만, 만일 그런 멤버들의 주소를 취하는 코드(이를테면 그런 멤버를 가리키는 포인터를 만든다면)를 만든다면, 
			그런 멤버를 위한 저장소가 필요해지며, 그러면 이 코드는 컴파일되긴 하지만 링크에 실패한다.

			컴파일러가 산출한 코드에서 참조는 포인터처럼 취급되는 것이 보통이다(즉, 주소를 취한다). 
			따라서 그런 멤버들을 보편 참조(universal reference)에 묶으려 하면 링크에 실패하는 코드가 만들어질 가능성이 크다. 
			설령 링크가 된다고 하더라도 표준이 아니므로 이식성이 떨어진다.
			
			따라서, 그러한 멤버들을 완벽하게 전달하려면 그런 멤버들의 정의를 만들어 주면 된다

		*/

		class Widget {
		public:
			static constexpr std::size_t MinVals = 28;
		};

		inline void RunSample() {
			f(Widget::MinVals);
			fwd(Widget::MinVals);	//컴파일러에 따라 링크에 실패할 수 있다. static 변수는 cpp에 구현시킬 것.

			const size_t * ptr = &Widget::MinVals;
			/*
				하드웨어와 프로그램 바탕의 이진코드에서 참조는 포인터와 본질적으로 동일하다.

				MinVals를 참조로 전달하는 것으 사실상 포인터로 넘겨주는 것이며, 그러면 포인터가 가리킬 뭔가가 필요하다.
				일반적으로 정수 static const 및 constexpr 자료 멤버를 참조로 전달하려면 그 멤버를 정의할 필요가 있다.
			*/
		}
	}

	namespace Case3 {
		//중복적재된 함수 이름과 템플릿 이름

		inline int processVal(int) { return 0; }
		inline int processVal(int, int) { return 0; }

		template<typename T>
		T workOnVal(T) { return T(); }

		inline void RunSample() {
			//fwd(processVal);	//컴파일 오류, fwd는 어떤 processVal 선택해야 할지 모른다.
			//fwd(workOnVal);		//마찬가지

			//우회책
			using FuncType = int(*)(int);
			FuncType pv = processVal;

			fwd(pv);								//명시적 지정
			fwd(static_cast<FuncType>(workOnVal));	//템플릿 함수 역시 명시적 지정
		}
	}

	namespace Case4 {
		//비트필드
		/*
			메모리의 주소는 바이트 단위로 할당된다. 따라서 임의의 바이트를 가리키는 포인터를 만들 수 있지만, 
			임의의 비트를 가리키는 포인터는 만들 수 없다. 위에서도 언급했지만, 컴파일러가 산출한 코드에서 참조는 포인터처럼 취급되는 것이 보통이다. 
			이 때문에, 비트 필드는 보편 참조(universal reference)에 묶일 수가 없어서 완벽 전달에 실패한다.

			비트필드를 매개변수에 전달하는 방법은 단 두 가지로, 하나는 값으로 전달하는 것이고, 다른 하나는 const에 대한 참조로 전달하는 것이다.

			값 전달 매개변수의 경우 호출된 함수가 비트필드 값의 복사본을 받는다. 그리고 const 참조 매개변수의 경우, 
			표준에 따르면 그 참조는 실제로 어떤 표준 정수 타입(이를테면 int)의 객체에 저장된 비트필드 값의 복사본에 묶여야 한다. 
			즉, 그 const 참조는 비트필드 자체가 아닌, 비트필드 값이 복사된 '보통'객체에 묶인다.

			따라서 비트필드를 완벽 전달 함수에 넘겨주려면, 비트필드 값의 복사본을 직접 생성해서 그 복사본을 전달하면 된다.
		*/

		struct IPv4Header {
			std::uint32_t 
				version : 4,
				IHL : 4,
				DSCP : 6,
				ECN : 2,
				totalLength : 16;
		};

		inline void RunSample() {
			IPv4Header h;
			h.totalLength = 16;
			std::cout << sizeof(IPv4Header) << std::endl;
			f(h.totalLength);
			//fwd(h.totalLength);            // 오류, 비트필드는 주소값이 없음

			//우회책
			auto length = static_cast<std::uint16_t>(h.totalLength);
			fwd(length);					// 복사본을 전달한다.
		}
	}
}