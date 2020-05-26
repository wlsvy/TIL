#include <iostream>
#include <vector>
#include <string>
using namespace std;

//new 및 delete 를 작성할 때 따라야 할 기존의 관례를 잘 알아 두자

namespace Item51 {
	/*
		operator new 구현 요구사항
		
		: 일단 반환 값이 제대로 되어 있어야 하고, 
		
		가용 메모리가 부족할 경우에는 new 처리자 함수를 호출해야 하며, 
		
		크기가 없는 메모리 요청에 대한 대비책을 갖춰두어야 한다. 
		
		끝으로 실수로 "기본(normal)" 형태의 new 가 가려지지 않도록 해야한다.
	*/

	class Base {
	public:
		//사용자 정의 operator new는 다른 매개변수를 추가로 가질 수 있다
		void * operator new(std::size_t size) throw(std::bad_alloc) {

			//0바이트가 들어오면 1바이트 요구로 간주하고 처리
			if (size == 0) {
				size = 1;
			}

			//new 처리자 호출
			while (true) {

				//메모리 할당 및 성공시 할당한 메모리 주소 반환
				//if(할당 성공) return 할당된 메모리 포인터;

				//할당이 실패했을 경우, 현재의 new 처리자 함수가 어느것인지 찾아내어 호출
				new_handler globalHandler = set_new_handler(0);
				set_new_handler(globalHandler);

				if (globalHandler) (*globalHandler)();
				else throw std::bad_alloc();
			}
		}
	};

	/*
		주의점

		기반 클래서에서 정의된 operator new는 파생클래스가 상속받을 수 있다.

		이때 sizeof(Base) != sizeof(Derived) 인 경우라면, 
		사용장 정의 operator new 파생클래스를 생성할 때 Base 크기의 메모리를 할당할 수 있는 것
	*/

	class Derived : public Base {};

	void func() {
		//Base::operator new 가 호출
		Derived *d = new Derived; 
	}
}

namespace Item51_2 {

	class Base {
	public:
		void * operator new(std::size_t size) throw(std::bad_alloc) {

			/*
				틀린 크기가 들어오면 표준 operator new쪽으로 넘긴다.

				C++에서 독립 개체는 0 바이트를 가질 수 없기 때문에
				0바이트 메모리 요청은 아래 if문에서 반드시 false가 된다.
			*/
			if (size != sizeof(Base)) {
				return ::operator new(size);
			}

			//맞는 크기가 들어오면 이곳에서 메모리 할당. 나머지는 동일
		}

		/*
			Operator new[] 를 구현할 때는 특히 주의할 것.

			사용자 정의 operator new[] 안에서 해 줄 일은 단순히 원시 메모리의 덩어리를 할당하는 것밖에 없다.
			이 시점에서는 배열 메모리에 아직 생기지도 않은 클래스 객체에 대해서 아무것도 할 수 없다.

			위에서 본 것처럼 파생클래스의 객체 배열 크기를 구해야 할 경우,
			객체의 크기가 sizeof(Base) 보다 클 수도 있기 때문에 배열의 개수를 (요구되는 바이트 수) / sizeof(Base) 로 구할 수 없는 것은 당연.

			게다가 동적할당으로 배열이 생성되는 경우 담기에 딱 맞은 메모리 양보다 더 많게 설정될 수 있다.(항목 16)
			배열 원소의 개수를 담기 위한 자투리 공간이 추가로 들어가기 때문.
		*/

		//delete의 구현. new 보다 간단한데 널 포인터에 대한 delete 적용이 안전하도록 보장만 하면 ok
		void operator delete(void *rawMemory, std::size_t size) throw()
		{
			//널 포인터가 delete 되려는 경우 아무것도 하지 않도록 설정
			if (rawMemory == 0) return;

			/*
				파생클래스 객체는 기반 클래스와 메모리 크기가 다를 수 있다

				주의할 점은, 가상 소멸자가 없는 기본클래스에서 파생된 클래스 객체를 삭제할시
				delete로 넘어오는 size 값이 엉터리일 수 있다.
			*/
			if (size != sizeof(Base)) {
				::operator delete(rawMemory); // 다를 시 표준 delete 사용
				return;
			}

			//여기서 rawMemory가 가리키는 메모리 해제
		}
	};

	
}