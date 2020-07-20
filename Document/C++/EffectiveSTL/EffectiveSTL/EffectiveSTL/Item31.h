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

//���Ľ��� ���� ���׵��� ����� �ľ��� ����

namespace Item31 {
	using namespace std;

	/*
		1.ǥ�� ������ �����̳ʰ� �ְ� �� �����̳��� ��ҵ��� � ���ؿ� �����ϴ� �͵�� �׷��� ���� �͵��� ��� �����ϰ� �ʹٸ� partition Ȥ�� stable_partition�� ã���ʽÿ�.
		- partition
		- stable_partition

		2. vector, string, deque, Ȥ�� C++ �迭�� ���� ���� n���� ��Ҹ� �̵� ������ ����� �ʿ䰡 ���ٸ� nth_element�� �����մϴ�.
		- nth_element

		3. vector, string, deque, Ȥ�� C++ �迭�� ���� ���� n���� ��Ҹ� ������ ���߾� �̾Ƴ��� �ʹٸ� partial_sort�� ����մϴ�.
		- partial_sort  

		4. vector, string, deque, Ȥ�� C++ �迭�� ���� ��ü ������ ������ �ʿ䰡 ���� ������ sort�� stable_sort�� ����մϴ�.
		- sort			
		- stable_sort

		�۾����� ���� �˰����� �ð��� ���� �ɸ���, ������ �����ϸ� �����ϴ� �˰����� �׷��� ���� �ͺ��� �����ϴ�.
	*/

	inline void RunSample() {
		vector<int> vec(100, 0);
		for (int i = 0; i < vec.size(); i++) {
			vec[i] = vec.size() - i;
			//vec[i] = i % 31;
		}

		{
			/*
				vector, string, deque, Ȥ�� C++ �迭�� ���� ���� n���� ��Ҹ� ������ ���߾� �̾Ƴ��� �ʹٸ� partial_sort�� ����մϴ�.
				partial_sort�� ����ϸ� ���� n���� ��Ҹ� ������ ������ �� �ֽ��ϴ�. ���� n���� ���� ���ϴ� ��ҵ��� ���ĵ��� ���� ä �����ְ� �˴ϴ�. 
				�̶� ������ ���鰣 ������ �������� �ʽ��ϴ�.
			*/
			auto value = vec;
			partial_sort(value.begin(), value.begin() + 20, value.end());
		}

		
		{
			/*
				vector, string, deque, Ȥ�� C++ �迭�� ���� ���� n���� ��Ҹ� �̵� ������ ����� �ʿ䰡 ���ٸ� nth_element�� �����մϴ�.

				nth_element�� �ڽ��� ó���� ���� ���� ��ü�� �����ϵ�, n° ��ġ(�������� ������)�� �ִ� ��Ҹ� ��ü ���ĵ� ���¿� �ְԸ� �մϴ�. 
				�� �˰��� ���� ������ ���鰣 ������ �������� �ʽ��ϴ�.
			*/
			auto value = vec;
			nth_element(value.begin(), value.begin() + 20, value.end());
		}
		{
			/*
				�̷� ���� �̿��ϸ� ���� ������ ���� n���� ��Ҹ� ã�� ����(������ �������) �� �ܿ�, 
				�־��� ���� ���� �߾Ӱ�(median) Ȥ�� Ư���� �����(percentile) ��ġ�� �ִ� ���� ã�Ƴ��� ������ �� �˰����� �� �� �ֽ��ϴ�.
			*/
			auto value = vec;

			//medianIter�� �˰��� ���� ���� �߾Ӱ��� ����ŵ�ϴ�.
			auto medianIter = value.begin() + value.size() * 0.5;
			nth_element(value.begin(), medianIter, value.end());

			//percentageOffsetIter�� �˰��� ���� ���� Ư�� ����� ��ġ�� �ش��ϴ� ���� ���� ���Ҹ� ����ŵ�ϴ�.
			auto percentageOffsetIter = value.begin() + value.size() * 0.25;
			nth_element(value.begin(), percentageOffsetIter, value.end());
		}

		{
			auto isPrime = [](int val) {
				if (val < 2) return true;
				for (int i = 2; i < val; i++) {
					if (val % i == 0) return false;
				}
				return true;
			};

			/*
				ǥ�� ������ �����̳ʰ� �ְ� �� �����̳��� ��ҵ��� � ���ؿ� �����ϴ� �͵�� �׷��� ���� �͵��� ��� �����ϰ� �ʹٸ� 
				partition Ȥ�� stable_partition�� ã���ʽÿ�.

				partition�� ���� �� ������ ���鰣 ������ ���� �Ŀ� �������� ������, stable_partition�� �����˴ϴ�.

				�� �˰����� �־��� ������ �ִ� ����� ��ġ�� ��迭�ϴµ�, � ���ؿ� �´� ��Ҵ� ��� �� ������ �պκп� ���� �����ϴ�.
			*/

			auto value = vec;
			auto iter = stable_partition(value.begin(), value.end(), isPrime);
		}


		/*
			sort, stable_sort, nth_element �˰����� ���� ���� �ݺ��ڿ� �Բ� ����ؾ� �մϴ�.
			���� �̵� �˰��� ������ �� �ִ� �����̳ʴ� vector, string, deque, c++ �迭 ���Դϴ�.

			partition, stable_partition �� ����� �ݺ����̸� ��� OK��� ������ STL ǥ�� ������ �����̳� ��ο� ���� ������ �� �ֽ��ϴ�.

			����ϰ� �ִ� �����̳ʰ� list�� ��쿡, partition�� stable_partition�� ���� ����� �� �����ϴ�.
			sort�� stable_sort �˰��� ��ſ� list::sort ��� �Լ��� ����� �� �ֽ��ϴ�. 
			
			���� partial_sort�� nth_element�� ����� �ʿ��ϴٸ� �������� ��� �ۿ��� ����� ������ �Ʒ��� ���� ����� �� �ϳ��� ��쿡 ���� ������ �����ؼ� �����ϸ� �˴ϴ�.
	
			
			1. list�� ��Ҹ� ���� ���� �ݺ��ڸ� �����ϴ� �����̳ʿ� ������ ��, �� �����̳ʿ� ���ϴ� �˰����� �����ϴ� ���Դϴ�.
			2. list::iterator�� �����̳ʸ� �ϳ� �����, �� �����̳ʿ� �˰����� ������ �Ŀ� �� �ݺ��ڸ� ���� ����Ʈ ��� �����͸� �׼����ϴ� ���Դϴ�.
			3. �ݺ��ڸ� ������ ���� �����̳��� ������ �Ἥ, ���ϴ� ��ġ�� ����Ʈ�� ��� �����͸� splice�ϴ� ���Դϴ�.
		*/
	}
}