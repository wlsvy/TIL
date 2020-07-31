#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<string> uid, bid;
set<int> answer;
bool check[10];

void dfs(int index, int mask) {
	if (index == bid.size()) answer.insert(mask);

	for (int i = 0; i < uid.size(); i++) {
		if (check[i]) continue;
		if (uid[i].size() != bid[index].size()) continue;

		int j = 0;
		for (; j < uid[i].size(); j++) {
			if (bid[index][j] == '*') continue;
			if (uid[i][j] == bid[index][j]) continue;
			break;
		}

		if (j == uid[i].size()) {
			check[i] = true;
			dfs(index + 1, mask | ( 1 << i ));
			check[i] = false;
		}
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	uid = user_id;
	bid = banned_id;
	dfs(0, 0);
	return answer.size();;
}
