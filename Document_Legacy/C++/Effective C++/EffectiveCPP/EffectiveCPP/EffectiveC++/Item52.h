#include <iostream>
#include <vector>
#include <string>
using namespace std;

//위치지정 new를 작성한다면 위치지정 delete도 같이 준비하자

namespace Item52 {

	namespace StandardCase {
		class Widget{};

		inline void RunSample() {
			/*
				이 경우 먼저 operator new 함수가 메모리를 할당한 뒤 Widget의 생성자가 호출됩니다.

				그런데 Widget의 생성자에서 예외가 발생한 경우 프로그래머는 메모리 누수를 해결할 수 없습니다.

				동적 할당 받은 메모리의 시작 주소가 pw에 담기기도 전에 예외가 던져지기 때문이죠.
				이 경우 메모리의 해제는 C++ 런타임 시스템께서 맡이 주시게 됩니다.

				하지만 C++ 런타임 시스템이 알아서 메모리를 해제하려면 new와 짝이 맞는 delete를 알아야 합니다.
			*/
			Widget *pw = new Widget;
			delete pw;
		}
	}

	/*
		일반적인 경우 이것은 큰 문제가 되지 않습니다. 왜냐하면 기본형 operator new는
		역시 기본형 operator delete와 짝을 맞추기 때문입니다.

		void* operator new(std::size_t) throw(std::bad_alloc);

		//전역 유효범위에서의 기본형 시그너처
		void operator delete(void *rawMemory) throw();

		//클래스 유효범위에서의 전형적인 기본형 시그너처
		void operator delete(void *rawMemory, std::size_t size) throw();
	*/
	
		
					
	/*
		따라서 표준 형태의 new 및 delete만 사용하는 한, 런타임 시스템은 new의 동작을 되돌릴 방법을 알고 있는 delete을 문제없이 찾아낼 수 있습니다.
		하지만 operator new의 기본형이 아닌 형태를 선언하기 시작하면 new와 delete짝을 맞추는 데 문제가 뽀송뽀송 피어나게 됩니다.

		비기본형이란 바로 다른 매개변수를 추가로 갖는 operator new를 뜻합니다.
		(이런 operator new를 위치지정 (placement) new 라고 합니다.)

		메모리 할당은 성공했지만 생성자에서 예외가 발생하는 경우, 메모리 할당을 되돌리는 것은 c++ 런타임 시스템의 책임입니다. 
		그런데 런타임 시스템 쪽에서는 호출된 operator new 가 어떻게 동작하는지를 알아낼 방법이 없으므로 할당 자체를 되돌릴 방법이 없습니다.
		대신 런타임 시스템은 operator new가 받아들이는 매개변수의 개수 및 타입이 똑같은 operator delete를 찾고, 찾아냈으면 그 녀석을 호출합니다.

		따라서 만약에 위치지정 new를 만들어 둔 뒤, 그에 대응하는 위치지정 delete를 만들어 놓지 않는다면, 
		런타임 시스템은 예외 상황에 어떻게 대처해야 하는지 몰라 아무것도 하지 않습니다.
	*/

	namespace BadCase {

		class Widget {
		public:
			// 비표준 형태의 operator new
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}

			// 클래스 전용 operator delete의 표준 형태
			static void operator delete(void *pMemory, size_t size) throw() {}
		};

