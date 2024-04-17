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

//���� �����̳� ��ſ� ���ĵ� vector�� ���� ���� ���� ���� �ִ�

namespace Item23 {
	using namespace std;


	/*
		�Ʒ��� ������� �ڷ� ������ ����ϴ� ���ø����̼��̶�� ���ĵ� ���Ͱ� ���� �����̳ʺ��� �ξ� ���� ���༺���� ������ ���ɼ��� �����ϴ�(���� �ð��� �޸� ���� ���).

		1. ������ �¾�(Setup)
		�ڷ� ������ �ϳ� �����, ���� ������ ��Ҹ� ���⿡ �ֽ��ϴ�. 
		�̶� �̷������ ������ ������ ���� �� ������ ��κ��̸�, Ž���� ���� �Ͼ�� �ʽ��ϴ�.

		2. ������ Ž��(Lookup)
		�¾��� ���� �ڷ� ������ ����Ͽ� ���ϴ� ������ ��� �ִ��� ã���ϴ�. 
		�� �ܰ迡�� �̷������ ��κ��� ������ Ž���Դϴ�. ���� �� ������ �幰���.

		3. ������ �籸��(Reorganize)
		�ڷ� ������ ��� �ִ� ���빰�� �ٲߴϴ�. 
		�밳 �̶� ������ �����͸� ��� ����� �� �����͸� ����ְ� �˴ϴ�. 
		���ۻ����� �� �� �ܰ� 1�� ����մϴ�. �ϴ� �� �ܰ谡 ������, ���ø����̼��� �ٽ� �ܰ� 2�� �����մϴ�.

		�� �� ���ʹ� �ݵ�� ����(sort)�Ǿ� �־�� �Ѵٴ� ������ ������. 
		�ֳ��ϸ� ������ ��Ұ� ���ĵ� ���¿� ���� �� binary_search, lower_bound, equal_range ���� Ž�� �˰����� ����� ������ �� �ֱ� �����Դϴ�
	*/

	/*
		��°�� ���Ͱ� ���� Ž�� Ʈ���� ���� Ž���� �����ϴ� �ͺ��� �� ���� ���ϱ��? 
		������ ũ�� �� �κ����� ���� �� �ֽ��ϴ�. 
		
		1. ù° ������ ���������� ��¿ �� ���� �޸� ũ�� �����Դϴ�.

		���� �����̳ʸ� �����ϸ� �ᱹ ���� ���� Ʈ���� ����ϴ� ���Դϴ�. 
		�̶� Ʈ���� ��忡�� �ڽ��� ����Ű�� ������ ����(����/������ �ڽ�, �׸��� (�밳) �θ� �����ͱ���) �з��� ������尡 �߰��� �ٽ��ϴ�.

		�ݴ��, Widget�� vector�� �����ϴ� ������ �̷� ������尡 �����ϴ�. �׳� Widget �ϳ��� ����� ���Դϴ�.

		���� ���Ϳ� ������尡 ���� ���� �ƴմϴ�. �޸��� �������� ����Ǿ� �����ϱ��. 
		������, ���� ��ü�� �ɸ��� �޸� �������� �׷��� ũ�� �ʽ��ϴ�. �׸��� �ʿ� ���� �޸� �������� �߶� ���� �ֽ��ϴ�

		2. �� ��° ������ �� ���������� ���� ����ε�, 1�忡�� ��� ����� �޸� ���� ��ġ�� ������(locality of reference)�� ���� �����Դϴ�.

		���ʹ� �������� �޸� ������ ���մϴ�. 
		������ ���� �����̳ʴ� �׷��� �ʽ��ϴ�. ��� �� �Ÿ��� ������� ��尡 �Ҵ�� �޸𸮴� �������̶�� ������ �� �� �����ϴ�.

		���� Ž�� ���� ������ ����page fault �� �ּ�ȭ�ϱ⿡�� ���Ͱ� �� �����մϴ�.
	*/

	class Widget{};
	

