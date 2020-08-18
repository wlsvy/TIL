#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

//소유권 공유 자원의 관리에는 std::shared_ptr를 사용하라


namespace Item19 {

	/*
	std::shared_ptr는 임의의 공유 자원의 수명을 편리하게(가비지 컬렉션에 맡길 때만큼이나) 관리할 수 있는 수단을 제공한다.

	std::shared_ptr가 할 수 없는 일로는 배열 관리가 있다. std::unique_ptr와는 다르게, std::shared_ptr의 API는 단일 객체를 가리키는 포인터만 염두에 두고 설계되었다.
	std::shared_ptr<T>로 배열을 가리키되, 배열 삭제를 수행하는 커스텀 삭제자를 지정할 수는 없지만, std::shared_ptr은 operator[]를 제공하지 않으므로 배열 원소에 접근하기 까다롭다.
	코드가 컴파일되긴 하지만, 그리 좋은 발상은 아니다.

	또 다른 이유로, std::shared_ptr가 지원하는 파생 클래스 포인터에서 기반 클래스 포인터로의 변환은 단일 객체에는 합당하지만, 배열에 적용하면 타입 시스템에 구멍이 생긴다(그래서 std::unique_ptr<T[]> API는 그러한 변환을 금지한다).

	가장 중요하게는, C++11은 내장 배열에 대한 다양한 대안들(이를테면 std::array나 std::vector, std::string)을 제공한다.


	대체로 std::shared_ptr 객체는 그 크기가 std::unique_ptr 객체의 두 배이며, 제어 블록에 관련된 추가 부담을 유발하며, 원자적 참조 카운트 조작을 요구한다.
	어떤 객체를 가리키는 마지막 std::shared_ptr가 객체를 더 이상 가리키지 않게 되면, 그 std::shared_ptr는 자신이 가리키는 객체를 파괴한다.
	
	그런데 std::shared_ptr는 자신이 객체를 가리키는 최후의 공유 포인터임을 어떻게 알까? 그 비결은 바로 자원의 참조 카운트(reference count)에 있다. 참조 카운트는 관리되는 자원에 연관된 값으로, 그 자원을 가리키는 std::shared_ptr들의 개수에 해당한다.
	
	이러한 참조 카운트 관리는 성능에 다음과 같은 영향을 미친다.
	
	std::shared_ptr의 크기는 생 포인터의 두 배이다. 내부적으로 자원을 가리키는 생 포인터뿐만 아니라 자원의 참조 카운트(Control Block)를 가리키는 생 포인터도 저장해야 하기 때문이다.
	참조 카운트를 담을 메모리를 반드시 동적으로 할당해야 한다. 개념적으로는 참조 카운트는 공유 포인터가 가리키는 객체에 연관된 것이지만, 그 객체 자제는 참조 카운트를 전혀 알지 못한다. 
	따라서 객체는 참조 카운트를 담을 장소를 따로 마련하지 않는다. 항목 21에서 설명하겠지만, std::make_shared를 이용해서 std::shared_ptr를 생성하면 동적 할당의 비용을 피할 수 있다. 
	그러나 std::make_shared를 사용할 수 없는 상황들도 존재한다. 어떤 경우이든, 참조 카운트는 동적으로 할당된 데이터로서 저장된다.
	

	참조 카운트의 증가와 감소가 반드시 원자적 연산이어야 한다. 여러 스레드가 참조 카운트를 동시에 읽고 쓰려 할 수 있기 때문이다. 

	예를 들어 어떤 자원을 가리키는 어떤 std::shared_ptr의 소멸자가 한 스레드에서 실행되는(그래서 그것이 가리키는 자원의 참조 카운트를 감소하는) 도중에 
	다른 어떤 스레드에서 같은 자원을 가리키는 std::shared_ptr가 복사될(그래서 같은 참조 카운트가 증가할) 수도 있다. 
	
	대체로 원자적 연산은 비원자적 연산보다 느리므로, 비록 참조 카운트가 워드 하나 크기라고 해도 그것을 읽고 쓰는 연산이 비교적 느릴 것이라고 가정해야 마땅하다.


	보통 std::shared_ptr의 생성자는 피지칭 객체의 참조 카운트를 1 만큼 증가시키는데, 그렇지 않은 경우도 있다. 바로 이동 생성이 일어날 때이다.
	이것은 이동 대입이 일어날 때에도 마찬가지인데, 참조 카운트를 조작하지 않기 때문에(즉, 원자적 연산을 수행하지 않기 때문에) 복사 연산보다 이동 연산이 더 빠르다.

	std::shared_ptr가 관리하는 객체당 하나의 제어 블록이 존재한다. std::shared_ptr 생성 시 커스텀 삭제자를 지정했다면,
	참조 카운트와 함께 그 커스텀 삭제자의 복사본이 제어 블록에 담긴다.

	앞에서 std::shared_ptr 객체가 자신이 가리키는 객체에 대한 참조 카운트를 가리키는 포인터도 담는다고 했다.
	그 말이 틀린 것은 아니지만, 오해의 소지가 있다. 사실 참조 카운트는 제어 블록(control block)이라고 부르는 더 큰 자료구조의 일부이다.

	자원은 기본적으로 delete를 통해 파괴되나, 커스텀 삭제자도 지원된다. 삭제자의 타입은 std::shared_ptr의 타입에 아무런 양향도 미치지 않는다.
	삭제자를 지원하는 구체적인 방식은 std::unique_ptr의 것과 다르다. std::unique_ptr에서는 삭제자의 타입이 스마트 포인터의 타입의 일부였지만, std::shared_ptr에서는 그렇지 않다.
	


	std::unique_ptr와의 또 다른 차이점은, 커스텀 삭제자를 지정해도 std::shared_ptr 객체의 크기가 변하지 않는다는 점이다.
	커스텀 삭제자는 std::shared_ptr 객체가 아니라, 제어 블록에 담긴다.
	*/
	
