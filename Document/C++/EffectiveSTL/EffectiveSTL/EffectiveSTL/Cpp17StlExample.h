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

	inline void RunIosSample() {

		//ios - std::cout.width
		//ios - std::cout.fill
		//ios - std::setw
		//ios - dec, oct, hex
		//ios - boolalpha, noboolalpha (bool ǥ��)
		//ios - setprecision, precision (�Ҽ��� �ڸ���)
		//ios - showpoint, noshowpoint (�Ҽ��� ǥ��)
		//ios - showpos, noshowpos (��ȣ ǥ��)
		//ios - showbase, noshowbase
		//ios - uppercase, nouppercase
		//ios - fixed, scientific, hexfloat, defaultfloat 

		//setw, setfill
		std::cout << "default fill: " << std::setw(10) << 42 << '\n'
				  << "setfill('*'): " << std::setfill('*')
									  << std::setw(10) << 42 << '\n';
		std::cout << std::setfill(' ') << std::endl;

		/*
			default fill:         42
			setfill('*'): ********42
		*/

		//dec, hex, oct
		std::cout << "The number 42 in octal:   " << std::oct << 42 << '\n'
			<< "The number 42 in decimal: " << std::dec << 42 << '\n'
			<< "The number 42 in hex:     " << std::hex << 42 << '\n';
		std::cout << std::dec << std::endl;

		/*
			The number 42 in octal:   52
			The number 42 in decimal: 42
			The number 42 in hex:     2a
		*/

		//left, right, internal,  fill
		std::cout.fill('*');
		std::cout.imbue(std::locale("en_US.utf8"));
		std::cout << "Left fill:\n" << std::left << std::setfill('*')
			<< std::setw(12) << -1.23 << '\n'
			<< std::setw(12) << std::hex << std::showbase << 42 << '\n'
			<< std::setw(12) << std::put_money(123, true) << "\n\n";
		std::cout << "Internal fill:\n" << std::internal
			<< std::setw(12) << -1.23 << '\n'
			<< std::setw(12) << 1.23 << '\n'
			<< std::setw(12) << 42 << '\n'
			<< std::setw(12) << std::put_money(123, true) << "\n\n";
		std::cout << "Right fill:\n" << std::right
			<< std::setw(12) << -1.23 << '\n'
			<< std::setw(12) << 42 << '\n'
			<< std::setw(12) << std::put_money(123, true) << '\n';
		//std::cout.fill(' ');
		std::cout << std::setfill(' ') << std::dec << std::endl;
		/*
			Left fill:
			-1.23*******
			0x2a********
			USD1.23*****
			
			Internal fill:
			-*******1.23
			********1.23
			0x********2a
			USD*****1.23
			
			Right fill:
			*******-1.23
			********0x2a
			*****USD1.23
		*/

		struct {
			string Str;
			int interger;
			bool Boolean;
		} Values[] =
		{
			{ "Row0", 0, true},
			{ "Row1", 1, false},
			{ "Row2", 2, true},
			{ "Row3", 99, false},
			{ "Row4", -99, true},
			{ "Row5", 999, false}
		};

		std::cout.setf(std::ios::left, std::ios::adjustfield);		//���� ����
		//std::cout.setf(std::ios::right, std::ios::adjustfield);		//���� ����
		//std::cout.setf(std::ios::internal, std::ios::adjustfield);

		for (auto v : Values) {
			auto const& [str, interger, boolean] = v;

			std::cout.width(10);
			std::cout << ("| " + str) << "| ";

			std::cout.width(5);
			std::cout << interger << "| ";

			std::cout.width(10);
			std::cout << std::boolalpha << boolean << '|';

			std::cout << std::endl;
		}
		/*
			| Row0    | 0    | true      |
			| Row1    | 1    | false     |
			| Row2    | 2    | true      |
			| Row3    | 99    | false     |
			| Row4    | -99   | true      |
			| Row5    | 999  | false     |
		*/
	}
}
