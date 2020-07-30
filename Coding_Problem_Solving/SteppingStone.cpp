//첫번째 방법 : Map 활용

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

//두번째 방법 : 이분 탐색 

#include <string>
#include <vector>
using namespace std;
bool isPossible(int n, const vector<int>& stones, int k) {
    int currLength = 0;
    for (int i = 0; i < stones.size(); i++) {
        if (stones[i] - n <= 0)
            currLength++;
        else
            currLength = 0;
        if (currLength >= k)
            return false;
    }
    return true;
}
int solution(vector<int> stones, int k) {
    int lo = 1;
    int hi = 200000000;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (isPossible(mid, stones, k))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return lo;
}


//세번째 방법 : multiset

#include <bits/stdc++.h>
using namespace std;
multiset <int> s;

int solution(vector<int> a,int k) {
    int ans = 1e9;
    for(int i = 0;i < k-1;i++) {
       s.insert(a[i]);
    }
    for(int i = k-1;i < a.size();i++) {
       s.insert(a[i]);
       auto it = s.end(); --it;
       ans = min(ans,*it);
       s.erase(s.find(a[i-(k-1)]));
    }
    return ans;
}
