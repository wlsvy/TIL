#pragma once
#include <iostream>
#include <vector>
#include <string>

//iterator ���� const_iterator�� ��ȣ�϶�

namespace Item13 {

	

	inline void RunSample() {
		std::vector<int> vec = { 1, 2, 3, 4, 5 };

		/*
			const_iterator Ȱ��, 
			
			cbegin/cend ����Լ��� c++ 11�� �Ұ��Ǿ�, �������� �� �����ϰ� const_iterator�� ����ϵ��� ���´�.
		*/

		auto it = std::find(vec.cbegin(), vec.cend(), 3);

		vec.insert(it, 6);
	}

	template<typename C, typename V>
	void findAndInert(C& container, const V& target, const V& insertVal) {
		//���� �Լ� std::cbegin/cend �� ���� const_iterator�� ��� ��
		auto it = std::find(std::cbegin(container), std::cend(container), target);

		container.insert(it, insertVal);
	}


	/*
		cbegin�� ���� ������ ��

		return���� std::begin�� Ȱ���� ������,
		const C& ��ü (���� ���, C : vector<int> �� const C& : const vector<int> &)
		�� ���ؼ�, begin �� ȣ���ϸ� const_iterator ������ �ݺ��ڰ� ��ȯ�ȴ�.
	*/
	template<class C>
	auto myCbegin(const C& container) -> decltype(std::begin(container))
	{
		return std::begin(container);
	}
}