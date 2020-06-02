#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <thread>
#include <mutex>
#include <atomic>

//const 멤버 함수를 스레드에 안전하게 작성하라

namespace Item16 {

	inline int ExpensiveComputation(int seed) {
		for (int i = 1; i < 100000; i++) {
			seed += seed % i;
		}

		return seed;
	}

	namespace UsingAtomic {
		class Widget {
		public:
			using RootsType = std::vector<double>;

			int magicValue() const	//공유 자원 접근
			{
				if (cacheValid) {
					return cachedValue;
				}
				
				std::cout << "Cache Miss" << std::endl;
				auto val1 = ExpensiveComputation(1);
				auto val2 = ExpensiveComputation(2);
				cachedValue = val1 + val2;
				cacheValid = true;
				return cachedValue;
			}

		private:
			mutable std::atomic<bool> cacheValid = false;
			mutable std::atomic<int> cachedValue = 0;
		};

		inline void RunSample() {
			Widget w;
			std::vector<thread> workers;

			for (int i = 0; i < 1000; i++) {
				workers.emplace_back(
					[&w]()
				{
					w.magicValue();
				}
				);
			}

			for (auto& t : workers) {
				t.join();
			}
		}
		/*
			문제없이 작동하지만, 생각보다 비용이 클 수 있다.cacheMiss는 한번 이상 발생한다.

			한 스레드가 magicValue 호출, cacheValue가 false라고 관측하고 cachedValue 연산을 수행한다.
			두번째 스레드(혹은 다수의 다른 스레드)가 magicValue를 호출, 역시 cachedValid가 false라고 관측해서 첫 스레드가 방금 마친 것과 동일한 계산들을 수행
		*/
	}

	namespace UsingMutex {
		class Widget {
		public:
			using RootsType = std::vector<double>;

			int magicValue() const	//공유 자원 접근
			{
				std::lock_guard<std::mutex> g(m);
				if (cacheValid) {
					return cachedValue;
				}

				std::cout << "Cache Miss" << std::endl;	
				auto val1 = ExpensiveComputation(1);
				auto val2 = ExpensiveComputation(2);
				cachedValue = val1 + val2;
				cacheValid = true;
				return cachedValue;
			}

		private:
			mutable std::mutex m;
			mutable bool cacheValid = false;
			mutable int cachedValue = 0;
		};

		inline void RunSample() {
			Widget w;
			std::vector<thread> workers;

			for (int i = 0; i < 1000; i++) {
				workers.emplace_back(
					[&w]()
				{
					w.magicValue();
				}
				);
			}

			for (auto& t : workers) {
				t.join();
			}
		}
		/*
			위의 예시에서 cacheMiss는 단 한번만 발생한다. magicValue 함수는 mutex에 의해 보호받게 되므로

			atomic 변수는 뮤텍스에 비해서 성능상의 이점이 있지만, 하나의 변수 또는 메모리 장소를 다룰 때에만 적합하다.
		*/
	}
}