#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

vector<int> Weak;
vector<int> Dist;
int N;
int answer = INT_MAX;

void dfs(vector<bool> walls, int cnt, int weakSize) {

	if (cnt >= answer) return;
	if (weakSize == 0) {
		answer = min(answer, cnt);
		return;
	}
	if (cnt >= Dist.size()) return;

	for (auto w : Weak) {
		if (!walls[w]) continue;

		auto after = walls;
		auto afterWeakSize = weakSize;
		for (int i = w; i <= w + Dist[cnt]; i++) {
			if (after[i % N]) {
				after[i % N] = false;
				afterWeakSize--;
			}
		}
		dfs(move(after), cnt + 1, afterWeakSize);
	}
}

int solution(int n, vector<int> weak, vector<int> dist) {
	sort(dist.begin(), dist.end(), greater<int>());

	N = n;
	Weak = weak;
	Dist = dist;

	vector<bool> walls(N, false);
	for_each(weak.begin(), weak.end(), [&walls](int i) {walls[i] = true; });

	dfs(move(walls), 0, Weak.size());

	if (answer == INT_MAX) return -1;
	return answer;
}
