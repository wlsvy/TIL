/*
데이터를 '기록'해야할 일이 있으면 무조건 '배열'을 먼저 생각합시다. map/unordered_map, 심지어 vector보다도 배열이 문제풀이에 적합한 경우가 빈번합니다. 이번 문제를 포함해서요.

map/unordered_map과 같은 연관 컨테이너의 경우, 반복자를 다루는 과정탓에 코드가 많아지고, 혹여나 이 부분에서 실수가 발생하면 찾기 어렵습니다.

아래의 경우, 처음에는 map을 활용했다가 크게 애를 먹었고, 두 번째로 배열을 활용해 훨씬 가독성 좋은 코드를 작성한 문제입니다.
*/

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
