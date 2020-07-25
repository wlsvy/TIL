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
		//컨테이너 범위 내 원소에 점진적으로 증가하는 값을 대입합니다. 아래의 경우, 컨테이너에 0 ~ 99까지의 값이 대입됩니다.(header - <numeric>)
		//iota는 그리스어에서 따온 말이라고 합니다.(가장 작은 값?? 을 뜻한다고 stack overflow에 어떤 분이 설명하셨습니다. https://stackoverflow.com/questions/9244879/what-does-iota-of-stdiota-stand-for)
		iota(vi.begin(), vi.end(), 0);

		//copy 함수를 활용해 컨테이너의 원소를 출력 스트림으로 넘기는 방법입니다.
		//for문 루프를 돌리는 방법보다 훨씬 세련되 보이지 않습니까??
		copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

		//generate_n 과 back_inserter를 활용해서 for 문 없이 벡터 원소를 채웁시다.
		vector<Widget> vw;
		generate_n(back_inserter(vw), 50, [count = 0]() mutable {return Widget(count++); });

		//연관 컨테이너는 이렇게 생성할 수 있습니다.
		set<int> si;
		generate_n(inserter(si, si.begin()), 10, [count = 1]() mutable {return count++; });

        //매우 큰 숫자에는 이렇게 구분자를 붙일 수 도 있습니다.
        constexpr long long LongValue = 400'000'000'0'0;

		//shuffle을 활용하는 방식입니다.
		vector<int> source;
		generate_n(back_inserter(source), 20, [count = 0]() mutable{return rand() % 10; });

		shuffle(source.begin(), source.end(), mt19937(random_device()()));

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
