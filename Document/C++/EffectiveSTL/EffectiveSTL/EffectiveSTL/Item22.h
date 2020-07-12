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

//set�� multiset�� ����� ������ ��ҿ� ���� Ű(key)�� �ٲٴ� ���� ������

namespace Item22 {
	using namespace std;

	/*
		c++ 17 ���� set/multiset ���� extract ����� �߰��Ǿ����ϴ�. �����̳��� ��带 ������ ���� ����� �ٲ� �� ��带 ������ ��ų �� �ֽ��ϴ�.
	
	*/

	//"set/multiset�� ����� ����� ������ �ٲ� ������ �ٲ� �Ŀ��� �ݵ�� ��� ��Ұ� ���ĵǾ� �ֵ��� �����ؾ� �Ѵ�" �� ������ �׻� �����ϼž� �մϴ�.

	/*
		��� ǥ�� ���� �����̳ʰ� �׷��� set�� multiset�� ���ο� ����Ǵ� ������ ��Ҹ� �����ؼ� �����ϸ�, �����̳��� �������� ������ ��ҵ��� ���ĵ� ���¿����� �����մϴ�. 
		
		� ���� �����̳ʿ� ��� �ִ� � ����� ���� �ٲ۴ٰ� �սô�. 
		�ٲ� ���� ����� �� ��ġ�� �� ���� ���� �����ϹǷ�, �����̳��� ���� ���´� �������� �˴ϴ�.
	*/

	/*
		�� ��Ģ�� map�� multimap���� Ư�� ������ ���մϴ�. �ֳ��ϸ�, �� �����̳ʵ��� Ű ���� �ٲٴ� ���� �� ��ü�� �Ұ����ϱ� �����Դϴ�.
		������, map<K, V> Ȥ�� multimap<K, V> Ÿ���� ��ü�� ����Ǵ� ��Ҵ� pair<const K, V>�̱� �����Դϴ�.
	*/

	/*
		set�̳� multiset ���� ������ ����� Ÿ���� const�� �ƴ� ����

		���⼭ �׷����� ������ �ϳ� �ϴ� ���Դϴ�. 
		�����ΰ� �ϴ�, �������� ��� ������ �ĺ�(ID) ��ȣ�� ������ �ֵ��� �ϸ�, �� ��ȣ�� idNumber ��� ������ �˾Ƴ��ٰ� ���ϴ� ����. 
		���� �������� set�� ���� ������ �� �ĺ� ��ȣ������ ���� �����͸� �����ϸ� �˴ϴ�.

		���α׷������� �ð����� �� ��, ������ �ĺ� ��ȣ�� set�� ����Ǵ� ����� Ű(key) ������ �մϴ�. 
		�̿��� �����͵�(�̸��̳� ���� ��)�� �׳� �鷯���� �Ұ�����. 
		�̷��� ����� Ư���� ������ �����͸� ������ ����(title)�� �ٲٴ� ���� ���� �Ұ����� ������ �����ϴ�.

		�׷����� ���� �ϳ� Ű �κ��� �ǵ帮�� �����̳ʴ� ������ �ǰ�, �� �����̳ʴ� ����ġ ���� ������ �����ϸ�, ��� å���� �������� ������� �˴ϴ�.
	*/
	class Employee {
	public:
		const string& gettitle(void) const { return title; }
		void setTitle(const string& title) { this->title = title; }
		int idNumber(void) const { return id; }
	private:
		string title;
		int id;
	};

	

	/*
		set/multiset�� ��Ұ� const Ÿ���� �ƴ϶�� �ص�, ���⿡ ����� ������ ����� ������ ������ stl ���̺귯���� �����Ǿ��� ���� �ֽ��ϴ�.
		set<T>::iterator �� ���� �������� const T& ��ü�� ��ȯ�ϵ��� �� ���� �� ���Դϴ�.

		��ȣ�� ǥ�ؾȰ� �װͿ� ���� �ٸ� �ؼ� ������, set�̳� multiset�� ��Ҹ� ������ �ڵ�� �̽ļ��� ������ �ݴϴ�.

		const_cast�� Ȱ���ϴ� ����� �ֱ� ������ ���� �������� ����ϸ� ���ϴ� ���� �����ϴ�. 
		�Ʒ��� ����� Ȱ���սô�.
	*/
	struct IDNumberLess : public binary_function<Employee, Employee, bool> {
		bool operator()(const Employee& lhs, const Employee& rhs) const
		{
			return lhs.idNumber() < rhs.idNumber();
		}
	};

	inline void RunSample() {
		set<Employee, IDNumberLess> se; 
		
		// �ܰ� 1: �ٲٰ��� �ϴ� ��Ҹ� ã���ϴ�.
		Employee selectedID;                   
		auto i = se.find(selectedID);
		if (i != se.end()) {
			// �ܰ� 2: ��Ҹ� �����մϴ�.
			Employee e(*i);                        

			// �ܰ� 3: �����̳ʿ����� �� ��Ҹ� ����ϴ�.
			se.erase(i++);              

			// �ܰ� 4: ���纻�� �����մϴ�.
			e.setTitle("Corporate Deity");     

			// �ܰ� 5: �� ��(���纻)�� �����մϴ�.
			se.insert(i, e);                   
		}
	}
}