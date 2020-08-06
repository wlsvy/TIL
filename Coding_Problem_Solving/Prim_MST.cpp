#include <bits/stdc++.h>
using namespace std;

using ULL = unsigned long long;

struct Edge{
	int weight;
	int to;
};
struct Node {
	int index;
	vector<Edge> edges;
};

Node nodes[3001];
bool visit[3001] = { false, };
struct Comp {
	bool operator()(Edge& e0, Edge& e1)
	{
		return e0.weight > e1.weight;
	}
};

ULL prims(int n, vector<vector<int>> edges, int start) {
	
	ULL weights = 0;

	for (auto val : edges) {
		Edge e;
		e.weight = val[2];

		e.to = val[0];
		nodes[val[1]].edges.push_back(e);
		e.to = val[1];
		nodes[val[0]].edges.push_back(e);
	}

	priority_queue<Edge, vector<Edge>, Comp> pq;

	visit[start] = true;
	for (auto& e : nodes[start].edges) {
		pq.push(e);
	}

	while (!pq.empty()) {
		auto edge = pq.top(); pq.pop();

		if (visit[edge.to]) continue;
		visit[edge.to] = true;
		weights += edge.weight;

		auto& node = nodes[edge.to];
		for (auto e : node.edges) {
			pq.push(e);
		}
	}
	
	return weights;
}
