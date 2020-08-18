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
#include <chrono>
#include <execution>
#include <random>
#include <iomanip>
#include <array>
#include <tuple>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace Example {
	using namespace std;

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(int i) : value(i) { std::cout << "Int ctor" << std::endl; }
		Widget(const Widget& rhs) : value(rhs.value) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept : value(rhs.value) { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }

		Widget& operator=(const int i) {
			value = i;
			std::cout << "interger assign operator =" << std::endl;
			return *this;
		}

		int value;
	};

	inline void RunSample() {
		vector<int> vi(100);

		//Fills the range [first, last) with sequentially increasing values, starting with value and repetitively evaluating ++value.
		//�����̳� ���� �� ���ҿ� ���������� �����ϴ� ���� �����մϴ�. �Ʒ��� ���, �����̳ʿ� 0 ~ 99������ ���� ���Ե˴ϴ�.(header - <numeric>)
		//iota�� �׸������ ���� ���̶�� �մϴ�.(���� ���� ��?? �� ���Ѵٰ� stack overflow�� � ���� �����ϼ̽��ϴ�. https://stackoverflow.com/questions/9244879/what-does-iota-of-stdiota-stand-for)
		iota(vi.begin(), vi.end(), 0);

		//copy �Լ��� Ȱ���� �����̳��� ���Ҹ� ��� ��Ʈ������ �ѱ�� ����Դϴ�.
		//for�� ������ ������ ������� �ξ� ���õ� ������ �ʽ��ϱ�??
		copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

		//generate_n �� back_inserter�� Ȱ���ؼ� for �� ���� ���� ���Ҹ� ä��ô�.
		vector<Widget> vw;
		generate_n(back_inserter(vw), 50, [count = 0]() mutable {return Widget(count++); });

		//���� �����̳ʴ� �̷��� ������ �� �ֽ��ϴ�.
		set<int> si;
		generate_n(inserter(si, si.begin()), 10, [count = 1]() mutable {return count++; });

        //�ſ� ū ���ڿ��� �̷��� �����ڸ� ���� �� �� �ֽ��ϴ�.
        constexpr long long LongValue = 400'000'000'0'0;

		//shuffle�� Ȱ���ϴ� ����Դϴ�.
		vector<int> source;
		generate_n(back_inserter(source), 20, [count = 0]() mutable{return rand() % 10; });

		shuffle(source.begin(), source.end(), mt19937(random_device()()));

		
		//algorithm - adjacent_find	
		//algorithm - mismatch, equal
		//algorithm - minmax, minmax_element
		//algorithm - search, search_n
		//algorithm - partition, partition_point
		//algorithm - merge, inplace_merge, include
		//algorithm - set_union(������), set_difference(������, A - B), set_intersection(������), set_symmetric_difference(������ - ������, A & B - AUB)
		//algorithm - make_heap, pop_heap, push_heap
		//iterator - prev, next
		//numeric - adjacent_difference, inner_product, partial_sum
		//numeric - iota
		//numeric - accumulate
		std::cout << "default fill: " << std::setw(10) << 42 << '\n'
			<< "setfill('*'): " << std::setfill('*')
			<< std::setw(10) << 42 << '\n';

		//=======
        const std::vector<double> v(10'000'007, 0.5);

        {
            const auto t1 = std::chrono::high_resolution_clock::now();
            const double result = std::accumulate(v.cbegin(), v.cend(), 0.0);
            const auto t2 = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> ms = t2 - t1;
            std::cout << std::fixed << "std::accumulate result " << result
                << " took " << ms.count() << " ms\n";
        }

        {
            //c++17 ���� numeric ����� reduce�� �߰��Ǿ����ϴ�.
            const auto t1 = std::chrono::high_resolution_clock::now();
            const double result = std::reduce(std::execution::seq, v.cbegin(), v.cend());
            const auto t2 = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> ms = t2 - t1;
            std::cout << "std::reduce result "
                << result << " took " << ms.count() << " ms\n";
        }
	}
}
