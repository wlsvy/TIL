#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <functional>
#include <unordered_map>
using namespace std;

//����� ���� ���𺸴ٴ� auto�� ��ȣ�϶�

namespace Item05 {
	/*
		auto�� c++11 ���� �߰��� Ư��. �־��� �ʱⰪ�� ���� Ÿ���� �����ϴ� Ű�����̴�.
		auto�� �� Ȱ���ϸ� Ÿ��(typing)���� �پ�� �Ӹ� �ƴ϶� ������ ���� �������� �� �ް� �Ǵ� ��Ȯ�� ������ ���� ������ ������ �� �ִ�.
		������ auto �� ���� �ǵ����� ���� ������ Ÿ���� �����ϱ⵵ �Ѵ�.
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
					�� ���, ���� �ǵ��� �� ���Ҹ� �����ϴ� ��������
					�������� �ӽð�ü�� �����ǰ�, p�� �ӽð�ü�� �����Ѵ�.

					���� unordered_map<string, int> �� ���� Ÿ���� std::pair<const std::string, int> �̴�. => key Ÿ�Կ� �ش��ϴ� string�� const �� �ٴ´�.
					�� �Ϲ������� pair<const string, int> ���� pair<string, int> Ÿ������ ��ȯ���Ѿ� �ϱ� ������ �����Ϸ��� �ӽð�ü�� �����ϰ� �ȴ�.
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
			�����Լ� ��ü�� Ŭ���� Ÿ��(�����Ϸ��� �˰��ִ�)
			auto �� ����ϸ� Ŭ���� Ÿ�� �״�� ����Ǵµ�, std::function�� ����ϴ� �ͺ��� �޸𸮸� ������ �� �ִ�.
			���� ��������� function�� ����� �����Ѵٸ� inline ȭ�� ���ѽ��� �ӵ��鿡���� ������ ���� �� �ִ�.
		*/
		auto derefUpLess = [](const auto& p1, const auto& p2)
		{
			return *p1 < *p2;
		};

		/*
			unsinged sz; ���⼭ unsigned �� 32��Ʈ windows������ 32��Ʈ�� �ݸ�, 64��Ʈ windows���� 64��Ʈ�̴�. -> ���� ���� �߻� ����

			�ݸ鿡 auto �� ���� size�� ������ std::vector<int>::size_type Ÿ���� �״�� ����Ѵ�.
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
				//���� ������ �������� ��´�.
			}

			bool comp0 = derefUpLess(make_shared<Widget>(), make_shared<Widget>());
			bool comp1 = derefUpLess(make_shared<int>(3), make_shared<int>(5));
		}
	}
}
