#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <climits>
using namespace std;
using LL = long long;

LL answer = 0;
LL totalPerson;

LL GetSumAndUpdateAns(LL time, vector<int>& vi) {
	LL sum = accumulate(vi.begin(), vi.end(), (LL)0, [time](LL l, LL r) {return l + time / r; });
	if (sum >= totalPerson) {
		answer = min(answer, time);
	}
	return sum;
}

long long solution(int n, vector<int> times) {

	totalPerson = n;
	sort(times.begin(), times.end());
	answer = (LL)times.back() * n;
	LL low = 0, high = (LL)times.back() * n, mid;


	while (high - low > 1) {
		mid = (high + low) / 2;
		if (GetSumAndUpdateAns(mid, times) >= totalPerson) {
			high = mid;
		}
		else {
			low = mid;
		}
	}

	for (LL i = -1; i <= 1; i++) {
		GetSumAndUpdateAns(low + i, times);
	}
	return answer;
}
