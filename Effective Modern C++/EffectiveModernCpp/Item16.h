#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <thread>
#include <mutex>
#include <atomic>

//const ��� �Լ��� �����忡 �����ϰ� �ۼ��϶�

namespace Item16 {

	class Polynomial {
	public:
		using RootsType = std::vector<double>;

		Polynomial() { std::cout << "Default Ctor" << std::endl; }

		RootsType roots(void) const	//���� �ڿ� ����
		{
			std::lock_guard<std::mutex> g(m);    

			if (!rootsAreValid) {    
				//ĳ�ð� ��ȿ���� �ʴٸ� ���� �ٽ� ���
				rootVals = RootsType(3, rootVals[0] + 1);
				rootsAreValid = true;
			}

			std::cout << "Access To Shared Memory" << rootVals[0] << std::endl;
			return rootVals;
		}                                        

	private:
		mutable std::mutex m;
		mutable bool rootsAreValid{ false };
		mutable RootsType rootVals = {0, 0, 0};
	};

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

			int magicValue() const	//���� �ڿ� ����
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
			�������� �۵�������, �������� ����� Ŭ �� �ִ�.cacheMiss�� �ѹ� �̻� �߻��Ѵ�.

			�� �����尡 magicValue ȣ��, cacheValue�� false��� �����ϰ� cachedValue ������ �����Ѵ�.
			�ι�° ������(Ȥ�� �ټ��� �ٸ� ������)�� magicValue�� ȣ��, ���� cachedValid�� false��� �����ؼ� ù �����尡 ��� ��ģ �Ͱ� ������ ������ ����
		*/
	}

	namespace UsingMutex {
		class Widget {
		public:
			using RootsType = std::vector<double>;

			int magicValue() const	//���� �ڿ� ����
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
			���� ���ÿ��� cacheMiss�� �� �ѹ��� �߻��Ѵ�. magicValue �Լ��� mutex�� ���� ��ȣ�ް� �ǹǷ�

			atomic ������ ���ؽ��� ���ؼ� ���ɻ��� ������ ������, �ϳ��� ���� �Ǵ� �޸� ��Ҹ� �ٷ� ������ �����ϴ�.
		*/
	}
}