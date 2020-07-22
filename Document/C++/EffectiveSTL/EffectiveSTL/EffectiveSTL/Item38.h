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

//함수자 클래스는 값으로 전달되도록(pass-by-value) 설계하자

namespace Item38 {
	using namespace std;
	//c++ 11 이후

	template<typename T>
	struct BigResourceBase {
		BigResourceBase() { std::cout << "Base default ctor" << std::endl; }
		BigResourceBase(const BigResourceBase& rhs) { std::cout << "Base copy ctor" << std::endl; }
		BigResourceBase(BigResourceBase&& rhs) noexcept { std::cout << "Base move ctor" << std::endl; }
		~BigResourceBase() { std::cout << "Base dtor" << std::endl; }

		virtual bool operator()(const T& lhs, const T& rhs) const {
			return lhs < rhs;
		}

	private:
		T BigItem[1000];
	};

	template<typename T>
	struct BigResourceDerived : public BigResourceBase<T> {
		BigResourceDerived() { std::cout << "Derived default ctor" << std::endl; }
		BigResourceDerived(const BigResourceDerived& rhs) { std::cout << "Derived copy ctor" << std::endl; }
		BigResourceDerived(BigResourceDerived&& rhs) noexcept { std::cout << "Derived move ctor" << std::endl; }
		~BigResourceDerived() { std::cout << "Derived dtor" << std::endl; }

		bool operator()(const T& lhs, const T& rhs) const override {
			return lhs % 13 < rhs % 13;
		}
	};

	inline void RunSample() {
		vector<int> vi(30);
		iota(vi.rbegin(), vi.rend(), 1);

		BigResourceBase<int> bb;
		BigResourceDerived<int> bd;

		/*
			가상함수를 재정의 하는 경우, 함수 포인터를 sort의 pred 매개변수로 보내는 것은 올바른 동작을 보장할 수 없습니다.
			함수 주소는 정적으로 정의되기 때문에 동적으로 수행 함수가 결정되는 가상함수와는 다릅니다.
			
			이 경우 operator()를 재정의하는 함수객체의 값 복사를 고려해볼 수 있습니다.

			아래는 함수객체를 활용하는 경우로 BigResource 클래스의 임시객체 생성 비용이 추가로 발생합니다.
			이 경우 BigResource 의 메모리 크기는 상당하므로 비싼 추가비용을 지불해야 합니다.
		*/
		sort(vi.begin(), vi.end(), bb);
		sort(vi.begin(), vi.end(), bd);

		//이 경우 아래의 방법을 고려합시다. 임시 객체가 생성되지 않습니다.
		//Effective Modern C++ 항목 31 : 람다 객체와 갈무리 대상의 생명주기를 신경쓰는 것도 잊지 맙시다.
		sort(vi.begin(), vi.end(), [&bb](const auto lhs, const auto rhs) {
			return bb(lhs, rhs);
		});
		sort(vi.begin(), vi.end(), [&bd](const auto lhs, const auto rhs) {
			return bd(lhs, rhs);
		});
	}
}
