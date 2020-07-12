#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//파일 사이의 컴파일 의존성을 최대로 줄이자

namespace Item31 {

	/*
		위의 include 지시자에서 #include <string>, string 은 전방선언을 해선 안된다

		string은 사실 클래스가 아니라 typedef로 정의한 타입동의어 (basic_string<char>를 typedef 한 것)
		string을 전방선언이 맞을 리가 없다.

		표준 라이브러리 헤더는 일반적인 경우 컴파일 시 병목요인이 되지 않는다. #include <string> 꼭 하자.
	*/

	class PersonImpl;	//전방선언
	class Date;
	class Address;

	/*
		포인터/ 참조자 뒤에 실제 객체 구현부를 숨긴다면 사용하는 측에서는 해당 타입에 대해 정확히 알지 못하더라도 컴파일에는 지장이 없다.
		정의부에 대한 의존성(dependencies on definitions)을 선언부에 대한 의존성(dependencies on declarations)으로 바꾸어 놓은 것

		객체 참조자 및 포인터로 충분한 경우에는 객체를 직접 사용하지 않는다

		어떤 클래스를 사용하는 함수를 선언할 때는 그 클래스의 정의를 가져오지 않아도 된다.
		-> 해당 클래스를 값 형태 매개변수로 전달하거나 반환하더라도 클래스 정의가 필요 없다.
		-> 함수가 호출되기 전에만 해당 타입 정보를 컴파일러가 알게 된다면 ok

		선언부와 정의부에 대해 별도의 헤더 파일을 제공한다.
	*/

	//선언에 의존하는 방법 1 -> 핸들 클래스
	//PersonHandle 클래스 선언부는, Date, address, PersonImpl 에 대한 정의를 몰라도 전방선언이면 충분.
	class PersonHandle {
	public:
		PersonHandle(const std::string& name, const Date& birthday, const Address& addr);
		std::string name() const;
		Date birthday() const;
		Address address() const;
	private:
		std::shared_ptr<PersonImpl> pImpl;
	};

	//선언에 의존하는 방법 2 -> 인터페이스 클래스
	//어떤 기능을 나타내는 인터페이스를 추상 기본 클래스를 통해 마련해 놓고, 이 클래스로부터 파생 클래스를 만들 수 있게 하는 것
	class PersonInterface {
	public:
		static shared_ptr<PersonInterface> create(const std::string& name, const Date& birthday, const Address& addr);
		virtual ~PersonInterface() {}
		virtual std::string name() const = 0;
		virtual Date birthday() const = 0;
		virtual Address address() const = 0;
	};

	
	//사용자 측에서는 Item31.h 파일/ Date, Address 클래스 정보 만 포함시키면 내부 인터페이스들을 문제없이 사용가능하다.
	void func0();

	/*
		라이브러리 헤더는 그 자체로 모든 것을 갖추어야 하며 선언부만 갖고 있는 형태여야 합니다. 이 규칙은 템플릿이 쓰이거나 쓰이지 않거나 동일하게 적용합시다.
	*/
}