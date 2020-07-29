
/*
    로봇의 '특정 지점을 방문할 때까지 걸린시간?'을 체크할때 고생한 케이스.
    
    회전 상태에 따라 다르게 확인해 줘야 할 필요가 있었는데 
    처음에 회전 상태를 고려하지 않고 코드를 작성한 것이 2시간!! 씩이나 시간을 낭비하게 했다.
    
    (로직이 복잡한 케이스라 오류가 생기면 원인을 찾는데도 시간이 꽤나 걸리니....)
    
    결론은 역시 배열. 
    int Dist[2][200][200]; (회전 상태 - 2, 최대 x 범위 - 200, 최대 y 범위 - 200)
    회전상태에 따라서 구분함으로써 보다 가독성 있는 코드를 작성했다.
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <stack>
using namespace std;

struct Move {
	int x;
	int y;
	int isHorizon = true;
	int time;
	Move(int x, int y, bool h, int t) : x(x), y(y), isHorizon(h), time(t) {}
};


int N;
int Dist[2][200][200];
vector<vector<int>> Board;
int answer = INT_MAX;

int moveDir[4][2] =
{
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};
//2 -> 회전 상태 2가지 경우, 
//4 -> 회전 방향 네 가지, 
//6 -> 회전 하기 전 검사할 좌표 (x1, y1, x2, y2) 그리고 회전 후 새로운 위치 (new x, new y)
int rotateDir[2][4][6] =
{
	{
		{1, 0, 1, 1, 0, 1},
		{1, 0, 1, 1, 0, 0},
		{-1, 0, -1, 1, -1, 1},
		{-1, 0, -1, 1, -1, 0}
	},
	{
		{0, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 0, 0},
		{0, -1, 1, -1, 1, -1},
		{0, -1, 1, -1, 0, -1}
	}
};

bool isValid(int x, int y) {
	return
		0 <= x && x < N &&
		0 <= y && y < N &&
		Board[y][x] == 0;
}

bool isValidPosition(int x, int y, bool isHorizon) {
	if (!isValid(x, y)) return false;
	if (isHorizon && !isValid(x + 1, y)) return false;
	if (!isHorizon && !isValid(x, y + 1)) return false;
	return true;
}

void bfs() {
	stack<Move> s;
	s.emplace(0, 0, true, 0);

	while (!s.empty()) {
		auto m = s.top(); s.pop();

		if ((m.x == N - 1 && m.y == N - 1) ||
			(m.isHorizon && m.x + 1 == N - 1 && m.y == N - 1) ||
			(!m.isHorizon && m.x == N - 1 && m.y + 1 == N - 1))
		{
			answer = min(answer, m.time);
			continue;
		}

		for (auto md : moveDir) {
			int nx = m.x + md[0];
			int ny = m.y + md[1];
			int nt = m.time + 1;

			if (!isValidPosition(nx, ny, m.isHorizon)) continue;
			if (Dist[m.isHorizon][nx][ny] <= nt) continue;

			Dist[m.isHorizon][nx][ny] = nt;
			s.emplace(nx, ny, m.isHorizon, nt);

		}
		for (auto rd : rotateDir[m.isHorizon])
		{
			if (!isValid(m.x + rd[0], m.y + rd[1])) continue;
			if (!isValid(m.x + rd[2], m.y + rd[3])) continue;

			int nx = m.x + rd[4];
			int ny = m.y + rd[5];
			auto isHorizon = !m.isHorizon;
			int nt = m.time + 1;

			if (!isValidPosition(nx, ny, isHorizon)) continue;
			if (Dist[isHorizon][nx][ny] <= nt) continue;

			Dist[isHorizon][nx][ny] = nt;
			s.emplace(nx, ny, isHorizon, nt);
		}
	}
}

int solution(vector<vector<int>> board) {
	Board = board;
	N = board.size();
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++)
		{
			Dist[true][i][j] = INT_MAX;
			Dist[false][i][j] = INT_MAX;
		}
	}
	Dist[true][0][0] = true;

	bfs();
	return answer;
}