	class Widget{};

	class Gadget : public std::enable_shared_from_this <Gadget> {
	public:
		static shared_ptr<Gadget> Create() { return shared_ptr<Gadget>(new Gadget()); }

		//enable_shared_from_this 를 상속받으면 해당 클래스는 this 포인터로부터 shared_ptr를 생성할 수 있다.
		void process() {
			//vw.emplace_back(this);
			/*
				shared_ptr의 컨트롤블럭이 다수 생성되며, 참조카운트가 0 이 될때마다 해당 Gadget 객체는 여러 번 파괴된다.
				미정의 행동 유발
			*/
		}
		void process2() {
			vw.emplace_back(shared_from_this());
			/*
				컨트롤 블럭을 공유하는 다수의 shared_ptr이 생성된다.
			*/
		}
	private:
		Gadget() = default;
		vector<shared_ptr<Gadget>> vw;

		/*
			내부적으로 shared_from_this는 현재 객체에 대한 제어 블록을 조회하고, 
			그 제어블록을 지칭하는 새 std::shared_ptr를 생성한다.
			
			이는 곧, 현재 객체를 가리키는 기존의 std::shared_ptr가 반드시 존재한다는 가정에 해당한다.
			
			그런 std::shared_ptr가 존재하지 않는다면 함수의 행동은 정의되지 않는다.
			
			
			std::shared_ptr가 유효한 객체를 가리키기도 전에 클라이언트가 shared_from_this를 호출하는 일을 방지하기 위해, 
			std::enable_shared_from_this를 상속받은 클래스는 자신의 생성자들을 private로 선언한다.
		*/
	};

	inline void RunSample() {
		auto loggingDel = [](Widget *pw)            // 커스텀 삭제자
		{                        
			cout << "Delete Wdiget" << endl;
			delete pw;
		};

		std::unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel); // 삭제자의 타입이 포인터 타입의 일부

		std::shared_ptr<Widget> spw(new Widget, loggingDel); // 삭제자의 타입이 포인터 타입의 일부가 아님

		auto g = Gadget::Create();
		for (int i = 0; i < 3; i++) {
			auto sp = g->shared_from_this();
		}
		
	}

	/*

	커스텀 할당자를 지정했다면 그 할당자의 복사본도 제어 블록에 담긴다. 그 외에도 제어 블록에는 약한 카운트라고 부르는 이차적인 참조 카운트가 포함되며 그밖의 추가 데이터가 포함될 수 있으나, 일단 지금은 그런 추가 데이터의 존재를 무시하기로 한다.
	생 포인터 타입의 변수로부터 std::shared_ptr를 생성하는 일은 피해야 한다.
	제어 블록의 생성 여부에 관해 다음과 같은 규칙들을 유추할 수 있다.

	std::make_shared(항목 21 참고)는 항상 제어 블록을 생성한다. 이 함수는 공유 포인터가 가리킬 객체를 새로 생성하므로, 
	std::make_shared가 호출되는 시점에서 그 객체에 대한 제어 블록이 이미 존재할 가능성은 전혀 없다.
	
	고유 소유권 포인터(즉, std::unique_ptr나 std::auto_ptr)로부터 std::shared_ptr 객체를 생성하면 제어 블록이 생성된다. 
	고유 소유권(unique-ownership) 포인터는 제어 블록을 사용하지 않으므로, 피지칭 객체에 대한 제어 블록이 이미 존재할 가능성은 전혀 없다(생성 과정에서 std::shared_ptr 객체는 피지칭 객체의 소유권을 획득하므로, 고유 소유권 포인터는 널로 설정된다).
	
	생 포인터로 std::shared_ptr 생성자를 호출하면 제어 블록이 생성된다. 
	이미 제어 블록이 있는 객체로부터 std::shared_ptr를 생성하고 싶다면, 생 포인터가 아니라 std::shared_ptr나 std::weak_ptr(항목 20 참고)를 생성자의 인수로 지정하면 된다. 
	std::shared_ptr나 std::weak_ptr를 받는 std::shared_ptr 생성자들은 새 제어 블록을 만들지 않는다.
	전달된 스마트 포인터들이 이미 필요한 제어 블록을 가리키고 있을 것이기 때문이다.
	
	
	이 규칙에서 비롯되는 한 가지 결과는, 하나의 생 포인터로 여러 개의 std::shared_ptr를 생성하면 피지칭 객체에 여러 개의 제어 블록이 만들어지므로, 
	의문의 여지 없이 미정의 행동이 된다는 점이다.
	
	제어 블록이 여러 개라는 것은 참조 카운트가 여러 개라는 뜻이며, 참조 카운트가 여러 개라는 것은 해당 객체가 여러 번 파괴된다는 뜻이다
	

	std::unique_ptr에 비해 std::shared_ptr가 더 많은 비용이 들지만, 그리 크지 않은 비용을 치르는 대신, 동적 할당 자원의 수명이 자동으로 관리된다는 이득이 생긴다.

	독점 소유권으로도 충분하거나, 심지어는 반드시 충분하지는 않더라도 충분할 가능성이 있다면, 
	std::unique_ptr가 더 나은 선택이다. std::unique_ptr의 성능은 생 포인터의 것에 가까우며, 언제라도 std::unique_ptr를 std::shared_ptr로 '업그레이드'하기도 쉽다.

	하지만 반대로, std::shared_ptr를 std::unique_ptr로 바꾸는 것은 불가능하다.

	*/
}