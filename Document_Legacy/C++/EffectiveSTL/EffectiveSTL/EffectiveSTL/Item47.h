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
#include <numeric>

//쓰기 전용(write-only) 코드는 만들지 말자

namespace Item47 {
	using namespace std;

	/*
		쓰기 전용 코드란, 쓰기에는 쉽지만 읽고 이해하는데는 머리에 쥐가 나는, 그런 코드를 말합니다. 
		당연히 유지보수에 악영향을 주기 때문에 바람직하지 못합니다.

		코드를 쓰기보다는 읽기를 더 많이 하는 것이 소프트웨어 공학의 본질이요 이치입니다. 소프트웨어는 개발보다 유지보수에 더 많은 시간이 들어갑니다.

		읽기에 거북하고 이해하기 힘든 소프트웨어는 유지보수가 그만큼 어렵고, 유지 보수가 불가능한 소프트웨어는 있을 가치가 없습니다.
		
		꼭 기억해 두세요. 여러분이 오늘 작성한 코드는 언젠가 다른 사람들(여러분 자신일 수도 있습니다)이 읽을 거라는 사실을요.
	*/

	inline void RunSample() {
		// vector<int>가 하나 있습니다.
		vector<int> source;
		generate_n(back_inserter(source), 20, [count = 0]() mutable{return rand() % 10; });

		shuffle(source.begin(), source.end(), mt19937(random_device()()));

		int x = 5, y = 9;
		
		{
			/*
				이 벡터에서 x보다 작은 값을 모두 지우고 싶은데,
				y보다 크거나 같은 값 중 가장 마지막 것의 앞에 있는 것들은 모두 그대로 두려고 합니다.

				그리하여 다음의 코드를 만들었습니다.

				이 코드가 주목을 받는 이유는 두 가지가 있습니다.

				먼저, 이 코드는 중첩된 함수 호출의 극치를 보입니다.
				Lisp 류(함수식 언어) 프로그래밍을 해보지 않은 대다수의 사람들은 이와 같은 코드를 읽는것이 익숙하지 않을 것입니다.

				두 번째 이유는, STL에 대한 심오한 이해를 필요로 한다는 것입니다.
			*/
			auto v = source;
			v.erase(
				remove_if(
					find_if(v.rbegin(), v.rend(), [y = y](int i) {return i >= y; }).base(),
					v.end(),
					[x = x](int i) {return i < x; }),
				v.end()
			);
		}
		{
			/*
				아래처럼 고쳐봅시다.
			*/
			auto v = source;

			// rangeBegin를 y보다 크거나 같은 요소 중 가장 마지막 요소로 초기화합니다. 이런 요소가 없으면, v.begin()로 초기화합니다.
			auto rangeBegin = find_if(v.rbegin(), v.rend(), [y = y](int i) {return i >= y; }).base();

			// rangeBegin부터 v.end()까지 횡단하면서 x보다 작은 값을 모두 지웁니다.
			v.erase(remove_if(rangeBegin, v.end(), [x = x](int i) {return i < x; }), v.end());
		}
		{
			auto v = source;
			
			/*
				isgreaterequal, isless 는 부동 소수점 값(double, float 등)을 비교합니다.
				
				int값에 대해서 비교를 수행하면 내부적으로 double 형변환을 거쳐 부동소수점 비교를 수행합니다.
				적절한 예시는 아니지만 한번 적용해보았습니다.
			*/
			auto rangeBegin = find_if(v.rbegin(), v.rend(), [y = y](int i) {return isgreaterequal<int>(i, y); }).base();
			v.erase(remove_if(rangeBegin, v.end(), [x = x](int i) {return isless<int>(i, x); }), v.end());
		}
	}
}