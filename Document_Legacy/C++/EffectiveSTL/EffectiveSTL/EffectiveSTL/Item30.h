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

//알고리즘의 데이터 기록 범위(destination range)는 충분히 크게 잡자

namespace Item30 {
	using namespace std;

	/*
		목적지 범위를 지정해야 하는 알고리즘을 사용할 때에는 언제나 이 목적지 범위의 크기를 미리 확보해 두든지, 
		알고리즘이 실행될 때 자동으로 증가하도록 만들어야 합니다.
		
		알고리즘이 실행될 때 크기를 증가시키려면 삽입 반복자를 사용하십시오. 
		back_inserter, front_inserter, inserter를 호출해서 얻는 반복자 말입니다. ostream_iterator도 여기에 속한다고 볼 수 있습니다.

		back_inserter나 front_inserter나 inserter나, 어떤 것을 쓰든지 간에 목적지 범위에 대한 결과 요소 삽입은 한 번에 한 개의 객체에 대해서만 이루어집니다.
	*/

	auto transmogrify = [](int& x) { return x * 2; };

	inline void RunSample() {
		{
			vector<int> result;
			vector<int> values(5, 3);

			/*
				values의 원소를 transmogrify 에 적용한 결과값을 result.end()의 자리에 순차적으로 추가시킵니다.
				result.end()는 유효하지 않은 자리이기에 아래 코드는 실패합니다.
				transform(values.begin(), values.end(), result.end(), transmogrify);
			*/
			
			/*
				back_inserter는 컨테이너 내부적으로 push_back을 호출하여 내부에 공간을 만들어 대입을 수행합니다.
				back_inserter는 push_back을 지원하는 컨테이너( vector, string, list, deque 등 )에 대해 적용 가능합니다.
			*/
			transform(values.begin(), values.end(), back_inserter(result), transmogrify);
		}
		{
			vector<int> values;
			list<int> result;

			/*
				반대로 front_inserter는 컨테이너 내부적으로 push_front을 호출하며,
				결과적으로 보면 컨테이너에 입력되는 원소의 순서는 기존 컨테이너의 원소 순서와 반대가 됩니다.

				마찬가지로 front_inserter는 push_front을 지원하는 컨테이너에 대해 적용 가능합니다.
			*/
			transform(values.begin(), values.end(), front_inserter(result), transmogrify);

			//reverse_iterator를 활용하면 기존 컨테이너의 원소 순서를 보존할 수 있습니다.
			transform(values.rbegin(), values.rend(), front_inserter(result), transmogrify);

			auto iter = result.begin();
			advance(iter, result.size() / 2);

			//임의의 위치에 원소를 입력하고 싶다면 inserter를 활용할 수 있습니다.
			transform(values.begin(), values.end(),
				inserter(result, iter),
				transmogrify);
		}

		{
			vector<int> result;
			vector<int> values(5, 3);

			result.reserve(result.size() + values.size());

			/*
				reserve를 통해 메모리 용량을 확보했을지라도 아래의 코드는 실패합니다.
				메모리 용량이 충분해도 result.end()가 유요하지 않은 위치라는 사실은 여전합니다.
			*/
			//transform(values.begin(), values.end(), result.end(), transmogrify);

			//다만 삽입 반복자를 활용한다면, 용량이 충분하니아래 동작을 수행하는 중 메모리 재할당이 발생하지는 않을 것입니다.
			transform(values.begin(), values.end(), back_inserter(result), transmogrify);
		}
	}
}