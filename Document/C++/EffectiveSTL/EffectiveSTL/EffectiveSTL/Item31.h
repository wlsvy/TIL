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

//정렬시의 선택 사항들을 제대로 파악해 놓자

namespace Item31 {
	using namespace std;

	/*
		1.표준 시퀸스 컨테이너가 있고 이 컨테이너의 요소들을 어떤 기준에 만족하는 것들과 그렇지 않은 것들을 모아 구분하고 싶다면 partition 혹은 stable_partition을 찾으십시오.
		- partition
		- stable_partition

		2. vector, string, deque, 혹은 C++ 배열에 대해 상위 n개의 요소를 뽑되 순서는 고려할 필요가 없다면 nth_element가 적합합니다.
		- nth_element

		3. vector, string, deque, 혹은 C++ 배열에 대해 상위 n개의 요소만 순서에 맞추어 뽑아내고 싶다면 partial_sort를 사용합니다.
		- partial_sort  

		4. vector, string, deque, 혹은 C++ 배열에 대해 전체 정렬을 수행할 필요가 있을 때에는 sort나 stable_sort를 사용합니다.
		- sort			
		- stable_sort

		작업량이 많은 알고리즘이 시간이 오래 걸리며, 순서를 유지하며 동작하는 알고리즘이 그렇지 않은 것보다 느립니다.
	*/

	inline void RunSample() {
		vector<int> vec(100, 0);
		for (int i = 0; i < vec.size(); i++) {
			vec[i] = vec.size() - i;
			//vec[i] = i % 31;
		}

		{
			/*
				vector, string, deque, 혹은 C++ 배열에 대해 상위 n개의 요소만 순서에 맞추어 뽑아내고 싶다면 partial_sort를 사용합니다.
				partial_sort를 사용하면 상위 n개의 요소만 정렬을 수행할 수 있습니다. 상위 n개에 들지 못하는 요소들은 정렬되지 않은 채 남아있게 됩니다. 
				이때 동등한 값들간 순서는 유지되지 않습니다.
			*/
			auto value = vec;
			partial_sort(value.begin(), value.begin() + 20, value.end());
		}

		
		{
			/*
				vector, string, deque, 혹은 C++ 배열에 대해 상위 n개의 요소를 뽑되 순서는 고려할 필요가 없다면 nth_element가 적합합니다.

				nth_element는 자신이 처리할 범위 내의 객체를 정렬하되, n째 위치(여러분이 지정한)에 있는 요소만 전체 정렬된 상태에 있게만 합니다. 
				이 알고리즘 역시 동등한 값들간 순서는 유지되지 않습니다.
			*/
			auto value = vec;
			nth_element(value.begin(), value.begin() + 20, value.end());
		}
		{
			/*
				이런 점을 이용하면 범위 내에서 상위 n개의 요소를 찾아 내는(순서에 상관없이) 것 외에, 
				주어진 범위 내의 중앙값(median) 혹은 특정한 백분위(percentile) 위치에 있는 값을 찾아내는 데에도 이 알고리즘을 쓸 수 있습니다.
			*/
			auto value = vec;

			//medianIter는 알고리즘 수행 이후 중앙값을 가리킵니다.
			auto medianIter = value.begin() + value.size() * 0.5;
			nth_element(value.begin(), medianIter, value.end());

			//percentageOffsetIter는 알고리즘 수행 이후 특정 백분위 위치에 해당하는 값을 가진 원소를 가리킵니다.
			auto percentageOffsetIter = value.begin() + value.size() * 0.25;
			nth_element(value.begin(), percentageOffsetIter, value.end());
		}

		{
			auto isPrime = [](int val) {
				if (val < 2) return true;
				for (int i = 2; i < val; i++) {
					if (val % i == 0) return false;
				}
				return true;
			};

			/*
				표준 시퀸스 컨테이너가 있고 이 컨테이너의 요소들을 어떤 기준에 만족하는 것들과 그렇지 않은 것들을 모아 구분하고 싶다면 
				partition 혹은 stable_partition을 찾으십시오.

				partition은 수행 전 동등한 값들간 순서가 정렬 후에 유지되지 않지만, stable_partition은 유지됩니다.

				이 알고리즘은 주어진 범위에 있는 요소의 위치를 재배열하는데, 어떤 기준에 맞는 요소는 모두 그 범위의 앞부분에 몰아 놓습니다.
			*/

			auto value = vec;
			auto iter = stable_partition(value.begin(), value.end(), isPrime);
		}


		/*
			sort, stable_sort, nth_element 알고리즘은 임의 접근 반복자와 함께 사용해야 합니다.
			따라서 이들 알고리즘에 적용할 수 있는 컨테이너는 vector, string, deque, c++ 배열 뿐입니다.

			partition, stable_partition 은 양방향 반복자이면 모두 OK라는 점에서 STL 표준 시퀀스 컨테이너 모두에 대해 동작할 수 있습니다.

			사용하고 있는 컨테이너가 list인 경우에, partition과 stable_partition은 직접 사용할 수 없습니다.
			sort와 stable_sort 알고리즘 대신에 list::sort 멤버 함수를 사용할 수 있습니다. 
			
			만일 partial_sort나 nth_element의 기능이 필요하다면 간접적인 방법 밖에는 대안이 없지만 아래에 나온 방법들 중 하나를 경우에 따라 적절히 선택해서 구현하면 됩니다.
	
			
			1. list의 요소를 임의 접근 반복자를 지원하는 컨테이너에 복사한 후, 이 컨테이너에 원하는 알고리즘을 적용하는 것입니다.
			2. list::iterator의 컨테이너를 하나 만들고, 이 컨테이너에 알고리즘을 적용한 후에 각 반복자를 통해 리스트 요소 데이터를 액세스하는 것입니다.
			3. 반복자를 정렬해 놓은 컨테이너의 정보를 써서, 원하는 위치에 리스트의 요소 데이터를 splice하는 것입니다.
		*/
	}
}