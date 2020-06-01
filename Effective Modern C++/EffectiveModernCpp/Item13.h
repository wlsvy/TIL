#pragma once
#include <iostream>
#include <vector>
#include <string>

//iterator 보다 const_iterator를 선호하라

namespace Item13 {

	

	inline void RunSample() {
		std::vector<int> vec = { 1, 2, 3, 4, 5 };

		/*
			const_iterator 활용, 
			
			cbegin/cend 멤버함수는 c++ 11에 소개되어, 이전보다 더 간편하게 const_iterator를 사용하도록 돕는다.
		*/

		auto it = std::find(vec.cbegin(), vec.cend(), 3);

		vec.insert(it, 6);
	}

	template<typename C, typename V>
	void findAndInert(C& container, const V& target, const V& insertVal) {
		//비멤버 함수 std::cbegin/cend 를 통해 const_iterator를 얻는 예
		auto it = std::find(std::cbegin(container), std::cend(container), target);

		container.insert(it, insertVal);
	}


	/*
		cbegin을 직접 구현한 예

		return에서 std::begin을 활용한 이유는,
		const C& 객체 (예를 들어, C : vector<int> 면 const C& : const vector<int> &)
		에 대해서, begin 을 호출하면 const_iterator 형식의 반복자가 반환된다.
	*/
	template<class C>
	auto myCbegin(const C& container) -> decltype(std::begin(container))
	{
		return std::begin(container);
	}
}