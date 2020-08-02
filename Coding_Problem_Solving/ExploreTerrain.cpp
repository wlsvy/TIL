/*
  시간초과만 아니었어도 더 빨리 풀 수 있었던 문제.
  
  시간초과가 발생한 이유는
  set<int> s; 
  이 변수를 활용 할 때 처음에는
  set<array<int, 3>>  s;
  형식으로 활용했다.
  
  즉, 배열값을 생으로 그대로 입력해서 값 비교를 수행한 것. 원소는 3개 뿐이지만 이 부분이 생각보다 오버헤드가 엄청났다....
  
  입력값 타입을 배열에서 int로 변경하고
  
  s.insert({diff, ny, yx});
  값을 입력할때도 세 개의 변수를 하나의 int 값으로 패킹해 줌으로써
  
  s.insert(diff * 90000 + (int)ny * 300 + (int)nx);
  
  시간초과 문제를 해결했다.
*/


#include <bits/stdc++.h>
using namespace std;
using UShort = unsigned short;
char dir[4][2] =
{
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};

vector<vector<int>> board;
int H;
int N;
bool visit[302][302];
set<int> s;
int answer = 0;

void bfs(UShort sy, UShort sx) {
	queue<array<UShort, 2>> q;
	q.push({ sy, sx });

	while (!q.empty()) {
		auto f = q.front(); q.pop();
		if (visit[f[0]][f[1]]) continue;
		visit[f[0]][f[1]] = true;

		for (auto d : dir) {
			UShort ny = f[0] + d[0];
			UShort nx = f[1] + d[1];

			if (ny >= N || nx >= N) continue;

			int diff = abs(board[ny][nx] - board[f[0]][f[1]]);
			if (diff > H) {
				s.insert(diff * 90000 + (int)ny * 300 + (int)nx);
				continue;
			}
			q.push({ ny, nx });
		}
	}
}

int solution(vector<vector<int>> land, int height) {
	N = land.size();
	H = height;
	board = land;

	bfs(0, 0);
	while (!s.empty()) {
		int diff, y, x;
        
		while (!s.empty()) {
			auto i = s.begin();
			diff = *i / 90000;
			y = (*i % 90000) / 300;
			x = *i % 300;
			if (visit[y][x])
				s.erase(s.begin());
			else break;
		}
		if (s.empty()) break;
        
		answer += diff;
		bfs(y, x);
	}

	return answer;
}
