#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;


int n;
int sy, sx;
int ey, ex;

queue<int> q;

bool visit[201][201] = { false, };
int dist[201][201] = { 99999, };
vector<char> moveDir[201][201];
int dir[6][2]{
	{-2, -1},
	{-2, 1},
	{0, 2},
	{2, 1},
	{2, -1},
	{0, -2}
};
//UL, UR, R, LR, LL, L

int main()
{
	cin >> n >> sy >> sx >> ey >> ex;
	
	q.push(sy * n + sx);
	dist[sy][sx] = 0;
	visit[sy][sx] = true;

	while (!q.empty()) {
		auto front = q.front(); q.pop();
		int y = front / n;
		int x = front % n;

		for (int i = 0; i < 6; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (visit[ny][nx]) continue;

			visit[ny][nx] = true;
			q.push(ny * n + nx);

			if (dist[ny][nx] > dist[ny][nx], dist[y][x] + 1) {
				dist[ny][nx] = dist[y][x] + 1;
				moveDir[ny][nx] = moveDir[y][x];
				moveDir[ny][nx].push_back(i);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}

	if (visit[ey][ex]) {
		cout << dist[ey][ex] << endl;
		for (int i = 0; i < moveDir[ey][ex].size(); i++) {
			switch (moveDir[ey][ex][i]) {
			case 0: cout << "UL"; break;
			case 1: cout << "UR"; break;
			case 2: cout << "R"; break;
			case 3: cout << "LR"; break;
			case 4: cout << "LL"; break;
			case 5: cout << "L"; break;
			}
			if (i != moveDir[ey][ex].size() - 1) {
				cout << " ";
			}
		}
	}
	else {
		cout << "Impossible";
	}

	return 0;
}
