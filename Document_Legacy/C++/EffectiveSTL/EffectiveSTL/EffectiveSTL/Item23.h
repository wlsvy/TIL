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

//연관 컨테이너 대신에 정렬된 vector를 쓰는 것이 좋을 때가 있다

namespace Item23 {
	using namespace std;


	/*
		아래의 방식으로 자료 구조를 사용하는 애플리케이션이라면 정렬된 벡터가 연관 컨테이너보다 훨씬 나은 수행성능을 제공할 가능성이 높습니다(수행 시간과 메모리 공간 모두).

		1. 데이터 셋업(Setup)
		자료 구조를 하나 만들고, 많은 데이터 요소를 여기에 넣습니다. 
		이때 이루어지는 동작은 데이터 삽입 및 삭제가 대부분이며, 탐색은 거의 일어나지 않습니다.

		2. 데이터 탐색(Lookup)
		셋업이 끝난 자료 구조를 사용하여 원하는 정보가 들어 있는지 찾습니다. 
		이 단계에서 이루어지는 대부분의 동작은 탐색입니다. 삽입 및 삭제는 드물고요.

		3. 데이터 재구성(Reorganize)
		자료 구조에 들어 있는 내용물을 바꿉니다. 
		대개 이때 기존의 데이터를 모두 지우고 새 데이터를 집어넣게 됩니다. 
		동작상으로 볼 때 단계 1과 흡사합니다. 일단 이 단계가 끝나면, 애플리케이션은 다시 단계 2로 진입합니다.

		단 이 벡터는 반드시 정렬(sort)되어 있어야 한다는 제약이 따르죠. 
		왜냐하면 벡터의 요소가 정렬된 상태에 있을 때 binary_search, lower_bound, equal_range 등의 탐색 알고리즘을 제대로 적용할 수 있기 때문입니다
	*/

	/*
		어째서 벡터가 이진 탐색 트리에 이진 탐색을 수행하는 것보다 더 나은 것일까요? 
		이유는 크게 두 부분으로 나눌 수 있습니다. 
		
		1. 첫째 이유는 진부하지만 어쩔 수 없는 메모리 크기 문제입니다.

		연관 컨테이너를 선택하면 결국 균형 이진 트리를 사용하는 셈입니다. 
		이때 트리의 노드에는 자식을 가리키는 포인터 세개(왼쪽/오른쪽 자식, 그리고 (대개) 부모 포인터까지) 분량의 오버헤드가 추가로 붙습니다.

		반대로, Widget을 vector에 저장하는 데에는 이런 오버헤드가 없습니다. 그냥 Widget 하나가 저장될 뿐입니다.

		물론 벡터에 오버헤드가 없는 것은 아닙니다. 메모리의 여유분이 예약되어 있으니까요. 
		하지만, 벡터 자체에 걸리는 메모리 오버헤드는 그렇게 크지 않습니다. 그리고 필요 없는 메모리 여유분은 잘라낼 수도 있습니다

		2. 두 번째 이유는 덜 진부하지만 역시 사실인데, 1장에서 잠깐 언급한 메모리 참조 위치의 근접성(locality of reference)의 문제 때문입니다.

		벡터는 연속적인 메모리 구조를 취합니다. 
		하지만 연관 컨테이너는 그렇지 않습니다. 노드 간 거리가 가까워도 노드가 할당된 메모리는 연속적이라는 보장을 할 수 없습니다.

		이진 탐색 시의 페이지 오류page fault 를 최소화하기에는 벡터가 더 유리합니다.
	*/

	class Widget{};
	

