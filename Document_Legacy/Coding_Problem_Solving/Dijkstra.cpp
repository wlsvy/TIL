#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

using PI = pair<int, int>;

struct Edge {
	int to;
	int weight;
};
struct Node {
	vector<Edge> edges;
};

int T, N, E, Start;

priority_queue<PI, vector<PI>, greater<PI>> pq;
bool visit[3001] = { false, };
int dist[3001];

void Dijkstra() {
	cin >> N >> E;
	vector<Node> nodes(N);
	fill(visit, visit + N, false);
	fill(dist, dist + N, INT_MAX);

	for (int i = 0; i < E; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		from--;
		to--;

		nodes[from].edges.push_back({ to, weight });
		nodes[to].edges.push_back({ from, weight });
	}
	cin >> Start;
	Start--;

	dist[Start] = 0;
	pq.push({ 0, Start });

	while (!pq.empty()) {
		auto current = pq.top().second; pq.pop();

		if (visit[current]) continue;
		visit[current] = true;

		for (auto& e : nodes[current].edges) {
			if (dist[e.to] > dist[current] + e.weight) {
				dist[e.to] = dist[current] + e.weight;
				pq.push({ dist[e.to], e.to });
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (i == Start) continue;

		cout << (dist[i] != INT_MAX ? dist[i] : -1);
		if (i != N - 1) cout << " ";
	}
}

int main()
{
	cin >> T;
	while (T--) {
		Dijkstra();
		cout << endl;
	}
	return 0;
}