		inline void RunSample() {
			/*
				operator new를 호출하면 cerr을 ostream 인자로 넘기는데, 이때 Widget 생성자에서 예외가 발생하면 메모리가 누출됩니다.
			*/
			Widget *pw = new(std::cerr) Widget;
		}
	}
										
	/*
		위에서 호출된 new는 ostream& 타입의 매개변수를 추가로 받아들이므로, 
		이것과 짝을 이루는 operator delete 역시 똑같은 시그너처를 가진 것이 마련되어 있어야 합니다.

		void operator delete(void *, std::ostream&) throw();
	*/

	namespace GoodCase {
		/*
			이러한 operator delete를 위치지정 delete라고 합니다.
			따라서 예제에서 위치지정 delete를 추가해 주면 메모리 누출 위험이 사라집니다.
		*/
		class Widget {
		public:
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}

			static void operator delete(void *pMemory) throw() {}
			static void operator delete(void *pMemory, std::ostream& logStream) throw() {}

		};

		inline void RunSample() {


			//이전과 같은 코드이지만 메모리 누출이 없습니다.
			Widget *pw = new(std::cerr) Widget;

			// 기본형의 operator delete가 호출됩니다.
			delete pw;

			// 일반적인 경우에는 위치지정 delete 대신 기본형의 operator delete 가 호출됩니다.
		}
	}

	//new 및 delete의 위치지정 버전을 선언할 때는, 의도한 바도 아닌데 이들의 표준 버전이 가려지는 일이 생기지 않도록 주의해 주세요.
	namespace DerivedClassCase {

		class Base {
		public:
			//이 new가 표준 형태의 전역 new를 가립니다.
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}
		};

		inline void RunSample() {
			// 에러! 표준 형태의 전역 operator new가 가려지거든요.
			//Base *pb = new Base;               

			//이건 문제없습니다. Base의 위치지정 new를 호출합니다.
			Base *pb = new(std::cerr) Base;

			// 파생 클래스는 전역 operator new는 물론이고 자신이 상속받는 기본 클래스의 operator new까지 가려 버립니다.

			// 위의 Base로부터 상속받은 클래스
			class Derived : public Base {
			public:
				//기본형 new를 클래스 전용으로 다시 선언합니다.
				static void* operator new(std::size_t size) throw(std::bad_alloc) {}
			};

			// 에러! Base의 위치지정 new가 가려져 있기 때문입니다.
			//Derived *pd = new(std::cerr) Derived;    

			// 문제없습니다. Derived의 operator new를 호출합니다.
			Derived *pd = new Derived;
		}

		/*
			C++가 전역 유효 범위에서 제공하는 operator new의 형태는 다음 세 가지가 표준입니다.

			// 기본형 new
			void* operator new(std::size_t) throw(std::bad_alloc);
			// 위치지정 new
			void* operator new(std::size_t, void*) throw();
			// 예외불가 new (항목 49 참조)
			void* operator new(std::size_t, const std::nothrow_t&) throw();
		*/


		/*
			어떤 형태든 간에 operator new가 클래스 안에 선언되는 순간, 앞의 예제처럼 위의 표준 형태들이 몽땅 가려지는 것입니다.

			다음과 같은 한 가지 해결책이 있습니다. 기본 클래스 하나를 만들고, 이 안에 new 및 delete의 기본 형태를 전부 넣어두십시오.
		*/
		class StandardNewDeleteForms {
		public:
			// 기본형 new/delete
			static void* operator new(std::size_t size) throw(std::bad_alloc)
			{
				return ::operator new(size);
			}
			static void operator delete(void *pMemory) throw()
			{
				::operator delete(pMemory);
			}

			// 위치지정 new/delete
			static void* operator new(std::size_t size, void *ptr) throw()
			{
				return ::operator new(size, ptr);
			}
			static void operator delete(void *pMemory, void *ptr) throw()
			{
				::operator delete(pMemory, ptr);
			}

			// 예외불가 new/delete
			static void* operator new(std::size_t size, const std::nothrow_t& nt) throw()
			{
				return ::operator new(size, nt);
			}
			static void operator delete(void *pMemory, const std::nothrow_t&) throw()
			{
				::operator delete(pMemory);
			}
		};

		/*
			표준 형태에 덧붙여 사용자 정의 형태를 추가하고 싶다면, 이제는 이 기본 클래스를 축으로 넓혀 가면 됩니다.

			상속과 using 선언을 2단 콤보로 사용해서 표준 형태를 파생 클래스 쪽으로 끌어와 외부에서 사용할 수 있게 만든 후에, 원하는 사용자 정의 형태를 선언해 주세요.
		*/
		class Widget : public StandardNewDeleteForms {
		public:
			// 표준 형태가 (Widget 내부에) 보이도록 만듭니다.
			using StandardNewDeleteForms::operator new;
			using StandardNewDeleteForms::operator delete;

			// 사용자 정의 위치지정  new를 추가합니다.
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}

			// 앞의 것과 짝이 되는 위치 지정 delete를 추가합니다.
			static void operator delete(void *pMemory, std::ostream& logStream) throw() {}
		};
	}
	
}