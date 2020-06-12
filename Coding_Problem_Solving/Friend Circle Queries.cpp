#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

class UnionFind {
public:
	static void Init(std::size_t n) {
		Get().m_Elements = std::vector<int>(n, -1);
		atexit([]() {
			delete &Get();
		});
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
		static UnionFind* s_Instance = new UnionFind();
		return *s_Instance;
	}
	std::vector<int> m_Elements;
};


vector<int> maxCircle(vector<vector<int>> queries) {

	unordered_map<int, int> um;
	unordered_map<int, int> umkey;
	set<int> si;
	for (auto q : queries) {
		si.insert(q[0]);
		si.insert(q[1]);
	}

	int cnt = 0;
	for (auto it : si) {
		umkey.insert(make_pair(it, cnt++));
	}

	for (auto q : queries) {
		um[umkey[q[0]]] = 1;
		um[umkey[q[1]]] = 1;
	}

	vector<int> uf = vector<int>(um.size(), -1);
	vector<int> ans;
	int max = 1;

	UnionFind::Init(um.size());
	for (auto q : queries) {
		int p0 = umkey[q[0]];
		int p1 = umkey[q[1]];
		int r0 = UnionFind::Find(p0);
		int r1 = UnionFind::Find(p1);
		if (r0 == r1) {
			ans.push_back(max);
			continue;
		}
		int size = um[r0] + um[r1];
		UnionFind::Union(p0, p1);
		um[UnionFind::Find(p0)] = size;

		if (max < size) {
			max = size;
		}

		ans.push_back(max);
	}

	return ans;
}
