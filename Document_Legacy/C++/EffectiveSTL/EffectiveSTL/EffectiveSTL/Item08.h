#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//auto_ptr의 컨테이너는 절대로 만들지 말자

namespace Item08 {
	using namespace std;
	//c++11 이후 unique_ptr이 소개되면서 auto_ptr사용은 권장되지 않는다.

	/*
		auto_ptr의 컨테이너(COAP: Container Of A(a)uto_P(p)tr)는 절대 금지입니다. 
		COAP를 만드는 코드는 컴파일조차 되어서는 안됩니다. 
		이것 때문에 C++ 표준화 위원회에서도 말 못할 노력을 많이 했다고 합니다.

		하지만 아직 몇몇 컴파일러들이 COAP를 허용합니다.

		위의 설명과 같은 이유로, COAP를 쓰는 코드는 이식성이 떨어집니다. 
		COAP를 쓰는 코드는, 표준을 따르는(COAP를 허용하지 않는) 컴파일러와 그렇지 않은(COAP를 허용하는) 컴파일러간에 이식이 되지 않을 것입니다.

		코드의 이식성을 따지지 않는다고 해도, 이보다 더 중요한 문제가 남아있습니다. auto_ptr의 독특한 복사 방식이 문제가 됩니다.
	*/

	class Widget{
	public:
		bool operator< (const Widget& rhs) { return true; }
	};

	/*bool WidgetAPCompare(const auto_ptr<Widget>& lhs,
		const auto_ptr<Widget>& rhs)
	{
		return *lhs < *rhs;                    
	}*/

	inline void RunSample() {
		/*auto vwp = vector<auto_ptr<Widget>>();
		for (int i = 0; i < 100; i++) {
			vwp.emplace_back(new Widget);
		}*/

		//벡터 정렬 작업을 수행하고 나면, 끔찍한 결과가 나타납니다.
		//sort(vwp.begin(), vwp.end(), WidgetAPCompare);

		/*
			sort는 보통 변형된 퀵소트 알고리즘을 사용하고 있습니다.
			
			알고리즘 내부적으로 피벗 요소를 복사하는 작업이 존재하는데 해당 동작이 있을 때마다 복사되는 auto_ptr은 NULL로 세팅됩니다.

			퀵소트는 재귀 알고리즘이므로 재귀 호출이 일어날 때마다 피벗 요소를 복사해 사용하기 때문에, 
			여러 개의 벡터 요소(auto_ptr)가 NULL로 세팅되고 여러 개의 Widget이 삭제되는 경우가 다반사일 것입니다.
		*/
	}
}