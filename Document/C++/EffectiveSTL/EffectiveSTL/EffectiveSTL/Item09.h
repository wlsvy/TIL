#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>

//�����͸� ������ ������ ���ɽ����� ������ ���� ����

namespace Item09 {
	using namespace std;

	inline void RunSample() {

		auto isBad = [](int i) { return i % 2 == 0; };

		//�����̳ʿ��� Ư���� ���� ���� ��ü�� ��� ���ַ���:
		{
			//�����̳ʰ� vector, string Ȥ�� deque�̸�, erase - remove �ռ����� ���ϴ�.
			vector<int> c;
			c.erase(remove(c.begin(), c.end(), 1963),
				c.end());
		}
		{
			//�����̳ʰ� list�̸�, list::remove�� ���ϴ�.

			/*
				list���� erase-remove �ռ����� �������� ��� �Լ��� remove�� �� ȿ�����Դϴ�.
			*/
			list<int> c;
			c.remove(1963);
		}
		{
			//�����̳ʰ� ǥ�� ���� �����̳��̸�, erase ��� �Լ��� ���ϴ�.
			multiset<int> c;
			c.erase(1963);
		}
		
		//�����̳ʿ��� Ư���� ���� ������ �����ϴ� ��ü�� ��� ���ַ���:
		{
			//�����̳ʰ� vector, string, deque�̸�, erase - remove_if �ռ����� ���ϴ�.
			vector<int> c;
			c.erase(remove_if(c.begin(), c.end(), isBad),
				c.end());
		}
		{
			//�����̳ʰ� list�̸�, list::remove_if�� ���ϴ�.
			list<int> c;
			c.remove_if(isBad);
		}
		{
			//ǥ�� ���� �����̳ʴ� �� ���� ����� �ֽ��ϴ�.
			
			multiset<int> c;
			multiset<int> goodValues;
			/*
				���� �����̳ʴ� Ʈ�� ��� ������ �����Ǳ⿡ ������ �����̳��� ���ó�� remove�� ���� ���ҵ��� ��ġ�� �ٲ������ ������ �ȵ˴ϴ�.
				remove_if(c.begin(), c.end(), [](int i) { return i % 2 == 0; }); //�ȵ˴ϴ�.
			*/

			for (int i = 0; i < 7; i++) c.insert(i);

			// �������� ���ƾ� �� ������ c���� goodValues�� �ű�ϴ�.
			remove_copy_if(c.begin(), c.end(),    
				inserter(goodValues,    
					goodValues.end()),  
				isBad);

			// c�� goodValues�� ������ �¹ٲߴϴ�.
			c.swap(goodValues);

			/*
				�� ����� ������ �������� �ʴ� ��Ҹ� ��� �����ߴٰ� �ű�� ������ ���翡 �ɸ��� ����� �츮�� ������ ���ݺ��� ��δٴ� ���Դϴ�.
			*/

			c.clear();
			for (int i = 0; i < 7; i++) c.insert(i);

			//�ι�° ��� for ����
			/*
				�����̳��� � ��Ұ� erase�� ��, �� ��Ҹ� ����Ű�� �ִ� ��� �ݺ��ڵ��� �Ѳ����� ��ȿȭ�ǰ� ���ϴ�.
				�ϴ� �ܼ��� c.erase(i)�� �Ѵٸ� ������ �����ڸ��� i�� �ٷ� ��ȿȭ�˴ϴ�.
				���� ������ ++i�κп��� ��ȿȭ�� �ݺ��ڸ� �������� ������ ���ϴ�.

				�� ������ �ذ��ϱ� ���ؼ� erase�� ȣ���ϱ� ���� �ݺ��� i�� c�� ���� ��Ҹ� ����Ű���� �����ϸ� �˴ϴ�.(postfix ++)�� Ȱ���մϴ�.
			*/
			for (auto i = c.begin(); i != c.end();) {
				//���Ҹ� �����ϴ� ��� ����� ���� �̸� �ݺ��ڸ� �Ѵܰ� ������ŵ�ϴ�.
				if (*i % 2 == 0) {
					c.erase(i++);
				}
				else {
					i++;
				}
			}
		}
		//���� �ȿ��� �����ΰ��� �Ϸ���(��ü ������ �����ؼ�)
		{
			/*
				�����̳ʰ� ǥ�� ������ �����̳��̸�, �����̳� ��Ҹ� �ϳ��� ����ϴ� ������ �ۼ��մϴ�. 
				�̶� erase�� ȣ���� ������ �� �Լ��� ��ȯ������ �ݺ��ڸ� ������Ʈ�ϴ� ���� �� �ؾ� �մϴ�.
			*/
			vector<int> c;
			for (auto i = c.begin(); i != c.end();) {
				if (isBad(*i)) {
					cout << "Erasing " << *i << '\n';

					// erase�� ��ȯ���� i�� �����ؼ� ��ȿ���� �����մϴ�.
					i = c.erase(i);        
				}                        
				else ++i;
			}
		}
		{
			/*
				���� �ȿ��� ������ �����Ϳ� ���� �α׸� ����Ѵٰ� �սô�.
				���� �����̳��� ��쿡�� ������ ���� ������ �α׸� ����ϴ� �ڵ带 �����ϱ⸸ �ϸ� �˴ϴ�.
			*/
			multiset<int> c;

			for (auto i = c.begin(); i != c.end();) {
				if (isBad(*i)) {
					cout << "Erasing " << *i << '\n'; 
					c.erase(i++);
				}
				else ++i;
			}
		}
		/*
			list�� ��� ���� �� ���� ����� ��� ����� �� ������, �Ϲ����� ���ʴ� vector/string/deque�� ���� ���ó�� list�� ó���ϴ� ���Դϴ�. 
			list�� ���������� ������ �����̳��̱� �����Դϴ�.
		*/
	}
}