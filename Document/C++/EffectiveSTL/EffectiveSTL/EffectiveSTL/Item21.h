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

//���� �����̳ʿ� �� �Լ��� ���� ���� ���� false�� ��ȯ�ؾ� �Ѵ�

namespace Item21 {
	using namespace std;

	inline void RunSample() {
		set<int, less_equal<int>> s;
		s.insert(10);
		//s.insert(10);
		/*
			less_equal <= �����ڸ� Ȱ���ؼ� ��� �񱳸� �����ϸ� �� ���� 10�� `���� �ʴ�`�� ����� ��Ÿ���ϴ�.
			���� ���, �� ���� 10�� ������ set�� �Է��Ϸ��� �ϸ� ������ ������ ������ �� �ֽ��ϴ�.

			���� �����̳ʿ� ����ϴ� �� �Լ��� ���� ���� ���� �� false�� ��ȯ�ϰ� �սô�.
		*/

		multiset<int, less_equal<int>> ms;
		ms.insert(10);
		//ms.insert(10); //���� �� ���� �߻�
		/*
			s�� 10�� �纻�� �� �� ������ �ִ� ���� �½��ϴ�. 
			���� ���⿡ equal_range �˰����� ���� �� ���� �纻�� ���� ������ ������ �ִ� �ݺ��� ���� ���� �� ���� �� �����ϴ�.
			
			������ �׷��� �ʽ��ϴ�. equal_range�� ����(equal) ���� ������ �ĺ����� �ʽ��ϴ�. ������(equivalent) ���� ������ �ĺ�������.

			����, s�� �� �Լ��� ���� 10A�� 10B�� �������� �ʱ� ������, �� ���� equal_range�� ���� ������ ���� �ȿ� �� ���� ���� �����ϴ�.
		*/
	}
}