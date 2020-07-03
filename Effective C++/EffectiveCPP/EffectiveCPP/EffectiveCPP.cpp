// EffectiveCPP.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include <iostream>
#include <vector>
#include <array>
#include <malloc.h>
#include <map>
#include <algorithm>
#include <math.h>

#include "EffectiveC++/Item02.h"

using namespace std;

class Widget {
public:
	int a, b, c;
};

int main()
{
	Widget w{ 1, 2, 3 };

	vector<Widget> v;
	v.emplace_back(Widget{ 1, 2, 3 });

	return 0;
}
