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

//�˰����� �Ű� �����δ� �Լ� ��� �Լ� ��ü�� ������

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
			average<typename iterator_traits<InputIter1>::value_type>        // �����ΰ�?
		);
	}

	inline void RunSample() {
		vector<double> vd;
		generate_n(back_inserter(vd), 100, [count = 0]() mutable{return count ++; });

		std::random_device rd;
		std::mt19937 g(rd());

		shuffle(vd.begin(), vd.end(), g);

		/*
			c++ 17 ���� �Լ� ��ü�� �Լ� �����͸� �ѱ�� ��쿡 ���� ũ�� �������̰� �߻����� �ʽ��ϴ�. ���������� Ÿ�Կ� ���� ����ȭ�� ����Ǵ� ����Դϴ�.

			============å ����===================
			�Ű������� �Ѱ��� �Լ� ��ü�� operator()�� �ζ��� �Լ����, �Լ� ��ü�� operator()�� ȣ���� �� �����δ� �Լ� ȣ�� ������ �Ͼ�� �ʽ��ϴ�.

			�Լ��� �ѱ涧�� �Լ��� �����Ͱ� �Ѿ��, �� �Լ� �����͸� ���� �Լ� ȣ���� �̷�����ϴ�.
			�׷��� �� �Ѱ��� �Լ��� �ζ��� �Լ����� �ƴ����� ������� �Լ� �����͸� ���� ȣ��Ǵ� �Լ��� �ζ��ε��� �ʽ��ϴ�.

			�� ��� �Լ� ��ü�� �Ѱ��ִ� ���� �Լ��� �Ѱ��ִ� �ͺ��� �ξ� ���� ����� ������ �˴ϴ�.
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
			å���� ������ �Լ� �������� ������ ���� ȯ�濡�� �������� �ʽ��ϴ�.

			1. mem_fun_ref(c++17 ������ �����) �� Ȱ���� �������� ������ �߻��ϴ� ��찡 �ֽ��ϴ�. ������ ���ٸ� ����ϸ� �˴ϴ�.
			2. �Լ� �ν��Ͻ� �̸��� �Լ��� �̸��� ���� ���� ��� ������ ������ ����Ű�� ����.(�̰��� �÷����� ���� �ٸ� �� ����)
		*/

		set<string> s = { "Abcd", "�����ٶ󸶹ٻ�", "Effective STL", "Scott Meyers" };
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
			average<double>        // �����ΰ�? å������ �߻��� ���� �ִٰ� ���������� ���� ȯ�濡���� �߻����� �ʽ��ϴ�.
		);
		cout << endl;

		transform(
			sd.begin(), sd.end(), sd2.begin(), outDoubleStream,
			[](auto lhs, auto rhs) {return (lhs + rhs) / 2; }
		);
		cout << endl;

	}
}