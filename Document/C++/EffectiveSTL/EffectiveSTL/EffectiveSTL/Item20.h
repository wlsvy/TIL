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

//포인터를 저장하는 연관 컨테이너에 대해서는 적합한 비교(비교 함수자) 타입을 정해주자

namespace Item20 {
	using namespace std;

	//스마트 포인터나 반복자를 담는 연관 컨테이너는 그것에 대한 비교 타입을 지정해 주세요.

	struct StringPtrLess {
		bool operator()(const string *ps1, const string *ps2) const
		{
			return *ps1 < *ps2;
		}
	};


	//코드 작성시 이런 경우가 잦을 때에는 비교 함수자의 템플릿을 하나 준비해 두는 것이 좋습니다.
	struct DereferenceLess {
		template <typename PtrType>
		bool operator()(PtrType pT1, PtrType pT2) const
		{                             
			return *pT1 < *pT2;
		}
	};

	inline void RunSample() {
		{
			//어떤 순서로 정렬될지 모릅니다.(포인터 주솟값에 따라 정렬)
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
			//정상적으로 정렬됩니다.
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