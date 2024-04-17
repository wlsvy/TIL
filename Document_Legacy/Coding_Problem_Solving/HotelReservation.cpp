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

//=================================================
//두번째 방법, 재귀를 활용하면 위의 과정을 더 단순화 시킬 수 있다.
//Union Find 알고리즘의 구현 방법과 비슷하다.
//=================================================

#include <string>
#include <vector>
#include <map>

using namespace std;

map<long long, long long> p;

long long find(long long x) {
    if (p[x] == 0) return x;
    else {
        p[x] = find(p[x]);
        return p[x];
    }
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for (long long x : room_number) {
        long long y = find(x);
        answer.push_back(y);
        p[y] = y + 1;
    }
    return answer;
}
