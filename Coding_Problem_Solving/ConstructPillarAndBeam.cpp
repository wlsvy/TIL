#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;
enum Type {
	Pillar = 0,
	Beam = 1
};

bool Structure[2][101][101];
int N;

bool IsValid() {
	for (int x = 0; x <= N; x++) {
		for (int y = 0; y <= N; y++) {

			if (Structure[Pillar][x][y]) {
				if (y == 0);
				else if (Structure[Pillar][x][y - 1]);
				else if (Structure[Beam][x - 1][y]);
				else if (Structure[Beam][x][y]);
				else return false;
			}
			if (Structure[Beam][x][y]) {
				if (Structure[Pillar][x][y - 1]);
				else if (Structure[Pillar][x + 1][y - 1]);
				else if (Structure[Beam][x - 1][y] &&
					Structure[Beam][x + 1][y]);
				else return false;
			}
		}
	}

	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	N = n;

	for (auto& f : build_frame) {
		int x = f[0];
		int y = f[1];
		int type = f[2];
		bool isConstruct = f[3];

		Structure[type][x][y] = isConstruct;
		if (!IsValid()) {
			Structure[type][x][y] = !isConstruct;
		}
	}

	vector<vector<int>> answer;
	for (int x = 0; x <= N; x++) {
		for (int y = 0; y <= N; y++) {
			if (Structure[Pillar][x][y]) answer.push_back({ x, y, Pillar });
			if (Structure[Beam][x][y]) answer.push_back({ x, y, Beam });
		}
	}
	return answer;
}
