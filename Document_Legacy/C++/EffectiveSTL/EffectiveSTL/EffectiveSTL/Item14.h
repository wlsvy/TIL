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

//reserve는 필요 없이 메모리가 재할당되는 것을 막아 준다

namespace Item14 {
	using namespace std;

	/*
		STL 컨테이너에 대한 가장 신통한 특징 중 하나는 프로그래머가 신경 쓰지 않아도 추가되는 요소를 담을 수 있다는 점입니다. 
		새로 넣어 주는 데이터의 개수만큼 자동으로 메모리가 늘어나기 때문이지요
		(물론 max_size를 호출하여 알 수 있는, 최대 크기를 넘도록 늘어나지는 않습니다).

		메모리가 늘어날 때 다음 네 단계의 동작이 진행됩니다.
		1. 컨테이너의 현재 용량의 몇 배가 되는 메모리 블록을 새로 할당합니다. 대부분의 제품에서는 '2'의 증가율 만큼 용량을 늘리도록 구현하고 있습니다. 즉, 컨테이너의 메모리가 증가되어야 할 필요가 있을 때 용량이 두 배씩 늘어난다는 뜻입니다.
		2. 컨테이너가 원래 가지고 있었던 메모리에 저장된 모든 요소 데이터(객체)를 새 메모리에 복사합니다.
		3. 원래의 메모리에 저장된 모든 객체를 소멸시킵니다.
		4. 원래의 메모리를 해제(dealloc)합니다.

		reserve 멤버 함수는 사용할 메모리를 미리 할당해 둠으로써 재할당의 회수를 최소화시키고, 
		아울러 메모리 재할당과 반복자/포인터/참조자의 무효화로 인해 요구되는 비용 부담을 피해갈 수 있도록 해줍니다.
	*/
	
	inline void RunSample() {
		vector<int> vi;
		cout << vi.max_size() << endl;	//4611686018427387903

		vector<char> vc;
		cout << vc.max_size() << endl;	//9223372036854775807

		vector<vector<int>> vvi;
		cout << vvi.max_size() << endl;	//576460752303423487

		{
			/*
				대부분의 라이브러리를 가지고 위의 코드를 빌드하면, 루프를 도는 동안 최소 2번에서 최대 10번의 재할당이 발생합니다
				(재할당이 일어날 때 용량이 두 배씩 불어난다고 계산하면 약 10회가 됩니다. 1000은 2의 약 10제곱이니까요).
			*/
			vector<int> v;
			for (int i = 1; i <= 1000; ++i) {
				v.push_back(i);
			}
		}
		

		{
			// 이제 루프를 도는 동안 단 한 번의 재할당도 일어나지 않습니다.
			vector<int> v;
			v.reserve(1000);
			for (int i = 1; i <= 1000; ++i) {
				v.push_back(i);
			}
		}
	}
}