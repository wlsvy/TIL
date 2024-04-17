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

//정렬된 범위에 대해 동작하는 알고리즘이 어떤 것들인지 파악해 두자

namespace Item34 {
	using namespace std;

	/*
		- 정렬된 범위에 대해 동작하는 알고리즘 리스트를 먼저 한 번 봅시다.

		binary_search, lower_bound, upper_bound, equal_range
		
		set_union, set_intersection, set_difference, set_symmetric_difference
		
		merge, inplace_merge
		
		includes
		
		* 정렬된 범위에 대해 동작하는 모든 알고리즘(unique와 unique_copy를 제외하고 이번 항목에서 이야기한 모든 알고리즘)은 
		두 개의 값이 같은지를 판정할 때 동등성(equivalence)을 기준으로 삼습니다.

		- 추가로, 다음의 알고리즘은 대개 정렬된 범위에 대해 쓰이긴 하지만 꼭 그렇지 않아도 되는 것들입니다.

		unique, unique_copy
		
		* unique와 unique_copy 알고리즘의 경우에는 상등성(equality)에 의해 두 객체의 같음을 판정합니다. 
		물론 술어 구문을 작성해서 "같음"의 기준을 다시 정해줄 수도 있지요. 
	*/

	/*
		binary_search, lower_bound, upper_bound, equal_range(항목 45 참조) 등의 탐색 알고리즘은 반드시 정렬된 범위가 필요합니다. 
		내부적으로 이진 탐색을 사용해서 값을 찾거든요.
		
		이 알고리즘들은 범위 내의 데이터들을 미리 정렬해 두어야 한다는 전제조건만 지키면, 로그 시간 안에 값을 찾아 줍니다.

		사실 임의 접근 반복자를 지원하지 않는 컨테이너에 대해서는 로그 시간의 탐색 효율을 보장해주지 못합니다.

		임의 접근 반복자보다 못한 반복자(이를테면 양방향 반복자)를 쓰게 되면 비교 동작은 로그 시간 안에 일어나지만, 실행은 선형 시간 안에 끝납니다.
		왜냐하면 "반복자의 산술연산"이 되지 않아서, 한 곳에서 다른 곳으로 이동할 때 한 번에 한 칸씩밖에 이동할 수 없으니까요.
	*/

	/*
		set_union, set_intersection, set_difference, set_symmetric_difference의 알고리즘 4총사는 이름 그대로 집합(set) 조작 알고리즘이며 선형 시간의 효율을 보입니다. 
		만약 데이터가 정렬되지 않은 경우에는 선형 시간 안에 동작하는 것이 불가능해 집니다(동작이 되기는 합니다).
	*/

	/*
		merge와 inplace_merge 알고리즘은 병합 정렬(merge sort) 알고리즘의 첫 단계(pass)와 똑같은 일을 한다고 보면 됩니다. 
		즉, 두 개의 정렬된 범위를 받아 이것을 합쳐 정렬된 하나의 범위를 만드는 것이죠.
	*/

	/*
		정렬된 범위를 기반으로 동작하는 마지막 알고리즘은 includes입니다. 
		이 알고리즘은 어떤 범위 안에 우리가 원하는 값이 들어 있는지의 여부를 알아볼 때 사용합니다. 
		이 알고리즘은 자신이 받아들이는 범위내의 데이터가 정렬되어 있음을 가정하고 동작하기 때문에 선형 시간의 효율을 보입니다. 

		이렇게 되어 있지 않으면 수행속도가 느려집니다.
	*/

	/*
		지금까지 이야기한 알고리즘과 달리, unique와 unique_copy는 범위가 정렬되지 않은 상태에서도 잘 동작합니다.

		
	*/

	inline void RunSample() {
		vector<int> v(100, 0);
		for (int i = 0; i < v.size(); i++) {
			v[i] = v.size() - i;
		}
		bool a5Exists = binary_search(v.begin(), v.end(), 5);

		/*
			binary_search 알고리즘은 기본적으로 범위 내의 요소들이 "<"에 맞추어 정렬되어 있다고 가정하고 있습니다
			(즉 오름차순으로 정렬되어 있다고 가정하고 있습니다).

			하지만 위의 코드에서 벡터는 내림차순으로 정렬이 되어 있지요. 당연히 엉뚱한 결과가 도출됩니다.

			이 코드를 제대로 동작하게 하려면 binary_search에게 sort가 사용했던 동일한 비교함수를 사용하라고 알려 줘야 합니다.
		*/

		a5Exists = binary_search(v.begin(), v.end(), 5, greater());
	}
}