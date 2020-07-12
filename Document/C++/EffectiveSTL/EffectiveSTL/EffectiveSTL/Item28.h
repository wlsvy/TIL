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

//reverse_iterator에 대응되는 기점 반복자(base_iterator)를 사용하는 방법을 정확하게 이해하자

namespace Item28 {
	using namespace std;

	inline void RunSample() {

		auto v = vector<int>(10);
		for (int i = 0; i < 10; i++) {
			v[i] = i;
		}

		{
			//원소 삽입
			auto tmp0 = v;
			auto tmp1 = v;

			auto it0 = find(tmp0.begin(), tmp0.end(), 5);
			//4, 5 사이에 99가 삽입됩니다.
			tmp0.insert(it0, 99);

			//reverse_iterator를 base() 함수를 통해 iterator로 변환합니다.
			auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
			//5, 6 사이에 99가 삽입됩니다.
			tmp1.insert(it1, 99);
		}
		{
			//원소 삭제
			auto tmp0 = v;
			auto tmp1 = v;

			auto it0 = find(tmp0.begin(), tmp0.end(), 5);
			//5가 삭제됩니다.
			tmp0.erase(it0);

			//reverse_iterator를 base() 함수를 통해 iterator로 변환합니다.
			auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
			//6이 삭제됩니다.
			tmp1.erase(it1);
		}
		{
			auto tmp = v;

			auto it = find(tmp.rbegin(), tmp.rend(), 5);
			//5가 삭제됩니다.
			tmp.erase((++it).base());
			/*
				아래도 마찬가지입니다.
				tmp.erase(--it.base());
			*/
		}
	}
}