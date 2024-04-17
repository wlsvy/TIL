/*
==============
첫번째 방식 : 배열 응용
==============
*/

int pylons(int k, vector<int> arr) {
    auto prev = vector<int>(arr.size(), -1);

    int last = -1;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1) last = i;
        prev[i] = last;
    }

    int ans = 0;
    for (int i = 0; i < arr.size();) {
        int take = prev[min(i + k - 1, (int)arr.size() - 1)];
        if (take == -1 || take + k <= i) return -1;
        i = take + k; 
        ans++;
    }

    return ans;
}

/*
==============
두번째 방식 : set 활용
==============
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
int c[100055];

int main() {
	scanf("%d %d", &n, &k);

	set<int> unpowered, station;

	for (int i = 0; i < n; i++) {
		scanf("%d", &c[i]);
		if (c[i]) station.insert(i);
		unpowered.insert(i);
	}

	int res = 0;

	for (auto u : station) {
		if (!unpowered.empty() && *unpowered.begin() <= u - k) {
			puts("-1");
			return 0;
		}

		auto ite = ++station.find(u);

		if (ite != station.end()) {
			if (!unpowered.empty() && *unpowered.begin() > *ite - k) {
				continue;
			}
		}

		res++;

		vector<int> vec;

		for (auto v : unpowered) {
			if (abs(v - u) >= k) break;
			vec.push_back(v);
		}

		for (auto v : vec) unpowered.erase(v);
	}

	printf("%d\n", res);

	return 0;
}

/*
==============
세번째 방식 : lower_bound 활용
==============
*/

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N,K;
	cin>>N>>K;
	vector<int> a(N);
	for(int i = 0;i < N;i++)
		cin>>a[i];
	vector<int> in;
	for(int i = 0;i < N;i++)
		if(a[i] == 1)
			in.push_back(i);
	bool can = true;
	long long cur = INT_MIN,out = 0;
	for(int i = 0;i < N;i++){
		if(abs(cur - i) >= K){
			int t = lower_bound(in.begin(),in.end(),i + K) - in.begin();
			t--;
			if(t < 0 || abs(in[t] - i) >= K){
				can = false;
				break;
			}
			cur = in[t];
			out++;
		}
	}
	cout<<(can?out:-1)<<'\n';
	return 0;
}
