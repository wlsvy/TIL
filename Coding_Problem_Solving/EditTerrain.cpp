#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<LL> oneDimensionLand;
vector<LL> accum;
LL answer = LONG_MAX;
LL Pcost, Qcost;

LL updateAnswer(LL height) {
	auto it = upper_bound(oneDimensionLand.begin(), oneDimensionLand.end(), height);
	LL pos = distance(oneDimensionLand.begin(), it);

	LL ctCost = Pcost * (LL)(pos * height - accum[pos - 1]);
	LL dtCost = Qcost * (LL)((oneDimensionLand.size() - pos) * height - (accum.back() - accum[pos - 1]));
	LL cost = abs(ctCost) + abs(dtCost);
	answer = min(answer, cost);
	return cost;
}

long long solution(vector<vector<int> > land, int P, int Q) {
	Pcost = P;
	Qcost = Q;

	for (auto& vi : land) oneDimensionLand.insert(oneDimensionLand.end(), vi.begin(), vi.end());

	sort(oneDimensionLand.begin(), oneDimensionLand.end());
	accum = oneDimensionLand;
	for (int i = 1; i < accum.size(); i++) {
		accum[i] += accum[i - 1];
	}

	LL high = oneDimensionLand.back();
	LL low = oneDimensionLand.front();

	while (high - low > 400000) {
		LL mid = (high + low) / 2;
		LL hcost = updateAnswer(high);
		LL lcost = updateAnswer(low);
		LL mcost = updateAnswer(mid);
		if (mcost <= hcost && mcost <= lcost) {
			high = (high + mid) / 2;
			low = (low + mid) / 2;
		}
		else if (hcost > lcost) high = mid;
		else low = mid;
	}
	for (LL h = low; h <= high; h++) {
		updateAnswer(h);
	}

	return answer;
}