	inline void SortedVector_Set() {
		//���͸� Ȱ���ؼ� set�� ��ü�� ���ô�.
		vector<int> vw;

		// ������ �¾� �ܰ�: ����� �����ϰ�, Ž���� ���� �� �մϴ�.
		for (int i = 0; i < 10; i++) {
			vw.push_back(i);
		}

		// �¾� �ܰ��� ���������Դϴ�.(multiset ��ſ� ����ϴ� ���Ͷ�� sort ��ſ� stable_sort�� ����ϼ���.)
		sort(vw.begin(), vw.end());

		int lookUpTarget = 1;

		// Ž�� �ܰ踦 �����մϴ�. binary_search�� Ž���մϴ�.
		if (binary_search(vw.begin(), vw.end(), lookUpTarget)) {
			//...
		}

		// lower_bound�� Ž���մϴ�.
		auto i = lower_bound(vw.begin(), vw.end(), lookUpTarget);
		if (i != vw.end() && !(lookUpTarget < *i)) {
			//...
		}
		// "!(w < *i)"�� ����ؼ� �˻��ϴ� �Ϳ� ���ؼ��� �׸� 45�� ������.

		// equal_range�� Ž���մϴ�.
		auto range = equal_range(vw.begin(), vw.end(), lookUpTarget);
		if (range.first != range.second) {
			//...
		}

		// Ž�� �ܰ谡 �������ϴ�

		// �籸�� �ܰ踦 �����մϴ�.
		sort(vw.begin(), vw.end());

		// Ž�� �ܰ踦 �ٽ� �����մϴ�.
	}


	using Data = pair<string, int>;

	/*
		pair�� �⺻������ �־����� operator<�� pair�� �� ��� �����͸� ��� ����ϱ� ������, ���Ŀ� ����� �� �Լ��� ����� �ξ�� �մϴ�.

		���⼭ ����! vector�� �Ἥ map/multimap�� ����� ������ ���Ŀ� �� �Լ� �ܿ� Ž���� �� �Լ��� ���� �ξ�� �մϴ�.

		���Ŀ� ���Ǵ� �� �Լ��� �� ���� pair ��ü�� �Ű� ������ ������, Ž���� Ű ���� ������ �̷������ �����Դϴ�.
	*/
	// �񱳿� �Լ��� �Ǵ� Ŭ����
	class DataCompare {                                        
	public:                                                    
		// ���Ŀ� �� �Լ�
		bool operator()(const Data& lhs, const Data& rhs) const
		{
			return keyLess(lhs.first, rhs.first);            
		}
		// Ž���� �� �Լ� (���� 1)
		bool operator()(const Data& lhs, const Data::first_type& k) const
		{                                                    
			return keyLess(lhs.first, k);
		}
		// Ž���� �� �Լ� (���� 2)
		bool operator()(const Data::first_type& k, const Data& rhs) const
		{                                        
			return keyLess(k, rhs.first);
		}
	private:
		// "����"�� ���ϴ� �Լ�
		bool keyLess(const Data::first_type& k1, const Data::first_type& k2) const
		{                                                    
			return k1 < k2;
		}
	};

	inline void SortedVector_Map() {
		/*
			map<K, V>Ÿ���� ��ü��(multimap�� ������������) �����Ѵٰ� �� �� �� �ʿ� ����Ǵ� ����� Ÿ���� pair<const K, V>�Դϴ�. 
			������, vector�� map�̳� multimap�� �䳻�� ������ �� const �κ��� ����� �մϴ�.

			�ֳ��ϸ� ���͸� ������ �� �� ����� ���� ���� ������ ���� �̵��ϱ� �����Դϴ�. 
			���������, ���Ϳ� ����Ǵ� pair ��ü�� pair<K, V>�� ����Ǿ�� �մϴ�.
		*/

		// map<string, int> ��ſ� ���� ����
		vector<Data> vd;                                
		// ������ �¾� �ܰ�: ���Ը� ����, Ž���� ���� �� �մϴ�.

		// �¾� �ܰ��� �� �������Դϴ�. (multiset ��ſ� ����ϴ� ���Ͷ�� sort ��ſ� stable_sort�� ����ϼ���)
		sort(vd.begin(), vd.end(), DataCompare());        

		// Ž���ϰ��� �ϴ� ���� ���� ��ü
		string s;                                        
		// Ž�� �ܰ踦 �����մϴ�.

		// binary_search�� Ž���մϴ�.
		if (binary_search(vd.begin(), vd.end(), s, DataCompare())) {
			//...
		}
		
		// lower_bound�� Ž���մϴ�. "!(s < i->first)"�� ����� �˻翡 ���ؼ��� ���� �׸� 45�� ������.
		auto i = lower_bound(vd.begin(), vd.end(), s, DataCompare());
		if (i != vd.end() && !(s < i->first)) {
			//...
		}
		
		// equal_range�� Ž���մϴ�.
		auto range = equal_range(vd.begin(), vd.end(), s, DataCompare());
		if (range.first != range.second) {
			//...
		}

		// Ž�� �ܰ谡 �������ϴ�. ���� �籸�� �ܰ踦 �����մϴ�.                                                

		sort(vd.begin(), vd.end(), DataCompare());        
		// Ž�� �ܰ踦 �ٽ� �����մϴ�.
	}

	inline void RunSample() {
		SortedVector_Set();
		SortedVector_Map();
	}
}