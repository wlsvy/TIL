#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//"컨테이너에 독립적인(container-independent) 코드"라는 환상을 조심하자

namespace Item02 {
	using namespace std;
	/*
		컨테이너에 독립적인 코드, 
		그러니까 vector에 대해서 작동하는 코드가 list, map, set에 대해서도 문제없이 작동할 수 있게 작성하는 시도는 좋지 않습니다.

		STL의 컨테이너들은 각각이 갖는 장단점과 특징이 있습니다. 
		만일 이 컨테이너에 독립적인 코드를 작성한다면, 각 컨테이너가 공통적으로 갖는 부분만을 이용해 코드를 작성해야 할 것입니다. 
		이는 특정 컨테이너만이 갖는 장점을 제대로 활용하기 어렵게 만듭니다.
	*/

	/*
		경우에 따라 수시로 컨테이너 타입을 바꿀 수밖에 없는 입장이라면, 변경을 조금 용이하게 해주는 방법을 쓸 수는 있습니다. 
		바로 "캡슐화"이지요. 가장 쉬운 방법은 컨테이너와 반복자 타입에 대해 별칭을 적용하는 것입니다.
	*/

	class Widget {
	};

	//책에서는 typedef를 활용했지만, 여기서는 using 사용
	//이렇게 하면 WidgetContainer의 vector를 바꾸는 것만으로 컨테이너 타입을 변경할 수 있습니다.
	using WidgetContainer = vector<Widget>;
	using WCIterator = WidgetContainer::iterator;


	inline void RunSample() {
		WidgetContainer vw;

		Widget bestWidget;
		WCIterator i = find(vw.begin(), vw.end(), bestWidget);
	}

	/*
		사실 typedef는 어떤 타입에 붙인 다른 이름에 불과하기 때문에, 이것으로 할 수 있는 캡슐화의 효과는 지극히 '문자적(lexical)'입니다. 
		항상 할 수 없는(혹은 의존할 수 없는) 것을 하지(혹은 의존하지) 못하도록 막는 장치는 가지고 있지 않습니다. 
		여러분이 만든 코드를 사용할 고객에게 '필요한' 것만 보이고 싶다면 좀 더 큰 무기인 클래스(class)를 써야 합니다.
	*/

	/*
		한 컨테이너를 다른 컨테이너로 바꿀 경우 요구되는 코드의 변경을 제한하기 위해서는 클래스에 컨테이너를 숨기고, 
		그 컨테이너에 관련된 정보 중에 필요한 것만 클래스 인터페이스를 통해 개방하면 됩니다.

		예를 들어 상품 구매자 '리스트'를 만든다고 할 때에 list를 바로 사용하지 말아야 합니다. 
		그 대신, CustomerList 클래스를 하나 만들고, private 영역에다가 list를 숨기는 것입니다.
		외부에서 별칭에 접근하지 못하게 막아 캡슐화를 높일 수 있습니다.

		별칭을 public 지정했다면 추후 CustomerList의 컨테이너 타입을 바꿔야할 일이 있을 때, 무슨 부작용이 생길지 알 수 없습니다.
	*/
	class Customer{};
	class CustomerList
	{
	private:
		using CustomerContainer = list<Customer>;
		using CCIterator = CustomerContainer::iterator;
		CustomerContainer customers;
	};
}