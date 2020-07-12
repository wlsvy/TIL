#include <iostream>
#include <vector>
#include <string>

//객체의 모든 부분을 빠짐없이 복사하자

namespace Item12 {

	/*
		객체 복사 함수는 주어진 객체의 모든 데이터 멤버 및 모든 기본 클래스 부분을 빠뜨리지 말고 복사해야 합니다.

		복사 대입 연산자에서 복사 생성자를 호출하지 말 것. 
		만든 객체를 또 생성한다. 그 반대도 마찬가지. 생성자는 객체를 초기화하는 것이지만 복사 대입은 초기화된 객체에 값을 주는 것이다.
	*/

	class Customer {
	public:
		//복사생성자
		Customer(const Customer& rhs) : name(rhs.name) {}	

		//대입연산자
		Customer& operator= (const Customer& rhs) {			
			name = rhs.name;
			return *this;
		}
	private:
		std::string name;
	};

	//파생클래스의 경우, 데이터 복사할 때 주의할 것
	class PriorityCustomer : public Customer {	
	public:
		/*
			기반 클래스의 복사생성자 반드시 호출해야 한다. 
			그렇지 않으면 기반클래스 데이터는 복사 되지 않는다.
		*/
		PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority), Customer(rhs) {}
				
		PriorityCustomer& operator= (const PriorityCustomer& rhs) {

			//마찬가지로 기반 클래스의 대입연산자 호출 
			Customer::operator=(rhs); 

			priority = rhs.priority;
			return *this;
		}
	private:
		int priority;
	};

	/*
		복사생성자와 대입연산자의 코드 중복을 피하려는 이유로 한쪽을 이용해서 다른쪽을
		구현하려는 시도는 좋은 방법이 아니다. 복사생성자는 객체 생성 시 초기화를 할때 적용되며
		대입 연산자는 이미 존재하는 객체를 대입시킬 때 적용된다. 분명히 다른 목적으로 활용된다.
		대신 공통 동작을 제 3의 함수에 분리해 놓고 양쪽에서 이것을 호출하는 방법을 활용할 수는 있다.
	*/
}