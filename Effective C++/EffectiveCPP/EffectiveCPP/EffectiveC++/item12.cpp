//객체의 모든 부분을 빠짐없이 복사하자
#include <iostream>
#include <vector>
#include <string>

namespace Item12 {
	class Customer {
	public:
		Customer(const Customer& rhs) : name(rhs.name) {}	//복사생성자
		Customer& operator= (const Customer& rhs) {			//대입연산자
			name = rhs.name;
			return *this;
		}
	private:
		std::string name;
	};

	class PriorityCustomer : public Customer {	//파생클래스의 경우, 데이터 복사할 때 주의할 것
	public:
		PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority), 
			Customer(rhs) {}	//기반 클래스의 복사생성자 반드시 호출해야 한다. 
								//그렇지 않으면 기반클래스 데이터는 복사 X
		PriorityCustomer& operator= (const PriorityCustomer& rhs) {
			Customer::operator=(rhs); //마찬가지로 기반 클래스의 대입연산자 호출 
			priority = rhs.priority;
			return *this;
		}
	private:
		int priority;
	};

	//복사생성자와 대입연산자의 코드 중복을 피하려는 이유로 한쪽을 이용해서 다른쪽을
	//구현하려는 시도는 좋은 방법이 아니다. 복사생성자는 객체 생성 시 초기화를 할때 적용되며
	//대입 연산자는 이미 존재하는 객체를 대입시킬 때 적용된다. 분명히 다른 목적으로 활용된다.
	//대신 공통 동작을 제 3의 함수에 분리해 놓고 양쪽에서 이것을 호출하는 방법을 활용할 수는 있다.

}