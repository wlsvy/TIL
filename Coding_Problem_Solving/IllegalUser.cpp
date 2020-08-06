#include <bits/stdc++.h>
using namespace std;

vector<string> uid, bid;
set<int> answer;
bool check[10];

void dfs(int bnum, int mask) {
	if (bnum == bid.size()) answer.insert(mask);

	for (int unum = 0; unum < uid.size(); unum++) {
		if (check[unum]) continue;
		if (uid[unum].size() != bid[bnum].size()) continue;

		int i = 0;
		for (; i < uid[unum].size(); i++) {
			if (bid[bnum][i] == '*') continue;
			if (uid[unum][i] == bid[bnum][i]) continue;
			break;
		}

		if (i == uid[unum].size()) {
			check[unum] = true;
			dfs(bnum + 1, mask | (1 << unum));
			check[unum] = false;
		}
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	uid = user_id;
	bid = banned_id;
	dfs(0, 0);
	return answer.size();;
}
