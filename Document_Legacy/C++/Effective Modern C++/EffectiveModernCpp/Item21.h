#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <Windows.h>
#include <malloc.h>
#include "MemoyUsage.h"

using namespace std;

//new를 직접 사용하는 것보다 std::make_unique와 std::make_shared 를 선호하라

namespace Item21 {

	/*
		new의 직접 사용에 비해, make 함수를 사용하면 소스 코드 중복의 여지가 없어지고, 예외 안전성이 향상되고, 
		std::make_shared와 std::allocate_shared의 경우 더 작고 빠른 코드가 산출된다.

		std::make_shared는 C++11의 일부이지만, std::make_unique는 C++14에서야 표준 라이브러리에 포함되었다. 
	*/

	/*
		make 함수를 사용하면 그렇지 않을 때보다 예외 안전성이 향상되는 효과도 있다.
	*/

	namespace Make_Exception {
		class Widget{};
		inline void processWidget(std::shared_ptr<Widget> spw, int priority) {}
		inline int computePriority() { return 0; }

		inline void RunSample() {

			//Make_Shared/Unique 둘 다 동일.

			processWidget(std::shared_ptr<Widget>(new Widget), computePriority());   // 자원 누수 위험이 존재
			/*
				1. 표현식 "new Widget"이 평가된다.
				즉, Widget이 힙에 생성된다.

				2. new가 산출한 포인터를 관리하는
				std::shared_ptr<Widget>의 생성자가 샐행된다.

				3. computePriority가 실행된다.

				문제는 1 이 2 보다 먼저 실행되어야 한다는 점을 제외하고, 위 세 작업의 실행 순서가
				정해져 있지 않아서 컴파일러마다 순서가 달라질 수 있다는 것이다.

				즉 다음과 같은 순서로 실행될 수도 있다.


				1. 표현식 "new Widget"이 평가된다.
				
				2. computePriority가 실행된다.
				
				3. std::shared_ptr<Widget>의 생성자가 호출된다.

				이런 순서로 실행되는 경우에 computePriority에서
				예외가 발생하면 "new Widget"을 통해 할당된
				메모리가 누수.
			*/

			processWidget(std::make_shared<Widget>(), computePriority());   // 자원 누수의 위험이 없음
		}
	}

	namespace MakeShared_AllocationEfficiency {

		class Widget {};

		inline void RunSample() {

			// 다음처럼 new를 직접 사용한다고 하자.

			std::shared_ptr<Widget> spw1(new Widget);

			/*
				이 코드가 한 번의 메모리 할당을 실행하는 것 처럼 보이지만, 실제로는 두 번의 할당이 일어난다.
				
				
				항목 19에서 설명하듯이, 모든 std::shared에는
				피지칭 객체의 참조 카운트를 비롯한 여러 가지
				관리 데이터를 담는 제어 블록을 가리키는 포인터가 있다.
				
				
				std::shared_ptr 생성자는 이 제어 블록을 위한 메모리를 할당한다.
				
				즉 new를 직접 사용해서 std::shared_ptr를 생성하면 Widget 객체를 위한 메모리 할당과
				제어 블록을 위한 또 다른 메모리 할당이 일어난다.
			*/

			auto spw2 = std::make_shared<Widget>();
			/*
				한 번의 할당으로 충분하다.
				
				이는 std::make_shared가 Widget 객체와 제어 블록 모두를 담을 수 있는 크기의
				메모리 조각을 한 번에 할당하기 때문이다.
				
				동적 할당 횟수가 줄어들 뿐만 아니라, 제어 블록에 일정 정도의 내부 관리용
				
				정보를 포함할 필요가 없어져서 프로그램의 전체적인 메모리 사용량이 줄어들 여지가 생긴다.
				
				방금 살펴본 내용들은 std::allocate_shared에도
				거의 그대로 적용된다.
			*/
		}
	}

