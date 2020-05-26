// EffectiveCPP.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include <iostream>
#include <vector>
#include <array>
#include <malloc.h>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;

struct inputtag {};
struct outputtag {};
struct forwardtag {};

class it {
public:
	using iType = inputtag;
};

class it1 {
public:
	using iType = outputtag;
};

class it2 {
public:
	using iType = forwardtag;
};

template<typename T>
void foo(T val, inputtag) { cout << "inputtag" << endl; }

template<typename T>
void foo(T val, outputtag) { cout << "outputtag" << endl; }

template<typename T>
void foo(T val, forwardtag) { cout << "forwardtag" << endl; }

template<typename T>
struct traits {
	typedef typename T::iType iType;
};

template<typename T>
void foo(T val) {
	foo(val, typename T::iType());
}

int main()
{
	it i1;
	it1 i2;
	it2 i3;
	foo(i1);
	foo(i2);
	foo(i3);


	return 0;
}
