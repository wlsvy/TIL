#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//#define �� �����ŵ� const, enum, inline �� ���ø���
namespace Item02 {
	using namespace std;

	class CostEstimate {
	private:
		static const double FudgeFactor; //���� Ŭ���� ��� ���� -> ��� ���Ͽ� �д�
	};
	//const double FudgeFactor = 1.5; //���� Ŭ���� ����� ���� -> ���� ���Ͽ� �д�.

	//enum�� �̿��� ��� ����
	class GamePlayer {
	private:
		enum {NumTurns = 5};

		int scores[NumTurns];	//NumTurns ���� ������ �ð��� �� �� �ִ�.
	};


	inline int Max(int lhs, int rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	inline void RunSample() {
		int a = 5;
		int b = 0;

		MAX(a++, b);	//a 2�� ����

		cout << a << " " << b << endl;

		Max(a++, b);	//a 1�� ����, �̻� ����

		cout << a << " " << b << endl;
	}
}