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

///////////////////////////
//두 번째 방법
///////////////////////////

#include <bits/stdc++.h>
using namespace std;

long long solution(vector<vector<int> > land, int P, int Q)
{
    vector<long long > v;
    for (auto& vi : land) v.insert(v.end(), vi.begin(), vi.end());
    sort(v.begin(), v.end());

    long long temp = 0;
    for (int i = 0; i < v.size(); i++)
        temp += (v[i]-v[0]) * Q;

    long long answer = temp;

    for (int i = 1; i < v.size();i++) {

        int down = i;
        int up = v.size() - down;

        temp += down * (v[i] - v[i - 1])*P;
        temp -= up * (v[i] - v[i - 1])*Q;
        answer = min(answer, temp);
    }
    return answer;
}
