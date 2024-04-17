/*
============
  가로세로 동일한 크기의 매트릭스 90도 회전
============
*/
void RotateMatrix(std::vector<vector<int>> &matrix) {
	auto size = matrix.size();
	VVI tmp(size, vector<int>(size));

	for (int j = size - 1; j >= 0; j--) {
		for (int i = 0; i < size; i++) {
			tmp[i][j] = matrix[size - j - 1][i];
		}
	}

	matrix = tmp;
}


/*
============
  시계/반시계 방향으로 원소들을 한칸씩 회전시키는 방법
============
*/
/*
============
  첫번째 방법
  - vector에 테두리 원소들을 삽입하고 나머지 연산을 통해 R번째 회전시킨 자리의 원소를 찾는 방식
============
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n, w;
vector<vector<string>> input;
vector<vector<string>> output;


void RotateLayer(int by, int bx, int row, int col) {
	int y = 0;
	int x = 0;
	int layerSize = (row + col - 2) * 2;
	vector<int> layer;

	for (int i = 0; i < col - 1; i++) {
		layer.push_back(y * col + x);
		x++;
	}
	for (int i = 0; i < row - 1; i++) {
		layer.push_back(y * col + x);
		y++;
	}
	for (int i = 0; i < col - 1; i++) {
		layer.push_back(y * col + x);
		x--;
	}
	for (int i = 0; i < row - 1; i++) {
		layer.push_back(y * col + x);
		y--;
	}
	int r = w % layerSize;
	r = r > 0 ? r : layerSize + r;

	for (int i = 0; i < layerSize; i++) {
		y = layer[i] / col;
		x = layer[i] % col;
		int ny = layer[(i + r) % layerSize] / col;
		int nx = layer[(i + r) % layerSize] % col;
		output[by + ny][bx + nx] = input[by + y][bx + x];
	}
}


int main() {
	cin >> n >> w;

	input = vector<vector<string>>(n, vector<string>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> input[i][j];
		}
	}
	output = input;

	for (int i = 0; i < n / 2; i++) {
		int depth = i;
		int row = n - 2 * depth;
		int col = row;
		RotateLayer(depth, depth, row, col);
		w *= -1;
	}

	for (auto vs : output) {
		for (int i = 0; i < vs.size(); i++) {
			cout << vs[i];
			if (i != vs.size() - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}

	return 0;
}

/*
============
  두번째 방법 
  - std::rotate 활용.
  (첫번째와 main함수는 동일하므로 RotateLayer 함수만 작성)
============
*/

void RotateLayer(int by, int bx, int row, int col) {
	int y = 0;
	int x = 0;
	int layerSize = (row + col - 2) * 2;
	vector<int> layer;

	for (int i = 0; i < col - 1; i++) {
		layer.push_back(y * col + x);
		x++;
	}
	for (int i = 0; i < row - 1; i++) {
		layer.push_back(y * col + x);
		y++;
	}
	for (int i = 0; i < col - 1; i++) {
		layer.push_back(y * col + x);
		x--;
	}
	for (int i = 0; i < row - 1; i++) {
		layer.push_back(y * col + x);
		y--;
	}
	int r = w % layerSize;
	r = r > 0 ? r : layerSize + r;

	auto target = layer;
	rotate(target.begin(), target.begin() + r, target.end());

	for (int i = 0; i < layerSize; i++) {
		y = layer[i] / col;
		x = layer[i] % col;
		int ny = target[i] / col;
		int nx = target[i] % col;
		output[by + ny][bx + nx] = input[by + y][bx + x];
	}
}


/*
============
  세번째 방법
  - Brute Force
  - 원소들을 전부 한칸씩 이동시킨다.
============
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n, w;
vector<vector<string>> input;
vector<vector<string>> output;

void movePosition(int& by, int& bx, int depth, int rotate) {
	int y = by - depth;
	int x = bx - depth;
	int layerSize = (n - depth * 2 - 1) * 4;
	int colMinusOne = n - 2 * depth - 1;
	int rowMinusOne = colMinusOne;
	int r = rotate % layerSize;
	r = r > 0 ? r : layerSize + r;

	while (r--) {
		if (y == 0 && x != colMinusOne) x++;
		else if (y != rowMinusOne && x == colMinusOne) y++;
		else if (y == rowMinusOne && x != 0) x--;
		else if (y != 0 && x == 0) y--;
	}

	by = y + depth;
	bx = x + depth;
}

void rotateRayer(int depth) {
	int y = depth;
	int x = depth;
	
	int layerSize = (n - depth * 2 - 1) * 4;
	for (int i = 0; i < layerSize; i++) {
		int ny = y;
		int nx = x;

		movePosition(ny, nx, depth, w);
		output[ny][nx] = input[y][x];

		movePosition(y, x, depth, 1);
	}
}

int main() {
	cin >> n >> w;

	input = vector<vector<string>>(n, vector<string>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> input[i][j];
		}
	}
	output = input;

	for (int i = 0; i < n / 2; i++) {
		rotateRayer(i);
		w *= -1;
	}

	for (auto vs : output) {
		for (int i = 0; i < vs.size(); i++) {
			cout << vs[i];
			if (i != vs.size() - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}

	return 0;
}
