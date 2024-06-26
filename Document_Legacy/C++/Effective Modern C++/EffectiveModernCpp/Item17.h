#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <map>

//특수 멤버 함수들의 자동 작성 조건을 숙지하라

namespace Item17 {

	/*
		컴파일러가 스스로 작성할 수 있는 멤버 함수들, 즉 기본 생성자와 소멸자, 복사 연산들, 이동 연산들을 가리켜 특수 멤버 함수라고 부른다.

		기본 생성자: 
		C++98의 규칙들과 같다. 클래스에 사용자 선언 생성자가 없는 경우에만 자동으로 작성된다.
		
		소멸자: 
		C++98의 규칙들과 본질적으로 같다. 유일한 차이는 소멸자가 기본적으로 noexcept라는 점이다(항목 14 참고). C++98에서처럼, 기본적으로 작성되는 소멸자는 오직 기반 클래스 소멸자가 가상일 때에만 가상이다.
		
		복사 생성자: 
		실행시점 행동은 C++98의 것과 같다. 즉, 비정적 데이터 멤버들을 멤버별로 복사 생성한다. 클래스에 사용자 선언 복사 생성자가 없을 때에만 자동으로 작성된다. 클래스에 이동 연산이 하나라도 선언되어 있으면 삭제(비활성화)된다. 사용자 선언 복사 대입 연산자나 소멸자가 있는 클래스에서 이 함수가 자동 작성되는 기능은 비권장이다.
		
		복사 대입 연산자: 
		실행시점 행동은 C++98의 것과 같다. 즉, 비정적 데이터 멤버들을 멤버별로 복사 대입한다. 클래스에 사용자 선언 복사 대입 연산자가 없을 때에만 자동으로 작성된다. 클래스에 이동 연산이 하나라도 선언되어 있으면 삭제(비활성화)된다. 사용자 선언 복사 생성자나 소멸자가 있는 클래스에서 이 함수가 자동 작성되는 기능은 비권장이다.
		
		이동 생성자와 이동 대입 연산자: 
		각각 비정적 데이터 멤버의 멤버별 이동을 수행한다. 클래스에 사용자 선언 복사 연산들과 이동 연산들, 소멸자가 없을 때에만 자동으로 작성된다.
	*/

	/*
		두 가지 복사 연산 - 복사 생성자/ 복사 대입 연산자
		- 둘은 서로 독립적이다. 즉 하나를 선언한다고 해서 컴파일러가 다른 하나를 자동작성 하지 않는 것은 아니다.

		사용자 정의 복사 연산이 없을 때 필요하다면 컴파일러는 자동으로 작성한다.
	*/

	/*
		두 가지 이동 연산 - 이동 생성자/ 이동 대입 연산자
		- 둘은 독립적이지 않다. 둘 중 하나를 선언하면 컴파일러는 다른 하나를 선언하지 않는다.

		예를 들어 사용자 정의 이동생성자를 선언했다면, 그것은 컴파일러가 작성해주는 기본적인 멤버별 이동 생성이 그 클래스에 그리 적합하지 않아서 다른 방식으로 구현해야 하기 때문일 것이다.
		그리고 기본적인 멤버별 이동 생성이 적합하지 않다면, 멤버별 이동 배정 역시 적합하지 않을 가능성이 크다.
		
		따라서 사용자가 이동 연산 중 하나를 정의한다면 컴파일러는 다른 하나를 자동으로 작성하지 않는다. 

		더 나아가서 복사연산을 하나라도 명시적으로 선언한 클래스에 대해서는 이동 연산들이 작성되지 않는다.
		그 근거는 복사연산을 선언했다는 것은 일반적인 복사 방식이 적합하지 않다는 거싱고 그렇다면 일반적인 객체 이동 방식 역시 적합하지 않을 가능성이 크기 때문.

		반대 방향도 마찬가지 - 이동 연산을 하나라도 명시적으로 선언하면 컴파일러는 복사 연산들을 비활성화한다.
	*/

	/*
		3의 법칙 - 복사 생성자, 복사 배정 연산자, 소멸자 중 하나라도 선언했다면 나머지 둘도 다 선언해야 한다는 것.

		어떤 클래스의 복사 배정 연산을 프로그래머가 직접 지정해야 할 필요성은 거의 항상 그 클래스가 어떤 형태로든 자원 관리를 수행하기 때문에 생긴다.
		그리고 그런 클래스에서는 거의 항상 
		1. 한 복사 연산이 수행하는 자원 관리를 다른 복사 연산에서도 수행해야 하며,
		2. 클래스의 소멸자 역시 그 자원의 관리에 참여한다.

		즉 클래스에 대한 이동 연산들은 다음 세 조건이 모두 만족될 때에만, 그리고 필요할 때에만, 자동으로 작성된다.
		1. 클래스에 그 어떤 복사 연산도 선언되어 있지 않다.
		2. 클래스에 그 어떤 이동 연산도 선언되어 있지 않다.
		3. 클래스에 소멸자가 선언되어 있지 않다.
	*/



	/*
		사용자가 소멸자를 선언하면 이동 연산들의 자동 작성이 금지된다.
		만일 그러한 사용자 선언 두면서도 이동 능력을 지원하고 싶다면, 이동 연산들에 "=default"를 지정하면 된다.
		이동 연산들을 선언하면 복사 연산들이 비활성화 되는데 만일 복사 연산도 활용하고 싶다면 마찬가지로 "=default"를 지정하면 된다.
	*/
	class Base {
	public:
		virtual ~Base(void) = default;                // 소멸자를 가상으로

		Base(Base&&) = default;                        // 이동 지원
		Base& operator=(Base&&) = default;

		Base(const Base&) = default;                // 복사 지원
		Base& operator=(const Base&) = default;
	};


	/*
		StringTable 에서 컴파일러는 자동으로 소멸자, 복사 연산자, 이동 연산자를 생성한다.
	*/
	class StringTable {
	public:
		StringTable(void) {}
		                    // 삽입, 삭제, 조회 등을 위한 함수들은 있지만
							// 복사/이동/소멸자 기능성은 없음

	private:
		std::map<int, std::string> values;
	};

	/*
		StringTable에서 필요에 의해 소멸자가 추가되었다고 해보자.
		아재 컴파일러는 이동 연산들을 자동 생성하지 않는다.

		만약 기존에 StringTableWithDtor을 '이동'하는 함수가 있다면 그 안에서 '이동' 동작은 전부 '복사'로 대체되어버린다!!
	*/
	class StringTableWithDtor {
	public:
		StringTableWithDtor(void)
		{
			std::cout << "Create StringTable object" << std::endl;
		}        

		~StringTableWithDtor(void)                                    
		{
			std::cout << "Destroying StringTable object" << std::endl;
		}   

	private:
		std::map<int, std::string> values;   
	};
}