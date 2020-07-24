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

//같은 이름을 가진 것이 있다면 일반 알고리즘 함수보다 멤버 함수가 더 낫다

namespace Item44 {
	using namespace std;
	using namespace chrono;

	/*
		컨테이너 관련 문서를 보면 STL 알고리즘과 같은 이름을 가진 멤버 함수를 찾을 수 있습니다. 
		
		연관 컨테이너는 count, find, lower_bound, upper_bound, equal_range를 제공하는가 하면, 
		list는 remove, remove_if, unique, sort, merge, reverse를 제공하지요.

		항목의 제목에서 제대로 느낄 수 있듯이 같은 이름의 알고리즘보다는 멤버 함수가 낫습니다.

		여기에는 두 가지 이유가 있는데요, 
		첫째는 멤버 함수가 빠르다는 점, 둘째는 멤버 함수는 해당 컨테이너와 더 잘 맞물려 있다는 점입니다(특히 연관 컨테이너는 더욱 그렇습니다).

		항목 19에서 이미 이야기했듯이, 
		STL 알고리즘은 두 개의 객체가 같은 값을 가지고 있는지 판단할 때 상등성(equality)을 기준으로 삼지만 
		연관 컨테이너는 동등성(equivalence)을 기준으로 삼습니다.

		이런 미묘한 차이 때문에, 
		연관 컨테이너에 find 알고리즘을 적용했을 때 헤매는 예(find 멤버를 쓰면 제대로 찾는데도 불구하고)를 항목 19에서 찾아볼 수 있습니다.

		결국 연관 컨테이너를 써서 프로그래밍 할 때에는 find, count, lower_bound 등의 작업은 알고리즘 대신에 멤버 함수를 사용하는 것이 좋다 이겁니다. 
		그 컨테이너의 다른 멤버 함수와 제대로 맞물려 동작하기 때문이죠.

		이 차이는 map과 multimap을 가지고 프로그래밍할 때에 특히 두드러집니다.

		list의 경우에도 동명의 알고리즘을 호출하는 것보다 멤버 함수를 호출하는 편이 효율적입니다. 
		게다가 list의 멤버 함수는 같은 이름의 알고리즘과 다르게 동작하는 경우가 적지 않다는 점도 꼭 기억해 두어야 합니다.
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

		//멤버 함수 버전이 알고리즘 버전보다 20배 가량 더 빠릅니다.
		{
			//멤버함수 버전은 로그시간안에 컨테이너를 조사합니다.
			auto start = high_resolution_clock::now();
			si.find(727);
			auto duration = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

			cout << duration << endl;
		}
		{
			//알고리즘 함수 버전은 set 컨테이너의 begin 부터 end 까지 선형 시간안에 조사합니다.
			auto start = high_resolution_clock::now();
			find(si.begin(), si.end(), 727);
			auto duration = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

			cout << duration << endl;
		}
	}
}