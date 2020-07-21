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

//�����͸� �����ϴ� ���� �����̳ʿ� ���ؼ��� ������ ��(�� �Լ���) Ÿ���� ��������

namespace Item20 {
	using namespace std;

	//����Ʈ �����ͳ� �ݺ��ڸ� ��� ���� �����̳ʴ� �װͿ� ���� �� Ÿ���� ������ �ּ���.

	struct StringPtrLess {
		bool operator()(const string *ps1, const string *ps2) const
		{
			return *ps1 < *ps2;
		}
	};


	//�ڵ� �ۼ��� �̷� ��찡 ���� ������ �� �Լ����� ���ø��� �ϳ� �غ��� �δ� ���� �����ϴ�.
	struct DereferenceLess {
		template <typename PtrType>
		bool operator()(PtrType pT1, PtrType pT2) const
		{                             
			return *pT1 < *pT2;
		}
	};

	inline void RunSample() {
		{
			//� ������ ���ĵ��� �𸨴ϴ�.(������ �ּڰ��� ���� ����)
			set<string*> ssp;
			ssp.insert(new string("Anteater"));
			ssp.insert(new string("Wombat"));
			ssp.insert(new string("Lemur"));
			ssp.insert(new string("Penguin"));

			for (auto ptr : ssp) {
				cout << *ptr << endl;
			}
		}
		{
			//���������� ���ĵ˴ϴ�.
			//set<string*, StringPtrLess> ssp;
			set<string*, DereferenceLess> ssp;
			ssp.insert(new string("Anteater"));
			ssp.insert(new string("Wombat"));
			ssp.insert(new string("Lemur"));
			ssp.insert(new string("Penguin"));

			for (auto ptr : ssp) {
				cout << *ptr << endl;
			}
		}

	}
}