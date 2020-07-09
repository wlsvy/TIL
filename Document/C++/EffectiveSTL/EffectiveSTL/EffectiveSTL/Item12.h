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
#include <mutex>
#include <thread>

//STL 컨테이너가 쓰레드 안전성에 대한 기대는 현실에 맞추어 가지자

namespace Item12 {
	using namespace std;

	/*
		STL 컨테이너에 있어서의 다중쓰레딩 지원이라면 SGI(실리콘 그래픽스사)에서 제정한 방식이 가장 권위 있는 표준입니다. 
		SGI사의 STL 웹 사이트에 공개되어 있으므로 참고하면 되는데, 핵심만 설명하면 다음과 같습니다.

		- 여러 쓰레드에서 읽는 것은 안전하다(Multiple readers are safe).
		쓰레드가 하나의 컨테이너의 내용을 동시에 읽어 내는 경우가 있는데, 제대로 동작합니다. 당연한 이야기이지만 읽기 도중에 쓰기 동작이 수행되면 안 됩니다.
		
		- 여러 쓰레드에서 다른 컨테이너에 쓰는 것은 안전하다(Multiple writers to different containers are safe).
		하나 이상의 쓰레드가 다른 컨테이너에 동시에 쓸 수 있습니다.
	*/

	/*
		컨테이너의 완벽한 쓰레드 안전성을 구현하려면

		1. 컨테이너의 멤버 함수를 호출하는 시간 동안에 컨테이너에 락(lock)을 걸기.
		2. 컨테이너가 만들어 내어 주는 반복자의 유효 기간 동안에 컨테이너에 락을 걸기.
		3. 컨테이너에 대해 실행된 알고리즘의 수행 시간 동안에 컨테이너에 락을 걸기
		(사실 불가능한 이야기입니다. 알고리즘은 자신이 조작하고 있는 컨테이너를 식별할 수 있는 방법을 가지고 있지 않으니까요).
	*/

	vector<int> v(15, 5);

	inline void UnSafeSample() {

		//아래 코드가 쓰레드 안전성을 갖출 수 있도록 해봅시다.
		auto first5 = find(v.begin(), v.end(), 5);
		if (first5 != v.end()) {
			*first5 = 0;
			cout << " Change" << " Value " << endl;
		}
		

		/*
			위 코드가 쓰레드 안전성을 가지려면 v는 첫째 줄부터 셋째 줄까지 실행될 동안 계속 락이 걸린 채로 남아 있어야 합니다.
			그런데 STL 제작자가 이런 경우를 자동으로 예측해서 구현하기란 상상하기도 어렵습니다.

			게다가 쓰레드 동기화에 사용하는 기본 장치(세마포어, 뮤텍스 등)의 비용이 그리 적잖은 것을 감안하면,
			오직 하나의 쓰레드만이 첫째 줄부터 셋째 줄까지 실행할 수 있도록 작성하는 프로그램을 어떻게 "심각한 수행성능의 저하 없이" 구현할 수 있을지는 더욱 짐작하기 힘듭니다.

			STL 컨테이너에게 쓰레딩 문제 해결을 전적으로 믿고 맡길 수는 없습니다. 오히려 여러분이 직접 쓰레드 동기화를 제어해 주는 것이 낫습니다.
		*/
	}

	inline void SafeSample() {
		static std::mutex m;
		lock_guard<mutex> lock(m);

		// 이제 이 코드는 안전합니다.
		vector<int>::iterator first5(find(v.begin(), v.end(), 5));
		if (first5 != v.end()) {
			*first5 = 0;
			cout << " Change" << " Value " << endl;
		}
	}

	inline void RunSample() {
		vector<thread> workers;

		cout << "============= Unsafe Sample ==============" << endl;
		for (int i = 0; i < 15; i++) {
			workers.emplace_back(UnSafeSample);
		}
		for (auto& w : workers) {
			w.join();
		}
		
		workers.clear();
		v = vector<int>(15, 5);


		cout << "============= Safe Sample ==============" << endl;
		for (int i = 0; i < 15; i++) {
			workers.emplace_back(SafeSample);
		}
		for (auto& w : workers) {
			w.join();
		}
	}
}