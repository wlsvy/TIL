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

//�Լ��� Ŭ������ ������ ���޵ǵ���(pass-by-value) ��������

namespace Item38 {
	using namespace std;
	//c++ 11 ����

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
			�����Լ��� ������ �ϴ� ���, �Լ� �����͸� sort�� pred �Ű������� ������ ���� �ùٸ� ������ ������ �� �����ϴ�.
			�Լ� �ּҴ� �������� ���ǵǱ� ������ �������� ���� �Լ��� �����Ǵ� �����Լ��ʹ� �ٸ��ϴ�.
			
			�� ��� operator()�� �������ϴ� �Լ���ü�� �� ���縦 ����غ� �� �ֽ��ϴ�.

			�Ʒ��� �Լ���ü�� Ȱ���ϴ� ���� BigResource Ŭ������ �ӽð�ü ���� ����� �߰��� �߻��մϴ�.
			�� ��� BigResource �� �޸� ũ��� ����ϹǷ� ��� �߰������ �����ؾ� �մϴ�.
		*/
		sort(vi.begin(), vi.end(), bb);
		sort(vi.begin(), vi.end(), bd);

		//�� ��� �Ʒ��� ����� ����սô�. �ӽ� ��ü�� �������� �ʽ��ϴ�.
		//Effective Modern C++ �׸� 31 : ���� ��ü�� ������ ����� �����ֱ⸦ �Ű澲�� �͵� ���� ���ô�.
		sort(vi.begin(), vi.end(), [&bb](const auto lhs, const auto rhs) {
			return bb(lhs, rhs);
		});
		sort(vi.begin(), vi.end(), [&bd](const auto lhs, const auto rhs) {
			return bd(lhs, rhs);
		});
	}
}
