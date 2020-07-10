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

//��� ����(equality)�� ���� ����(equivalence)�� ���̸� �ľ�����

namespace Item19 {
	using namespace std;

	//�� ��ü�� "������?"�� �˾ƺ��� ����� ��� ����� ���� ���踦 �����ϴ� ������� �������ϴ�.

	class Widget { 
	public:
		int val;
		bool other;
	};

	//��ü�� ���� �� ��� ����� Ȯ�������� �ʴ´ٰ� �սô�.
	bool operator==(const Widget & lhs, const Widget & rhs) {
		return lhs.val == rhs.val;
	}
	bool operator< (const Widget& lhs, const Widget& rhs) {
		return lhs.val < rhs.val;
	}

	inline void RunSample() {
		Widget x, y;
		x.val = 3;
		y.val = 3;

		/*
			���� operator== ���信 �Ѹ��� �Ӵϴ�.

			�̶� Widget�� ��� ������ ����� ���ٴ� �ǹ̴� �ƴմϴ�.
			operator==�� �Ϻ� ������ ����� �����ϵ��� �����Ǿ��� ���� �ֱ� �����Դϴ�.
		*/
		auto equality = x == y;
		if (equality) {
			//x�� y�� ��(���)���ϴ�
		}
		else {
			//x�� y�� �ٸ��ϴ�
		}

		/*
			�ݸ�, STL���� ����� ���ĵ� ���� �ȿ� �ִ� ��ü ������ ������� ������ ���ϰ� �ֽ��ϴ�.

			�����̳� c�� ����Ǿ� �ִ� � ��ü x, y�� �ִٰ� �� ��, x�� y ��ΰ� c�� ���� ������ ���� ������ �տ� ���� ������ x�� y�� �����ϴٰ� �մϴ�.

		*/
		auto equivalence = !(x < y) && !(y < x);
		if (equivalence) {
			//x�� y�� ��(����)���ϴ�;
		}
		else {
			//x�� y�� �ٸ��ϴ�
		}
		
		/*
			ǥ�� ���� �����̳ʿ� ����Ǵ� ������ ��Ҵ� ���ĵ� ������ �����˴ϴ�. 
			�� ������ ��� ���� �����̳ʿ��� ��ҵ��� �����ϴµ� ���Ǵ� �� �Լ�(comparison function)�� �ݵ�� �ʿ��մϴ�.
			
			����� �ٷ� �� ���Լ��� ���� ������ ���� ��������,
			���� �����̳ʸ� �ν��Ͻ�ȭ �� �� �� �Լ��� �� '�ϳ�' ������ �ִ� ���Դϴ�.(���� ������ ���ϴ� ������ 2�� �̻��̸� ����ϴϱ��)
			���� �� ��ü�� ���� �������� ������ �� ���� ������ ���̾��ٸ�, ���� �����̳ʴ� ���Ŀ� �� �Լ� ���� ���� �������� Ȯ���ϴ� �Լ��� �ϳ� �� �ʿ����� ���Դϴ�.

			��� STL������ ���� �ʿ��ϴٸ� operator==�� �ٷ� ���� ������ ���� ����Դϴ�. 
			find �˰����� �� �����Դϴ�.
		*/

		/*
			���ڿ��� ��ҹ��� ������ ���� �ʰ� ��� �񱳸� �ϴ� set �����̳� s�� �ִٰ� �����սô�.

			s.insert("Persephone");
			s.insert("persephone");
			�� ��� �ߺ��� ���� ������� �ʴ� set ���� ù ��° ���ڿ��� ���Ե����� �� ��° ���ڿ��� ���õ� ���Դϴ�.(��� ��)

			s.find("persephone");
			�� ��� find�� �� �񱳿����� �����մϴ�. �� �ش� Ž���� ������ ���Դϴ�.
		*/
	}
}