	inline void SortedVector_Set() {
		//벡터를 활용해서 set을 대체해 봅시다.
		vector<int> vw;

		// 데이터 셋업 단계: 지겹게 삽입하고, 탐색은 거의 안 합니다.
		for (int i = 0; i < 10; i++) {
			vw.push_back(i);
		}

		// 셋업 단계의 끝마무리입니다.(multiset 대신에 사용하는 벡터라면 sort 대신에 stable_sort를 사용하세요.)
		sort(vw.begin(), vw.end());

		int lookUpTarget = 1;

		// 탐색 단계를 시작합니다. binary_search로 탐색합니다.
		if (binary_search(vw.begin(), vw.end(), lookUpTarget)) {
			//...
		}

		// lower_bound로 탐색합니다.
		auto i = lower_bound(vw.begin(), vw.end(), lookUpTarget);
		if (i != vw.end() && !(lookUpTarget < *i)) {
			//...
		}
		// "!(w < *i)"를 사용해서 검사하는 것에 대해서는 항목 45를 보세요.

		// equal_range로 탐색합니다.
		auto range = equal_range(vw.begin(), vw.end(), lookUpTarget);
		if (range.first != range.second) {
			//...
		}

		// 탐색 단계가 끝났습니다

		// 재구성 단계를 시작합니다.
		sort(vw.begin(), vw.end());

		// 탐색 단계를 다시 시작합니다.
	}


	using Data = pair<string, int>;

	/*
		pair에 기본적으로 주어지는 operator<는 pair의 두 멤버 데이터를 모두 고려하기 때문에, 정렬에 사용할 비교 함수를 만들어 두어야 합니다.

		여기서 주의! vector를 써서 map/multimap을 대신할 때에는 정렬용 비교 함수 외에 탐색용 비교 함수를 따로 두어야 합니다.

		정렬에 사용되는 비교 함수는 두 개의 pair 객체를 매개 변수로 받지만, 탐색은 키 값만 가지고 이루어지기 때문입니다.
	*/
	// 비교용 함수가 되는 클래스
	class DataCompare {                                        
	public:                                                    
		// 정렬용 비교 함수
		bool operator()(const Data& lhs, const Data& rhs) const
		{
			return keyLess(lhs.first, rhs.first);            
		}
		// 탐색용 비교 함수 (형태 1)
		bool operator()(const Data& lhs, const Data::first_type& k) const
		{                                                    
			return keyLess(lhs.first, k);
		}
		// 탐색용 비교 함수 (형태 2)
		bool operator()(const Data::first_type& k, const Data& rhs) const
		{                                        
			return keyLess(k, rhs.first);
		}
	private:
		// "실제"로 비교하는 함수
		bool keyLess(const Data::first_type& k1, const Data::first_type& k2) const
		{                                                    
			return k1 < k2;
		}
	};

	inline void SortedVector_Map() {
		/*
			map<K, V>타입의 객체를(multimap도 마찬가지이죠) 선언한다고 할 때 이 맵에 저장되는 요소의 타입은 pair<const K, V>입니다. 
			하지만, vector로 map이나 multimap을 흉내낼 때에는 이 const 부분을 빼어야 합니다.

			왜냐하면 벡터를 정렬할 때 각 요소의 값이 대입 연산을 통해 이동하기 때문입니다. 
			결론적으로, 벡터에 저장되는 pair 객체는 pair<K, V>로 선언되어야 합니다.
		*/

		// map<string, int> 대신에 쓰인 벡터
		vector<Data> vd;                                
		// 데이터 셋업 단계: 삽입만 많고, 탐색은 거의 안 합니다.

		// 셋업 단계의 끝 마무리입니다. (multiset 대신에 사용하는 벡터라면 sort 대신에 stable_sort를 사용하세요)
		sort(vd.begin(), vd.end(), DataCompare());        

		// 탐색하고자 하는 값을 가진 객체
		string s;                                        
		// 탐색 단계를 시작합니다.

		// binary_search로 탐색합니다.
		if (binary_search(vd.begin(), vd.end(), s, DataCompare())) {
			//...
		}
		
		// lower_bound로 탐색합니다. "!(s < i->first)"를 사용한 검사에 대해서는 역시 항목 45를 보세요.
		auto i = lower_bound(vd.begin(), vd.end(), s, DataCompare());
		if (i != vd.end() && !(s < i->first)) {
			//...
		}
		
		// equal_range로 탐색합니다.
		auto range = equal_range(vd.begin(), vd.end(), s, DataCompare());
		if (range.first != range.second) {
			//...
		}

		// 탐색 단계가 끝났습니다. 이제 재구성 단계를 시작합니다.                                                

		sort(vd.begin(), vd.end(), DataCompare());        
		// 탐색 단계를 다시 시작합니다.
	}

	inline void RunSample() {
		SortedVector_Set();
		SortedVector_Map();
	}
}