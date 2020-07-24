#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <numeric>
#include <memory>
#include <chrono>

//���� �̸��� ���� ���� �ִٸ� �Ϲ� �˰��� �Լ����� ��� �Լ��� �� ����

namespace Item44 {
	using namespace std;
	using namespace chrono;

	/*
		�����̳� ���� ������ ���� STL �˰���� ���� �̸��� ���� ��� �Լ��� ã�� �� �ֽ��ϴ�. 
		
		���� �����̳ʴ� count, find, lower_bound, upper_bound, equal_range�� �����ϴ°� �ϸ�, 
		list�� remove, remove_if, unique, sort, merge, reverse�� ����������.

		�׸��� ���񿡼� ����� ���� �� �ֵ��� ���� �̸��� �˰��򺸴ٴ� ��� �Լ��� �����ϴ�.

		���⿡�� �� ���� ������ �ִµ���, 
		ù°�� ��� �Լ��� �����ٴ� ��, ��°�� ��� �Լ��� �ش� �����̳ʿ� �� �� �¹��� �ִٴ� ���Դϴ�(Ư�� ���� �����̳ʴ� ���� �׷����ϴ�).

		�׸� 19���� �̹� �̾߱��ߵ���, 
		STL �˰����� �� ���� ��ü�� ���� ���� ������ �ִ��� �Ǵ��� �� ��(equality)�� �������� ������ 
		���� �����̳ʴ� ���(equivalence)�� �������� ����ϴ�.

		�̷� �̹��� ���� ������, 
		���� �����̳ʿ� find �˰����� �������� �� ��Ŵ� ��(find ����� ���� ����� ã�µ��� �ұ��ϰ�)�� �׸� 19���� ã�ƺ� �� �ֽ��ϴ�.

		�ᱹ ���� �����̳ʸ� �Ἥ ���α׷��� �� ������ find, count, lower_bound ���� �۾��� �˰��� ��ſ� ��� �Լ��� ����ϴ� ���� ���� �̴̰ϴ�. 
		�� �����̳��� �ٸ� ��� �Լ��� ����� �¹��� �����ϱ� ��������.

		�� ���̴� map�� multimap�� ������ ���α׷����� ���� Ư�� �ε巯���ϴ�.

		list�� ��쿡�� ������ �˰����� ȣ���ϴ� �ͺ��� ��� �Լ��� ȣ���ϴ� ���� ȿ�����Դϴ�. 
		�Դٰ� list�� ��� �Լ��� ���� �̸��� �˰���� �ٸ��� �����ϴ� ��찡 ���� �ʴٴ� ���� �� ����� �ξ�� �մϴ�.
	*/

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(int i) : value(i) { std::cout << "Int ctor" << std::endl; }
		Widget(const Widget& rhs) : value(rhs.value) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept  : value(rhs.value) { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }

		Widget& operator=(const int i) {
			value = i;
			std::cout << "interger assign operator =" << std::endl;
			return *this;
		}

		int value;
	};

	inline void RunSample() {
		set<int> si;
		generate_n(inserter(si, si.begin()), 100000, [count = 1]() mutable {return count++; });

		//��� �Լ� ������ �˰��� �������� 20�� ���� �� �����ϴ�.
		{
			//����Լ� ������ �α׽ð��ȿ� �����̳ʸ� �����մϴ�.
			auto start = high_resolution_clock::now();
			si.find(727);
			auto duration = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

			cout << duration << endl;
		}
		{
			//�˰��� �Լ� ������ set �����̳��� begin ���� end ���� ���� �ð��ȿ� �����մϴ�.
			auto start = high_resolution_clock::now();
			find(si.begin(), si.end(), 727);
			auto duration = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

			cout << duration << endl;
		}
	}
}