//=========================
//데이터 갯수가 적어서 망정이지, 많았다면 연산 과정을 효율적으로 구현하기 위해 고생좀 많이 했을 겁니다.
//=========================

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;
using VC = vector<char>;
using VLL = vector<LL>;

LL Cal(LL l, LL r, char op) {
	switch (op) {
	case '*': return l * r;
	case '+': return l + r;
	case '-': return l - r;
	default : return 0;
	}
}

LL Cal(VC priority, VC operators, VLL numbers) {
	for (auto p : priority) {

		auto next = find_if(operators.begin(), operators.end(), [p](char c) {return c == p; });
		while (next != operators.end()) {
			auto pos = distance(operators.begin(), next);
			numbers[pos + 1] = Cal(numbers[pos], numbers[pos + 1], operators[pos]);

			numbers.erase(numbers.begin() + pos);
			operators.erase(operators.begin() + pos);
			next = find_if(operators.begin(), operators.end(), [p](char c) {return c == p; });
		}
	}
	return abs(numbers.back());
}

long long solution(string expression) {
	VLL numbers;
	VC operators;

	auto npos = find_if(expression.begin(), expression.end(), [](char c) {return c - '0' < 10; });
	auto opos = find_if(expression.begin(), expression.end(), [](char c) {return c == '*' || c == '-' || c == '+'; });
	while (npos != expression.end()) {
		string tmp(npos, opos);
		numbers.push_back(stoll(tmp));
		if (opos != expression.end()) operators.push_back(*opos);

		npos = find_if(opos + 1, expression.end(), [](char c) {return c - '0' < 10; });
		opos = find_if(npos + 1, expression.end(), [](char c) {return c == '*' || c == '-' || c == '+'; });
	}

	long long answer = 0;
	answer = max(answer, Cal({ '*', '+', '-' }, operators, numbers));
	answer = max(answer, Cal({ '*', '-', '+' }, operators, numbers));
	answer = max(answer, Cal({ '+', '*', '-' }, operators, numbers));
	answer = max(answer, Cal({ '+', '-', '*' }, operators, numbers));
	answer = max(answer, Cal({ '-', '*', '+' }, operators, numbers));
	answer = max(answer, Cal({ '-', '+', '*' }, operators, numbers));
	return answer;
}
