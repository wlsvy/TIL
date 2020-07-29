#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
using LL = long long;

map<LL, LL> reserved;
vector<LL> answer;

LL findLast(LL n) {
	LL res = n;
	auto it0 = reserved.find(n);
	auto it1 = it0;
	while (it1 != reserved.end()) {
		res = it1->second;
		it1 = reserved.find(it1->second);
	}
	while (it0 != it1) {
		auto tmp = reserved.find(it0->second);
		it0->second = res;
		it0 = tmp;
	}

	return res;
}

vector<long long> solution(long long k, vector<long long> room_number) {

	for (auto n : room_number) {
		auto r = findLast(n);
		reserved.insert({ r, r + 1 });
		answer.push_back(r);
	}

	return answer;
}
