#include <iostream>
#include <vector>
#include <string>
using namespace std;

//new 처리자의 동작 원리를 제대로 이해하자

namespace Item49 {
	/*
		new 처리자란?
		메모리 할당이 제대로 되지 못한 상황에 대한 반응으로 operator new가 예외를 던지기 전에, 
		이 함수는 사용자 쪽에서 지정할 수 있는 에러 처리 함수를 우선적으로 호출할도록 되어 있는데
		이 에러 처리 함수를 가리켜 new 처리자(new-handler, 할당에러 처리자)라고 한다

		(사실 완전히 맞는 말이 아니다. operator new 의 동작은 훨씬 복잡하다)
	*/

	//std:: 네임스페이스에서 new_handler는 받는 것도 없고 반환값도 없는 함수의 포인터에 typedef를 걸어둔 타입 동의어
	typedef void(*new_handler) ();	
	
	//new 처리자를 지정하는 함수
	new_handler set_new_handler(new_handler p) throw();	

	/*
		- New 처리자 함수를 올바르게 사용하기 위해서는 다음 동작 중 하나를 반드시 해 주어야 한다.

		1. 사용할 수 있는 메모리를 더 많이 확보

		2. 다른 new 처리자 설치 - 
		현재의 new 처리자가 더 이상 가용 메모리를 확보할 수 없다 해도 자기 몫까지 해 줄 다른 new 처리자를 알고 있을 수 있다. 
		이 경우 현재의 new 처리자는 다른 new 처리자를 설치할 수  있다.

		3. New 처리자의 설치를 제거 - 
		set_new_handler 에 널 포인터를 넘긴다. New 처리자가 설치된 것이 없으면, 
		operator new는 메모리 할당이 실패 했을 때 예외를 던지게 된다.

		4. 예외를 던진다  - 
		bad_alloc 혹은 bad_alloc 에서 파생된 타입의 예외를 던진다. 
		예외는 메모리 할당을 요청한 원래의 위치로 전파된다.(propagate, 예외를 다시 던진다)

		5. 복귀하지 않는다 - 
		대개 abort 혹은 exit를 호출
	*/
}

namespace Item49_2 {

	void outOfMem(void)
	{
		std::cerr << "Unable to satisfy request for memory\n";
		std::abort();
	}


	void func()
	{	
		//new 처리자 설정
		std::set_new_handler(outOfMem);

		int *pBicDataArray = new int[499999999L];
		/*
			메모리 할당량 초과시 new 처리자로 설정된 outOfMem이 호출된다
		*/
	}
}

namespace Item49_3 {

	class NewHandlerHolder
	{
	public:
		explicit NewHandlerHolder(std::new_handler p)
			: handler(p) { }

		~NewHandlerHolder() { std::set_new_handler(handler); }
	private:
		std::new_handler handler;

		//복사 및 대입 방지
		NewHandlerHolder(const NewHandlerHolder&);	
		NewHandlerHolder& operator=(const NewHandlerHolder&);
	};

	class Widget
	{
	public:
		static std::new_handler set_new_handler(std::new_handler p)
		{
			std::new_handler old_new_handler = currentHandler;
			currentHandler = p;
			return old_new_handler;
		}

		void* operator new(std::size_t size) throw(std::bad_alloc())
		{
			NewHandlerHolder h(std::set_new_handler(currentHandler));
			
			return ::operator new(size);
			/*
				new 처리자를 설정하면서  NewHandlerHolder 자원 관리 객체에 담는다.
				이후 함수가 끝날때 NewHandlerHolder 의 소멸자가 호출되면서, 기존의 new 처리자로 복원된다.
			*/
		}
	private:
		int m_a[499999999L]; // <-- 여기서 메모리 오류
		static std::new_handler currentHandler;
	};
	std::new_handler Widget::currentHandler = 0;

