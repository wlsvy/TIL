#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

class UnionFind {
public:
	static void Init(std::size_t n) {
		Get().m_Elements = std::vector<int>(n, -1);
	}
	static void Union(int x, int y) {
		auto& elements = Get().m_Elements;
		x = Find(x);
		y = Find(y);

		if (x != y) {
			if (elements[x] < elements[y]) {
				elements[x] += elements[y];
				elements[y] = x;
			}
			else {
				elements[y] += elements[x];
				elements[x] = y;
			}
		}
	}
	static int Find(int target) {
		auto& elements = Get().m_Elements;
		int root = target;

		while (elements[root] >= 0) {
			root = elements[root];
		}

		while (elements[target] >= 0) {
			int tmp = elements[target];
			elements[target] = root;
			target = tmp;
		}

		return root;
	}

private:
	static UnionFind& Get() {
		static UnionFind s_Instance;
		return s_Instance;
	}
	std::vector<int> m_Elements;
};

using ULL = unsigned long long;

struct Edge {
	int from;
	int to;
	int weight;
};
struct Comp {
	bool operator() (Edge& e0, Edge& e1){
		return e0.weight < e1.weight;
	}
};

ULL N, E;

Edge edges[10012];

int main() {
	cin >> N >> E;
	for (int i = 0; i < E; i++) {
		auto& e = edges[i];
		cin >> e.from >> e.to >> e.weight;
	}

	sort(edges, edges + E, Comp());

	ULL weights = 0;
	UnionFind::Init(N);
	for (auto& e : edges) {
		int root0 = UnionFind::Find(e.from);
		int root1 = UnionFind::Find(e.to);
		if (root0 == root1) continue;

		UnionFind::Union(e.from, e.to);
		weights += e.weight;
	}
	cout << weights;

	return 0;
}

