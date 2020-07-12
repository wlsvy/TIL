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

//const_iterator를 iterator로 바꾸는 데에는 distance와 advance를 사용하자

namespace Item27 {
	using namespace std;

	/*
		iterator와 const_iterator는 서로 다른 클래스 입니다. 따라서 const_cast를 통해서 const_iterator를 iterator로 변환할 수는 없습니다.
	*/

	

	inline void RunSample() {

		auto v = vector<int>(100);
		for (int i = 0; i < 100; i++) {
			v[i] = i;
		}

		{
			auto it = v.begin();
			auto cit = v.cbegin();

			//컴파일 오류. 둘은 다른 클래스입니다.
			//it = static_cast<decltype(it)>(cit); 

			/*
				it = const_cast<decltype(it)>(cit); 컴파일 오류

				단 vector와 string은 될 수도 있습니다.
				왜냐하면 vector와 string의 iterator는 T* 의 typedef 타입(const_iterator는 const T* 의 typedef 타입)일 수도 있거든요.
			*/
		}

		{
			//distance와 advance 활용 방법. 선형 시간의 비용이 듭니다.
			auto cit = v.cbegin();
			advance(cit, 20);

			auto it = v.begin();
			advance(it, distance<decltype(cit)>(it, cit));
			
			/*
				위에서 distance에 넘겨지는 매개변수는 iterator와 const_iterator입니다.
				두 클래스는 분명 다른 타입이므로 distance는 올바르게 템플릿 타입을 추론하지 못합니다.

				컴파일 실패를 방지하려면 위처럼 템플릿 매개변수를 명시적으로 지정합시다.
			*/
		}

		{
			//https://stackoverflow.com/questions/765148/how-to-remove-constness-of-const-iterator 참조
			//상수시간안에 const_iterator를 iterator로 변환하는 방법. 그러나 동작상의 또 다른 약점을 가지고 있을지도 모르겠습니다.

			auto getIterFromCiter = [](auto& container, auto constIter) {
				//유효한 범위가 아닙니다. 실제로 삭제되는 원소는 없습니다.
				return container.erase(constIter, constIter);
			};

			auto cit = v.cbegin();
			advance(cit, 20);

			auto it = getIterFromCiter(v, cit);
		}
	}

	template <typename Container, typename ConstIterator>
	typename Container::iterator remove_constness(Container& c, ConstIterator it)
	{
		//유효한 범위가 아닙니다. 실제로 삭제되는 원소는 없습니다.
		return c.erase(it, it);
	}
}