	/*
		Widget의 operator new 가 맡은 역할 세 가지

		1. 표준 set_new_handler 함수에 Widget의 new 처리자를 넘겨서 호출.
		즉, 전역 new 처리자로서 Widget의 new 처리자를 설치

		2. 전역 operator new  를 호출하여 실제 메모리 할당 수행.
		만약 여기서 실패하면, 이 함수는 Widget의 new 처리자를 호출

		마지막까지 전역 operator new 의 메모리 할당이 실패하면, bad_alloc 예외를 던진다
		이 경우 widget의 operator new 는 전역 new 처리자를 원래의 것으로 돌려놓고 예외를 전파시킨다

		3. 전역 operator new 가 widget 객체 하나만큼의 메모리를 할당할 수 있으면,
		widget의 operator new 는 할당된 메모리 반환

		동시에 전역 new 처리자가 관리하는 객체의 소멸자가 호출되면서
		widget의 operator new가 호출되기 전에 쓰이고 있던 전역 new 처리자가 자동 복원
	*/

	//widget 활용방식
	void outOfMem(void)
	{
		std::cerr << "Unable to satisfy request for memory\n";
		std::abort();
	}

	void func() {
		//new 처리자 설치
		Widget::set_new_handler(outOfMem);

		//여기서 메모리 할당이 실패하면 OutOfMem 이 호출
		Widget *pw1 = new Widget;

		//여기서 메모리할당이 실패하면 전역 new 처리자 함수 호출
		std::string *ps = new std::string;

		//widget 클래스의 new 처리자를 null로 설정
		Widget::set_new_handler(0);

		//메모리 할당이 실패하면 이제는 바로 예외를 던진다
		Widget *pw2 = new Widget;
	}
}

namespace Item49_4 {
	//자원관리 객체를 통한 할당에러 처리를 구현하는 방식은 어떤 클래스로 똑같이 나올 것 같다
	//이 코드를 해당 클래스에서도 재사용할 수 있도록 믹스인(mixin) 방식 사용

	class NewHandlerHolder {
	public:
		explicit NewHandlerHolder(std::new_handler nh) :handler(nh) {} 
		~NewHandlerHolder()            
		{
			std::set_new_handler(handler);
		}
	private:
		std::new_handler handler;

		NewHandlerHolder(const NewHandlerHolder&); 
		NewHandlerHolder& operator=(const NewHandlerHolder&);
	};

	template<typename T>   //"mixin-style"
	class NewHandlerSupport {
	public:
		static std::new_handler set_new_handler(std::new_handler p) throw ();
		static void * operator new(std::size_t size) throw (std::bad_alloc);
	private:
		static std::new_handler currentHandler;
	};
	template<typename T>
	std::new_handler NewHandlerSupport<T>::currentHandler = 0;

	template<typename T>
	std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
	{
		std::new_handler oldHandler = currentHandler;
		currentHandler = p;
		return oldHandler;
	}

	template<typename T>
	void* NewHandlerSupport<T>::operator new(std::size_t size)
		throw(std::bad_alloc)
	{
		NewHandlerHolder h(std::set_new_handler(currentHandler));
		return ::operator new(size); 
	}

	/*
		신기하게 반복되는 템플릿 패턴(curiously recurring template pattern : CRTP)
		: 기반클래스가 템플릿 클래스인데 템플릿 매개변수가 파생클래스인 경우.
		파생클래스 종류에 따라 템플릿 사본을 구분해주는 역할을 한다.

		아래의 Widget 클래스는 이전과 내용이 동일하나, NewHandlerSupport를 상속받고 있으므로
		set_new_handler, operator new 에 대한 선언문은 필요없다.
	*/
	class Widget : public NewHandlerSupport<Widget> { };

	void func() {
		// 실패시 bad_alloc 예외
		Widget *pw1 = new Widget;            
		
		//이 if 문 검사는 반드시 실패 
		//new Widget이 성공 시 pw1 에는 주소값이 있고
		//실패 시 bad_alloc 예외가 던져질때 new Widget은 널 포인터를 반환하진 않는다
		if (pw1 == 0) {}                   
		
		//p을 할당하다 실패하면 0(널)을 반환한다
		char* p = new (std::nothrow) char[1048576];

		//이 if문 검사는 성공할 수 있다
		if (p == 0) {}
	}
}

namespace Item49_5 {
	//CRTP와 관련하여, 한 가지 예외를 처리하는 방법
	template<typename T>
	class Base {};

	class Derived1 : public Base<Derived1> {};

	class Derived2 : public Base<Derived1> {};	//여기서 컴파일 에러가 나게 할려면?



	template<typename T>
	class NBase {
	private:
		friend T; //T가 파생클래스가 아닌 곳에서는 생성자 호출 막아버리기
		NBase() {}
	};
}