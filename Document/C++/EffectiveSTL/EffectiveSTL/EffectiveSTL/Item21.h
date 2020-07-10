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

//연관 컨테이너용 비교 함수는 같은 값에 대해 false를 반환해야 한다

namespace Item21 {
	using namespace std;

	inline void RunSample() {
		set<int, less_equal<int>> s;
		s.insert(10);
		//s.insert(10);
		/*
			less_equal <= 연산자를 활용해서 동등성 비교를 수행하면 두 개의 10은 `같지 않다`는 결과가 나타납니다.
			위의 경우, 두 개의 10을 억지로 set에 입력하려고 하며 미정의 동작을 유발할 수 있습니다.

			연관 컨테이너에 사용하는 비교 함수는 같은 값에 대해 꼭 false를 반환하게 합시다.
		*/

		multiset<int, less_equal<int>> ms;
		ms.insert(10);
		//ms.insert(10); //실행 시 오류 발생
		/*
			s가 10의 사본을 두 개 가지고 있는 것은 맞습니다. 
			이제 여기에 equal_range 알고리즘을 쓰면 두 개의 사본에 대한 범위를 지정해 주는 반복자 쌍을 얻을 수 있을 것 같습니다.
			
			하지만 그렇지 않습니다. equal_range는 같은(equal) 값의 범위를 식별하지 않습니다. 동등한(equivalent) 값의 범위를 식별하지요.

			따라서, s의 비교 함수에 의해 10A와 10B는 동등하지 않기 때문에, 이 둘이 equal_range에 의해 나오는 범위 안에 들어갈 일은 전혀 없습니다.
		*/
	}
}