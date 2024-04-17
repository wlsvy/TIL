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
#include <numeric>

//���� ����(write-only) �ڵ�� ������ ����

namespace Item47 {
	using namespace std;

	/*
		���� ���� �ڵ��, ���⿡�� ������ �а� �����ϴµ��� �Ӹ��� �㰡 ����, �׷� �ڵ带 ���մϴ�. 
		�翬�� ���������� �ǿ����� �ֱ� ������ �ٶ������� ���մϴ�.

		�ڵ带 ���⺸�ٴ� �б⸦ �� ���� �ϴ� ���� ����Ʈ���� ������ �����̿� ��ġ�Դϴ�. ����Ʈ����� ���ߺ��� ���������� �� ���� �ð��� ���ϴ�.

		�б⿡ �ź��ϰ� �����ϱ� ���� ����Ʈ����� ���������� �׸�ŭ ��ư�, ���� ������ �Ұ����� ����Ʈ����� ���� ��ġ�� �����ϴ�.
		
		�� ����� �μ���. �������� ���� �ۼ��� �ڵ�� ������ �ٸ� �����(������ �ڽ��� ���� �ֽ��ϴ�)�� ���� �Ŷ�� �������.
	*/

	inline void RunSample() {
		// vector<int>�� �ϳ� �ֽ��ϴ�.
		vector<int> source;
		generate_n(back_inserter(source), 20, [count = 0]() mutable{return rand() % 10; });

		shuffle(source.begin(), source.end(), mt19937(random_device()()));

		int x = 5, y = 9;
		
		{
			/*
				�� ���Ϳ��� x���� ���� ���� ��� ����� ������,
				y���� ũ�ų� ���� �� �� ���� ������ ���� �տ� �ִ� �͵��� ��� �״�� �η��� �մϴ�.

				�׸��Ͽ� ������ �ڵ带 ��������ϴ�.

				�� �ڵ尡 �ָ��� �޴� ������ �� ������ �ֽ��ϴ�.

				����, �� �ڵ�� ��ø�� �Լ� ȣ���� ��ġ�� ���Դϴ�.
				Lisp ��(�Լ��� ���) ���α׷����� �غ��� ���� ��ټ��� ������� �̿� ���� �ڵ带 �д°��� �ͼ����� ���� ���Դϴ�.

				�� ��° ������, STL�� ���� �ɿ��� ���ظ� �ʿ�� �Ѵٴ� ���Դϴ�.
			*/
			auto v = source;
			v.erase(
				remove_if(
					find_if(v.rbegin(), v.rend(), [y = y](int i) {return i >= y; }).base(),
					v.end(),
					[x = x](int i) {return i < x; }),
				v.end()
			);
		}
		{
			/*
				�Ʒ�ó�� ���ĺ��ô�.
			*/
			auto v = source;

			// rangeBegin�� y���� ũ�ų� ���� ��� �� ���� ������ ��ҷ� �ʱ�ȭ�մϴ�. �̷� ��Ұ� ������, v.begin()�� �ʱ�ȭ�մϴ�.
			auto rangeBegin = find_if(v.rbegin(), v.rend(), [y = y](int i) {return i >= y; }).base();

			// rangeBegin���� v.end()���� Ⱦ���ϸ鼭 x���� ���� ���� ��� ����ϴ�.
			v.erase(remove_if(rangeBegin, v.end(), [x = x](int i) {return i < x; }), v.end());
		}
		{
			auto v = source;
			
			/*
				isgreaterequal, isless �� �ε� �Ҽ��� ��(double, float ��)�� ���մϴ�.
				
				int���� ���ؼ� �񱳸� �����ϸ� ���������� double ����ȯ�� ���� �ε��Ҽ��� �񱳸� �����մϴ�.
				������ ���ô� �ƴ����� �ѹ� �����غ��ҽ��ϴ�.
			*/
			auto rangeBegin = find_if(v.rbegin(), v.rend(), [y = y](int i) {return isgreaterequal<int>(i, y); }).base();
			v.erase(remove_if(rangeBegin, v.end(), [x = x](int i) {return isless<int>(i, x); }), v.end());
		}
	}
}