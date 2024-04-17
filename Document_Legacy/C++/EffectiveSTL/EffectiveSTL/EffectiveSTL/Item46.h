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
#include <random>

//알고리즘의 매개 변수로는 함수 대신 함수 객체가 괜찮다

namespace Item46 {
	using namespace std;
	using namespace chrono;
	

	inline bool DoubleCompare(double lhs, double rhs) { return lhs > rhs; }
	inline size_t GetStringSize(const string& s) { return s.size(); }

	template <typename T>
	T average(T val1, T val2)
	{
		return (val1 + val2) / 2;
	}
	

	template <typename InputIter1,
		typename InputIter2>
		void writeAverage(InputIter1 begin1,
			InputIter1 end1,
			InputIter2 begin2,
			ostream& s)
	{
		transform(
			begin1, end1, begin2,
			ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s, "\n"),
			average<typename iterator_traits<InputIter1>::value_type>        // 에러인가?
		);
	}

	inline void RunSample() {
		vector<double> vd;
		generate_n(back_inserter(vd), 100, [count = 0]() mutable{return count ++; });

		std::random_device rd;
		std::mt19937 g(rd());

		shuffle(vd.begin(), vd.end(), g);

		/*
			c++ 17 기준 함수 객체와 함수 포인터를 넘기는 경우에 따라서 크게 성능차이가 발생하지 않습니다. 내부적으로 타입에 따른 최적화가 진행되는 모양입니다.

			============책 설명===================
			매개변수로 넘겨진 함수 객체의 operator()가 인라인 함수라면, 함수 객체의 operator()를 호출할 때 실제로는 함수 호출 과정이 일어나지 않습니다.

			함수를 넘길때는 함수의 포인터가 넘어가며, 이 함수 포인터를 통해 함수 호출이 이루어집니다.
			그런데 이 넘겨진 함수가 인라인 함수인지 아닌지에 상관없이 함수 포인터를 통해 호출되는 함수는 인라인되지 않습니다.

			그 결과 함수 객체를 넘겨주는 것이 함수를 넘겨주는 것보다 훨씬 빠른 결과가 나오게 됩니다.
		*/

		{
			auto target = vd;

			auto start = high_resolution_clock::now();
			sort(target.begin(), target.end(), greater<>());
			auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
			cout << "greater<double> : " << duration << endl;
		}
		{
			auto target = vd;

			auto start = high_resolution_clock::now();
			sort(target.begin(), target.end(), DoubleCompare);
			auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
			cout << "Function Pointer : " << duration << endl;
		}
		{
			auto target = vd;

			auto start = high_resolution_clock::now();
			sort(target.begin(), target.end(), [](double lhs, double rhs) {return lhs > rhs; });
			auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
			cout << "Lambda : " << duration << endl;
		}
		{
			auto target = vd;

			struct {
				bool operator()(double lhs, double rhs) { return lhs > rhs; };
			} Comparer;

			auto start = high_resolution_clock::now();
			sort(target.begin(), target.end(), Comparer);
			auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
			cout << "Functor : " << duration << endl;
		}
		{
			auto target = vd;

			struct {
				inline bool operator()(double lhs, double rhs) { return lhs > rhs; };
			} Comparer;

			auto start = high_resolution_clock::now();
			sort(target.begin(), target.end(), Comparer);
			auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
			cout << "Functor with inline operator : " << duration << endl;
		}

		/*
			책에서 설명한 함수 포인터의 단점은 현재 환경에서 문제되지 않습니다.

			1. mem_fun_ref(c++17 에서는 사라진) 을 활용한 예제에서 문제가 발생하는 경우가 있습니다. 지금은 람다를 사용하면 됩니다.
			2. 함수 인스턴스 이름이 함수의 이름과 같지 않은 경우 컴파일 에러를 일으키는 문제.(이것은 플랫폼에 따라 다를 수 있음)
		*/

		set<string> s = { "Abcd", "가나다라마바사", "Effective STL", "Scott Meyers" };
		set<string> s2 = { "DEFC", "Effective", "Errrrr...", "Lion" };

		const auto outSizeTStream = ostream_iterator<size_t>(cout, " ");
		transform(s.begin(), s.end(), outSizeTStream, GetStringSize);
		cout << endl;
		transform(s.begin(), s.end(), outSizeTStream, [](const string& s) {return s.size(); });
		cout << endl;

		set<double> sd{ 1.4, 2.46, 3.98 }, sd2{ 21.89, 72.13, 93.2 };

		const auto outDoubleStream = ostream_iterator<double>(cout, " ");
		transform(
			sd.begin(), sd.end(), sd2.begin(), outDoubleStream,
			average<double>        // 에러인가? 책에서는 발생할 수도 있다고 설명하지만 현재 환경에서는 발생하지 않습니다.
		);
		cout << endl;

		transform(
			sd.begin(), sd.end(), sd2.begin(), outDoubleStream,
			[](auto lhs, auto rhs) {return (lhs + rhs) / 2; }
		);
		cout << endl;

	}
}