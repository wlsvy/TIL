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

//const_iterator�� iterator�� �ٲٴ� ������ distance�� advance�� �������

namespace Item27 {
	using namespace std;

	/*
		iterator�� const_iterator�� ���� �ٸ� Ŭ���� �Դϴ�. ���� const_cast�� ���ؼ� const_iterator�� iterator�� ��ȯ�� ���� �����ϴ�.
	*/

	

	inline void RunSample() {

		auto v = vector<int>(100);
		for (int i = 0; i < 100; i++) {
			v[i] = i;
		}

		{
			auto it = v.begin();
			auto cit = v.cbegin();

			//������ ����. ���� �ٸ� Ŭ�����Դϴ�.
			//it = static_cast<decltype(it)>(cit); 

			/*
				it = const_cast<decltype(it)>(cit); ������ ����

				�� vector�� string�� �� ���� �ֽ��ϴ�.
				�ֳ��ϸ� vector�� string�� iterator�� T* �� typedef Ÿ��(const_iterator�� const T* �� typedef Ÿ��)�� ���� �ְŵ��.
			*/
		}

		{
			//distance�� advance Ȱ�� ���. ���� �ð��� ����� ��ϴ�.
			auto cit = v.cbegin();
			advance(cit, 20);

			auto it = v.begin();
			advance(it, distance<decltype(cit)>(it, cit));
			
			/*
				������ distance�� �Ѱ����� �Ű������� iterator�� const_iterator�Դϴ�.
				�� Ŭ������ �и� �ٸ� Ÿ���̹Ƿ� distance�� �ùٸ��� ���ø� Ÿ���� �߷����� ���մϴ�.

				������ ���и� �����Ϸ��� ��ó�� ���ø� �Ű������� ��������� �����սô�.
			*/
		}

		{
			//https://stackoverflow.com/questions/765148/how-to-remove-constness-of-const-iterator ����
			//����ð��ȿ� const_iterator�� iterator�� ��ȯ�ϴ� ���. �׷��� ���ۻ��� �� �ٸ� ������ ������ �������� �𸣰ڽ��ϴ�.

			auto getIterFromCiter = [](auto& container, auto constIter) {
				//��ȿ�� ������ �ƴմϴ�. ������ �����Ǵ� ���Ҵ� �����ϴ�.
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
		//��ȿ�� ������ �ƴմϴ�. ������ �����Ǵ� ���Ҵ� �����ϴ�.
		return c.erase(it, it);
	}
}