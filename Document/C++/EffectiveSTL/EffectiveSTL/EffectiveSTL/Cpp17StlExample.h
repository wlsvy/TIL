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
		//컨테이너 범위 내 원소에 점진적으로 증가하는 값을 대입합니다. 아래의 경우, 컨테이너에 0 ~ 99까지의 값이 대입됩니다.(header - <numeric>)
		//iota는 그리스어에서 따온 말이라고 합니다.(가장 작은 값?? 을 뜻한다고 stack overflow에 어떤 분이 설명하셨습니다. https://stackoverflow.com/questions/9244879/what-does-iota-of-stdiota-stand-for)
		iota(vi.begin(), vi.end(), 0);

		//copy 함수를 활용해 컨테이너의 원소를 출력 스트림으로 넘기는 방법입니다.
		//for문 루프를 돌리는 방법보다 훨씬 세련되 보이지 않습니까??
		copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        //매우 큰 숫자에는 이렇게 구분자를 붙일 수 도 있습니다.
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
            //c++17 이후 numeric 헤더에 reduce가 추가되었습니다.
            const auto t1 = std::chrono::high_resolution_clock::now();
            const double result = std::reduce(std::execution::seq, v.cbegin(), v.cend());
            const auto t2 = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> ms = t2 - t1;
            std::cout << "std::reduce result "
                << result << " took " << ms.count() << " ms\n";
        }
	}
}
