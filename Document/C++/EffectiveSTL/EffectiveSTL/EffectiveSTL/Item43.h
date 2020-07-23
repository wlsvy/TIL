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
#include <deque>
#include <numeric>

//어설프게 손으로 작성한 루프보다는 알고리즘이 더 낫다

namespace Item43 {
	using namespace std;

	/*
		손으로 작성한 어떤 루프보다도 한 번의 알고리즘 호출이 대개 더 괜찮습니다. 더 효율적이고, 더 정확하며, 유지보수성마저 더 뛰어납니다.
		
		효율(Efficiency): 알고리즘은 프로그래머가 만든 루프보다 자주 훨씬 효율적입니다.
		정확성(Correctness): 루프를 직접 작성하면 알고리즘을 호출하는 경우보다 에러가 일어나기 쉽습니다.
		유지보수성(Maintainability): 직접 만든 루프와 비교해서, 알고리즘은 훨씬 깨끗하고 간명한 코드로 만들어져 있는 경우가 많습니다.
		 - sort, replace_if, copy, partition 등 각 알고리즘들은 어떤 동작을 하는지 명확한 이름을 포함합니다. for, while 등은 보통 그렇지 않습니다.

	*/


	class Widget {
	public:
		void redraw(void) const { cout << "Draw\n"; }
	};


	
	inline void RunSample() {

		//1. 효출
		list<Widget> lw;

		//수행시 매번 루프마다 end()를 호출해서 루프 조건을 확인합니다.
		for (list<Widget>::iterator i = lw.begin(); i != lw.end(); ++i) {
			i->redraw();
		}

		/*
			lw.end()를 정확히 한 번만 평가합니다.
			실제 for_each 내부에서는 반복자를 최적화한 방식으로 사용합니다.
		*/
		for_each(lw.begin(), lw.end(), [](const Widget& w) {w.redraw(); });

		/*
			STL 제작자들은 begin과 end(그리고 size 등의 함수들)이 아주 자주 사용된다는 사실을 파악하고 있기 때문에 
			알고리즘을 구현할 때 최대의 효율을 내는데 온 신경을 씁니다.

			알고리즘이 수작업 루프보다 효율이 좋은 두 가지의 주요 원인 중 첫 번째는 라이브러리 제작자가 컨테이너의 구현 방식을 충분히 파악하고 있기 때문에, 
			컨테이너의 횡단(traversal) 코드를 더욱 최적화시킬 수 있다는 점입니다.
			
			예를 들죠. deque에 저장된 객체는 (내부적으로) 하나 이상의 고정 크기 배열에 저장되어 있습니다. 
			이 배열은 포인터를 통해 횡단하는 것이 반복자를 사용하는 것보다 훨씬 빠릅니다.
			
			하지만 포인터 기반의 횡단을 할 수 있는 칼자루는 라이브러리 제작자만이 쥐고 있습니다. 
			왜냐하면, 그들만이 내부 배열의 크기와 배열 사이의 이동 방법을 알고 있기 때문입니다.
			
			이렇게 컨테이너의 내부 데이터 구조를 고려하여 만들어진 알고리즘은 "순진하게" 구현한 알고리즘보다 20% 정도 빠르다고 알려져 있습니다. 
			이것은 deque뿐만이 아니라 다른 컨테이너 타입도 그럴 수 있습니다.

			수작업 루프보다 알고리즘이 효율적인 두 번째 이유는, 
			가장 허접한 것을 제외한 모든 STL 알고리즘은 평범한 C++ 프로그래머의 수준으로 따라오긴 힘들 정도로 세련된 컴퓨터 공학적인 알고리즘을 사용합니다.
		*/

		//2. 정확성 : 아래는 루프를 직접 만들때 실수하기 딱 좋은 예제를 가져와 보았습니다.
		double data[100];
		iota(data, data + 100, 1);

		{
			/*
				동작은 하지만, 삽입하는 위치가 d.begin() 이기 때문에, 마지막에 삽입된 요소는 이 데크의 앞에 있게 됩니다. 
				즉, 순서가 거꾸로 뒤집어졌습니다!
			*/
			deque<int> dq;
			for (int i = 0; i < 100; i++) {
				dq.insert(dq.begin(), data[i] + 41);
			}
		}

		{
			/*
				 insert가 호출될 때마다 insertLocation를 업데이트 해서 반복자를 항상 유효한 상태로 유지한 후에 이것을 증가시킵니다.

				 드디어 여러분이 원하는 대로 동작하게 되었습니다만, 코드가 대체 몇 줄이죠?
			*/
			deque<int> dq;
			auto insertLocation = dq.begin();
			for (size_t i = 0; i < 100; ++i) {
				insertLocation = dq.insert(insertLocation, data[i] + 41);
				++insertLocation;                          
			}
		}

		{
			/*
				알고리즘을 사용한 다음의 코드와 비교해 보시죠

				data의 모든 요소에 41을 더한 결과를 dq의 앞에 복사합니다.
			*/
			deque<int> dq;
			transform(data, data + 100, inserter(dq, dq.begin()), [](int val) {return val + 41; });
		}

	}
}