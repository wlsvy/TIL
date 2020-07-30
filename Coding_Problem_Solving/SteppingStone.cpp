#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct stone {
	int next, prev;
};

map<int, vector<int>> expireCntMap;
map<int, stone> bridge;
int maxJump = 1;

int solution(vector<int> stones, int k) {
	bridge[-1] = { 0, -1 };
	bridge[stones.size()] = { (int)stones.size(), (int)stones.size() - 1 };
	for (int i = 0; i < stones.size(); i++) {
		bridge[i] = { i + 1, i - 1 };
		expireCntMap[stones[i]].push_back(i);
	}
	auto expired = expireCntMap.begin();

	while (maxJump <= k) {
		for (auto i : expired->second) {
			auto prev = bridge[i].prev;
			auto next = bridge[i].next;
			bridge[prev].next = next;
			bridge[next].prev = prev;

			maxJump = max(maxJump, next - prev);
		}

		expired++;
	}

	return (--expired)->first;
}