	namespace Make_Disadvantage{
		/*
			Make_Unique/Shared 가 가지는 공통적인 단점으로는 커스텀 삭제자를 지정해야 하는 경우와 중괄호 초기치를 전달해야 하는 경우가 있다.

			std::initializer_list를 받는 생성자와 받지 않는 생성자를 모두 가진 타입의 객체를 생성할 때, 
			생성자 인수들을 중괄호로 감싸면 오버로딩 해소 과정에서 std::initializer_list를 받는 버전이 선택되고, 
			괄호로 감싸면 std::initializer_list를 받지 않는 버전이 선택된다.

			make 함수들은 내부적으로 매개변수들을 완벽 전달할 때 중괄호가 아니라 괄호를 사용한다. 
			이 때문에, 피지칭 객체를 중괄호 초기치로 생성하려면 반드시 new를 직접 사용해야 한다.
		*/

		inline void RunSample() {
			auto initList = { 10, 20 };

			// 그 std::initializer_list 객체를 이용해서 std::vector를 생성
			auto spv = std::make_shared<std::vector<int> >(initList);	//(10,20) -> 원소 2개 생성
		}
	}

	namespace MakeShared_MemoryTest {


		/*
		shared_ptr 로 객체를 생성 하면
		1. shared_ptr 이 가리키는 진짜 객체
		2. ControlBlock 으로 이루어진다.

		shared_ptr 생성자 (Ex : shared_ptr<Widget>(new Widget());) 를 호출하면
		메모리 할당은 총 두 번, Widget 객체와, ControlBlock 을 생성하면서 두 번 발생한다.

		shared_ptr을 만드는 또다른 함수, (Ex : make_shared<Widget>();) 를 호출하면
		메모리 할당은 한 번, Widget 객체 크기 + ControlBlock 크기를 합친 만큼 할당받는다.



		shared_ptr 의 controlBlock 에는
		1. shared_ptr 의 참조 횟수를 카운팅하는 strong reference Counter 와
		2. weak_ptr 의 참조 횟수를 카운팅하는 weak reference Counter 로 이루어진다.
		3. 기타 삭제자 등의 정보는 일단 패스

		shared_ptr 생성자로 만들어진 경우,
		strong reference Counter == 0 일 때, 참조하는 객체를 반환하고
		strong reference Counter == 0 && weak reference Counter == 0 일 때, shared_ptr 의 controlBlock 을 반환한다.

		shared_ptr 생성자는 둘의 메모리를 '나눠서' 할당받기 때문에 반환할 때도 '나눠서' 하는 것이 가능하다.

		하지만 make_shared<Widget>() 사용 시
		strong reference Counter == 0 일 때, 참조하는 Widget 객체의 소멸자 호출.
		하지만 메모리를 반환하지 않는다.(Widget 객체의 공간을 비워놓기만 한다.)
		strong reference Counter == 0 && weak reference Counter == 0 일 때, shared_ptr 의 controlBlock과 객체를 '같이' 반환한다.

		make_shared<Widget>()는 둘의 메모리를 '같이' 할당받기 때문에 반환할 때도 '같이' 해야 한다.
		*/

		class Widget {
		public:
			Widget() { cout << "Constructor Called" << endl; }
			~Widget() { cout << "Destructor Called" << endl; }
			char veryveryBig[100000000];
		};

		struct ControlBlock {
			void * ref = nullptr;
		};

		inline void RunSample() {

			cout << "Default Size : " << GetCurrentMemoryUsage() << "MB" << endl;

			{
				weak_ptr<Widget> pw;
				{
					pw = shared_ptr<Widget>(new Widget());
				}
				cout << "Memory Usage 1 = " << GetCurrentMemoryUsage() << "MB" << endl;
			}


			{
				weak_ptr<Widget> pw;
				{
					pw = make_shared<Widget>();
				}
				cout << "Memory Usage(make_shared) 1 = " << GetCurrentMemoryUsage() << "MB" << endl;
			}
			cout << "Memory Usage(make_shared) 2 = " << GetCurrentMemoryUsage() << "MB" << endl;

			/*
				대략적으로 추측해본 make_shared 활용 객체 생성
			*/

			//할당 같이
			unsigned char * mem = static_cast<unsigned char *>(malloc(sizeof(Widget) + sizeof(ControlBlock)));
			Widget * w = reinterpret_cast<Widget*>(mem);
			ControlBlock * c = reinterpret_cast<ControlBlock*>(mem + sizeof(Widget));
			c->ref = (void*)w;


			//객체 파괴(메모리 반환 없이)
			w->~Widget();
			ZeroMemory(w, sizeof(Widget));
			c->ref = nullptr;


			//해제도 같이
			free(mem);

		}

	}
}