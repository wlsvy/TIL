#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//#define 을 쓰려거든 const, enum, inline 을 떠올리자
namespace Item02 {
	using namespace std;

	class CostEstimate {
	private:
		static const double FudgeFactor; //정적 클래스 상수 선언 -> 헤더 파일에 둔다
	};
	//const double FudgeFactor = 1.5; //정적 클래스 상수의 정의 -> 구현 파일에 둔다.

	//enum을 이용한 상수 구현
	class GamePlayer {
	private:
		enum {NumTurns = 5};

		int scores[NumTurns];	//NumTurns 값은 컴파일 시간에 알 수 있다.
	};


	inline int Max(int lhs, int rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	inline void RunSample() {
		int a = 5;
		int b = 0;

		MAX(a++, b);	//a 2번 증가

		cout << a << " " << b << endl;

		Max(a++, b);	//a 1번 증가, 이상 없음

		cout << a << " " << b << endl;
	}
}