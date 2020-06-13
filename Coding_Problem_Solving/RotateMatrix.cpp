/*
============
  첫번째 방법
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

	for (int i = 0; i < row - 1; i++) {
		layer.push_back(y * col + x);
		x++;
	}
	for (int i = 0; i < col - 1; i++) {
		layer.push_back(y * col + x);
		y++;
	}
	for (int i = 0; i < row - 1; i++) {
		layer.push_back(y * col + x);
		x--;
	}
	for (int i = 0; i < col - 1; i++) {
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
