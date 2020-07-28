#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using LL = long long;

LL answer = 0;
LL totalM;
vector<LL> Budgets;

LL GetSumAndUpdateAns(LL m) {

	LL sum = accumulate(Budgets.begin(), Budgets.end(), (LL)0, [m](LL l, LL r) {return l + min(r, m); });
	if (sum < totalM) {
		answer = max(answer, m);
	}
	return sum;
}

LL solution(vector<int> budgets, int M) {

	answer = 0;
	totalM = M;
	copy(budgets.begin(), budgets.end(), back_inserter(Budgets));

	LL low = 0, high = 1000000000, mid;

	if (totalM >= accumulate(Budgets.begin(), Budgets.end(), (LL)0)) {
		return *max_element(Budgets.begin(), Budgets.end());
	}

	while (high > low + 1) {
		mid = (high + low) / 2;

		if (GetSumAndUpdateAns(mid) > M) {
			high = mid ;
		}
		else {
			low = mid;
		}
	}

	for (LL i = -1; i <= 1; i++) {
		GetSumAndUpdateAns(mid + i);
	}

	return answer;
}
