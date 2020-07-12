#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>

//set와 multiset에 저장된 데이터 요소에 대해 키(key)를 바꾸는 일은 피하자

namespace Item22 {
	using namespace std;

	/*
		c++ 17 이후 set/multiset 에는 extract 기능이 추가되었습니다. 컨테이너의 노드를 추출해 내부 멤버를 바꿀 때 노드를 재정렬 시킬 수 있습니다.
	
	*/

	//"set/multiset에 저장된 요소의 정보를 바꿀 때에는 바꾼 후에도 반드시 모든 요소가 정렬되어 있도록 유지해야 한다" 이 사항은 항상 염두하셔야 합니다.

	/*
		모든 표준 연관 컨테이너가 그렇듯 set과 multiset은 내부에 저장되는 데이터 요소를 정렬해서 관리하며, 컨테이너의 정상적인 동작은 요소들이 정렬된 상태에서만 가능합니다. 
		
		어떤 연관 컨테이너에 들어 있는 어떤 요소의 값을 바꾼다고 합시다. 
		바뀐 값이 제대로 된 위치에 들어가 있을 리가 만무하므로, 컨테이너의 정렬 상태는 무너지게 됩니다.
	*/

	/*
		이 법칙은 map과 multimap에서 특히 간단히 통합니다. 왜냐하면, 이 컨테이너들의 키 값을 바꾸는 일은 그 자체가 불가능하기 때문입니다.
		이유는, map<K, V> 혹은 multimap<K, V> 타입의 객체에 저장되는 요소는 pair<const K, V>이기 때문입니다.
	*/

	/*
		set이나 multiset 내의 데이터 요소의 타입이 const가 아닌 이유

		여기서 그럴듯한 가정을 하나 하는 것입니다. 
		무엇인고 하니, 직원들은 모두 유일한 식별(ID) 번호를 가지고 있도록 하며, 이 번호는 idNumber 멤버 변수로 알아낸다고 정하는 거죠. 
		직원 데이터의 set을 만들 때에는 이 식별 번호만으로 직원 데이터를 정렬하면 됩니다.

		프로그래밍적인 시각에서 볼 때, 직원의 식별 번호는 set에 저장되는 요소의 키(key) 역할을 합니다. 
		이외의 데이터들(이름이나 직위 등)은 그냥 들러리에 불과하죠. 
		이러한 경우라면 특정한 직원의 데이터를 꺼내어 직위(title)를 바꾸는 것은 전혀 불가능할 이유가 없습니다.

		그렇지만 만에 하나 키 부분을 건드리면 컨테이너는 엉망이 되고, 이 컨테이너는 예기치 못한 동작을 수행하며, 모든 책임은 여러분이 뒤집어쓰게 됩니다.
	*/
	class Employee {
	public:
		const string& gettitle(void) const { return title; }
		void setTitle(const string& title) { this->title = title; }
		int idNumber(void) const { return id; }
	private:
		string title;
		int id;
	};

	

	/*
		set/multiset의 요소가 const 타입이 아니라고 해도, 여기에 저장된 데이터 요소의 변경을 막도록 stl 라이브러리가 구현되었을 수도 있습니다.
		set<T>::iterator 에 대한 역참조가 const T& 객체를 반환하도록 한 것이 한 예입니다.

		모호한 표준안과 그것에 대한 다른 해석 때문에, set이나 multiset의 요소를 수정한 코드는 이식성에 지장을 줍니다.

		const_cast를 활용하는 방법이 있긴 하지만 역시 안전성을 고려하면 피하는 것이 낫습니다. 
		아래의 방법을 활용합시다.
	*/
	struct IDNumberLess : public binary_function<Employee, Employee, bool> {
		bool operator()(const Employee& lhs, const Employee& rhs) const
		{
			return lhs.idNumber() < rhs.idNumber();
		}
	};

	inline void RunSample() {
		set<Employee, IDNumberLess> se; 
		
		// 단계 1: 바꾸고자 하는 요소를 찾습니다.
		Employee selectedID;                   
		auto i = se.find(selectedID);
		if (i != se.end()) {
			// 단계 2: 요소를 복사합니다.
			Employee e(*i);                        

			// 단계 3: 컨테이너에서는 그 요소를 지웁니다.
			se.erase(i++);              

			// 단계 4: 복사본을 수정합니다.
			e.setTitle("Corporate Deity");     

			// 단계 5: 새 값(복사본)을 삽입합니다.
			se.insert(i, e);                   
		}
	}
}