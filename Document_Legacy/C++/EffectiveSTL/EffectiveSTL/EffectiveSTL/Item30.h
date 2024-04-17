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

//�˰����� ������ ��� ����(destination range)�� ����� ũ�� ����

namespace Item30 {
	using namespace std;

	/*
		������ ������ �����ؾ� �ϴ� �˰����� ����� ������ ������ �� ������ ������ ũ�⸦ �̸� Ȯ���� �ε���, 
		�˰����� ����� �� �ڵ����� �����ϵ��� ������ �մϴ�.
		
		�˰����� ����� �� ũ�⸦ ������Ű���� ���� �ݺ��ڸ� ����Ͻʽÿ�. 
		back_inserter, front_inserter, inserter�� ȣ���ؼ� ��� �ݺ��� ���Դϴ�. ostream_iterator�� ���⿡ ���Ѵٰ� �� �� �ֽ��ϴ�.

		back_inserter�� front_inserter�� inserter��, � ���� ������ ���� ������ ������ ���� ��� ��� ������ �� ���� �� ���� ��ü�� ���ؼ��� �̷�����ϴ�.
	*/

	auto transmogrify = [](int& x) { return x * 2; };

	inline void RunSample() {
		{
			vector<int> result;
			vector<int> values(5, 3);

			/*
				values�� ���Ҹ� transmogrify �� ������ ������� result.end()�� �ڸ��� ���������� �߰���ŵ�ϴ�.
				result.end()�� ��ȿ���� ���� �ڸ��̱⿡ �Ʒ� �ڵ�� �����մϴ�.
				transform(values.begin(), values.end(), result.end(), transmogrify);
			*/
			
			/*
				back_inserter�� �����̳� ���������� push_back�� ȣ���Ͽ� ���ο� ������ ����� ������ �����մϴ�.
				back_inserter�� push_back�� �����ϴ� �����̳�( vector, string, list, deque �� )�� ���� ���� �����մϴ�.
			*/
			transform(values.begin(), values.end(), back_inserter(result), transmogrify);
		}
		{
			vector<int> values;
			list<int> result;

			/*
				�ݴ�� front_inserter�� �����̳� ���������� push_front�� ȣ���ϸ�,
				��������� ���� �����̳ʿ� �ԷµǴ� ������ ������ ���� �����̳��� ���� ������ �ݴ밡 �˴ϴ�.

				���������� front_inserter�� push_front�� �����ϴ� �����̳ʿ� ���� ���� �����մϴ�.
			*/
			transform(values.begin(), values.end(), front_inserter(result), transmogrify);

			//reverse_iterator�� Ȱ���ϸ� ���� �����̳��� ���� ������ ������ �� �ֽ��ϴ�.
			transform(values.rbegin(), values.rend(), front_inserter(result), transmogrify);

			auto iter = result.begin();
			advance(iter, result.size() / 2);

			//������ ��ġ�� ���Ҹ� �Է��ϰ� �ʹٸ� inserter�� Ȱ���� �� �ֽ��ϴ�.
			transform(values.begin(), values.end(),
				inserter(result, iter),
				transmogrify);
		}

		{
			vector<int> result;
			vector<int> values(5, 3);

			result.reserve(result.size() + values.size());

			/*
				reserve�� ���� �޸� �뷮�� Ȯ���������� �Ʒ��� �ڵ�� �����մϴ�.
				�޸� �뷮�� ����ص� result.end()�� �������� ���� ��ġ��� ����� �����մϴ�.
			*/
			//transform(values.begin(), values.end(), result.end(), transmogrify);

			//�ٸ� ���� �ݺ��ڸ� Ȱ���Ѵٸ�, �뷮�� ����ϴϾƷ� ������ �����ϴ� �� �޸� ���Ҵ��� �߻������� ���� ���Դϴ�.
			transform(values.begin(), values.end(), back_inserter(result), transmogrify);
		}
	}
}