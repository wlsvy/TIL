#include <bits/stdc++.h>
using namespace std;

map<int, vector<int>> tree;
int blocked[200001];
bool visit[200001];
int hang[200001];

void dfs(int v) {
	if (visit[v])return;

	if (!visit[blocked[v]]) {
		hang[blocked[v]] = v;
		return;
	}

	visit[v] = true;
	dfs(hang[v]);		
	for (int u : tree[v])dfs(u);
}


void bfs() {
	if (blocked[0]) return;

	queue<int> q;
	q.push(0);
	visit[0] = true;

	while (!q.empty()) {
		auto f = q.front(); q.pop();
		for (auto i : tree[f])
		{
			if (visit[i]) continue;
			visit[i] = true;

			if (!visit[blocked[i]]) {
				hang[blocked[i]] = i;
				continue;
			}
			q.push(i);
			q.push(hang[i]);
		}
	}
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
	for (auto& p : path)
	{
		tree[p[0]].push_back(p[1]);
		tree[p[1]].push_back(p[0]);
	}
	for (auto& o : order) {
		blocked[o[1]] = o[0];
	}

	/*
		//dfs
		visit[0] = true;
		if (blocked[0])return false;
		for (int u : tree[0]) dfs(u);
	*/
	
	//bfs
	bfs();

	return all_of(visit, visit + n, [](bool b) {return b; });
}
