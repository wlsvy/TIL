#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

vector<int> Dist;
int N;
int answer = INT_MAX;

bool InDist(int from, int to, int dist) {
	if (to >= from && dist >= to - from) return true;
	if (from > to && dist >= N - from + to) return true;
	return false;
}
void dfs(vector<int> weaks, int cnt) {

	if (cnt >= answer) return;
	if (weaks.size() == 0) {
		answer = min(answer, cnt);
		return;
	}
	if (cnt >= Dist.size()) return;

	for (auto w : weaks) {
		auto afterRepair = weaks;
		afterRepair.erase(remove_if(afterRepair.begin(), afterRepair.end(),
			[w, cnt](int i) {return InDist(w, i, Dist[cnt]); }), afterRepair.end());
		dfs(move(afterRepair), cnt + 1);
	}
}


int solution(int n, vector<int> weak, vector<int> dist) {
	sort(dist.begin(), dist.end(), greater<int>());

	N = n;
	Dist = dist;

	dfs(move(weak), 0);

	if (answer == INT_MAX) return -1;
	return answer;
}
