#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <functional>
#include <unordered_map>
using namespace std;

//명시적 형식 선언보다는 auto를 선호하라

namespace Item05 {
	/*
		auto는 c++11 부터 추가된 특성. 주어진 초기값에 따라 타입을 추측하는 키워드이다.
		auto를 잘 활용하면 타자(typing)량이 줄어들 뿐만 아니라 형식을 직접 지정했을 때 겪게 되는 정확성 문제와 성능 문제도 방지할 수 있다.
		하지만 auto 는 가끔 의도하지 않은 엉뚱한 타입을 추측하기도 한다.
	*/

	namespace WithoutAuto {

		template<typename It>
		void dwim(It b, It e) {
			for (; b != e; ++b) {
				typename std::iterator_traits<It>::value_type currValue = *b;
			}
		}

		std::function<bool(const std::unique_ptr<int>&, const std::unique_ptr<int>&)> derefUpLess = 
			[](const std::unique_ptr<int>& p1,
			const std::unique_ptr<int>& p2) 
		{
			return *p1 < *p2;
		};

		unsigned sz = vector<int>(4).size();

		void RunSample() {
			unordered_map<string, int> m;

			for (const std::pair<string, int>& p : m) {
				/*
					이 경우, 원래 의도는 각 원소를 참조하는 것이지만
					루프마다 임시객체가 생성되고, p는 임시객체를 참조한다.

					실제 unordered_map<string, int> 의 원소 타입은 std::pair<const std::string, int> 이다. => key 타입에 해당하는 string에 const 가 붙는다.
					즉 일반적으로 pair<const string, int> 에서 pair<string, int> 타입으로 변환시켜야 하기 때문에 컴파일러는 임시객체를 생성하게 된다.
				*/
			}
		}
	}

	namespace WithAuto {

		template<typename It>
		void dwim(It b, It e) {
			for (; b != e; ++b) {
				auto currValue = *b;
			}
		}

		/*
			람다함수 객체는 클로져 타입(컴파일러만 알고있는)
			auto 를 사용하면 클로져 타입 그대로 선언되는데, std::function을 사용하는 것보다 메모리를 절약할 수 있다.
			또한 명시적으로 function을 사용해 선언한다면 inline 화를 제한시켜 속도면에서도 제한이 생길 수 있다.
		*/
		auto derefUpLess = [](const auto& p1, const auto& p2)
		{
			return *p1 < *p2;
		};

		/*
			unsinged sz; 여기서 unsigned 는 32비트 windows에서는 32비트인 반면, 64비트 windows에선 64비트이다. -> 추후 문제 발생 가능

			반면에 auto 를 통해 size를 받으면 std::vector<int>::size_type 타입을 그대로 사용한다.
		*/
		auto sz = vector<int>(4).size();
		

		struct Widget {
			bool operator<(const Widget& rhs) {
				return false;
			}
		};

		void RunSample() {
			unordered_map<string, int> m;

			for (const auto & p : m) {
				//실제 원소의 참조값을 얻는다.
			}

			bool comp0 = derefUpLess(make_shared<Widget>(), make_shared<Widget>());
			bool comp1 = derefUpLess(make_shared<int>(3), make_shared<int>(5));
		}
	}
}
