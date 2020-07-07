#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//size()의 결과를 0과 비교할 생각이라면 차라리 empty를 호출하자

namespace Item04 {
	using namespace std;

	/*
		size()의 결과와 0을 비교하는 것은 empty()를 호출하는 것과 본질적으로 똑같습니다. 
		하지만 size()는 항상 상수 시간에 수행된다는 보장이 없고, empty()는 항상 상수 시간에 수행됩니다.
	*/
	inline void RunSample() {
		list<int> li, li2;

		if (li.size() == 0) {

		}
		if (li.empty()) {

		}

		li.splice(li.end(), li2,
			find(li2.begin(), li2.end(), 5),
			find(li2.rbegin(), li2.rend(), 10).base());
		/*
			위의 경우 list에 size 값을 담아놓는 멤버 변수가 존재합니다.
			또한 splice함수가 호출될 때, 잘리는 부분의 size를 선형 시간에 확인하는 동작이 포함됩니다.
		*/
	}

	/*
		이유는 list의 splice 함수와 밀접한 관련이 있습니다. 
		splice 함수는 객체의 복사를 하지 않고, list의 특정 요소들을 다른 list로 옮길 수 있는 함수입니다.

		list의 size()가 상수 시간에 수행되도록 하려면, 
		list 객체 내에 리스트의 요소가 몇 개 존재하는지를 담아두는 멤버를 하나 준비하고, 
		요소의 수를 변경시킬 수 있는 모든 경우에 이 멤버 변수의 값을 갱신 해야 합니다.
		
		물론 splice 함수도 마찬가지로 요소의 수를 담는 멤버 변수를 갱신 해야 하고, 
		이를 위해서 splice가 호출될 때마다 옮긴 요소의 수를 세어야 하므로, splice 함수가 상수 시간에 수행되도록 만들 수가 없게 됩니다.
		
		여러 STL 제품에서 list를 다르게 구현해 놓고 있습니다. 
		예상하고 있겠지만 구현을 맡은 개발자가 size와 splice 중 어디에 비중을 두고 있는지에 따라, splice가 상수 시간에 수행되는 대신 size가 상수 시간에 수행되지 않을 수도 있고 그 반대일 수도 있습니다.
		
		지금 쓰는 라이브러리의 list에서 size()가 상수 시간에 수행된다고 하더라도 나중에 라이브러리를 교체하거나, 
		다른 플랫폼으로 포팅할 일이 생길 지도 모릅니다. 그러므로 size()의 결과를 0과 비교하기보다는 empty()를 호출하는 것이 좋습니다.
	*/
}