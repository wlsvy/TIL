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

//reverse_iterator�� �����Ǵ� ���� �ݺ���(base_iterator)�� ����ϴ� ����� ��Ȯ�ϰ� ��������

namespace Item28 {
	using namespace std;

	inline void RunSample() {

		auto v = vector<int>(10);
		for (int i = 0; i < 10; i++) {
			v[i] = i;
		}

		{
			//���� ����
			auto tmp0 = v;
			auto tmp1 = v;

			auto it0 = find(tmp0.begin(), tmp0.end(), 5);
			//4, 5 ���̿� 99�� ���Ե˴ϴ�.
			tmp0.insert(it0, 99);

			//reverse_iterator�� base() �Լ��� ���� iterator�� ��ȯ�մϴ�.
			auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
			//5, 6 ���̿� 99�� ���Ե˴ϴ�.
			tmp1.insert(it1, 99);
		}
		{
			//���� ����
			auto tmp0 = v;
			auto tmp1 = v;

			auto it0 = find(tmp0.begin(), tmp0.end(), 5);
			//5�� �����˴ϴ�.
			tmp0.erase(it0);

			//reverse_iterator�� base() �Լ��� ���� iterator�� ��ȯ�մϴ�.
			auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
			//6�� �����˴ϴ�.
			tmp1.erase(it1);
		}
		{
			auto tmp = v;

			auto it = find(tmp.rbegin(), tmp.rend(), 5);
			//5�� �����˴ϴ�.
			tmp.erase((++it).base());
			/*
				�Ʒ��� ���������Դϴ�.
				tmp.erase(--it.base());
			*/
		}
	}
}