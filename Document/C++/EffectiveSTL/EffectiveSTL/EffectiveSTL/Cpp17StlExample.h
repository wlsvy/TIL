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

namespace Example {
	using namespace std;

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

        //�ſ� ū ���ڿ��� �̷��� �����ڸ� ���� �� �� �ֽ��ϴ�.
        constexpr long long LongValue = 400'000'000'0'0;


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
