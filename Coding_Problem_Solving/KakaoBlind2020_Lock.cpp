/*
실수
1. key와 lock 이 유효한지 판정하는 코드를 작성할 때 비효율적을 작성. 
(lock 배열 값복사를 하면 간단한데, 그러지 않고, if 문 여러개로 분기를 나눠서 시간을 지체)
2. 맨 처음 matrix rotate 함수를 구현할 때, 완전히 잘못 구현. 90도 회전이 아니라, 한칸씩 시계방향으로 움직이도록 구현해서 시간 지체
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>
#include <queue>

using namespace std;

using VVI = std::vector<std::vector<int>>;

VVI Lock;
int keySize, lockSize;

bool isMatrixValid(VVI& key, int by, int bx) {

	auto lockM = Lock;
	for (int i = 0; i < keySize; i++) {
		for (int j = 0; j < keySize; j++) {
			int cy = i + by;
			int cx = j + bx;
			if (cy < 0 || cy >= lockSize || cx < 0 || cx >= lockSize) continue;;
			lockM[cy][cx] += key[i][j];
		}
	}


	for (int i = 0; i < lockSize; i++) {
		for (int j = 0; j < lockSize; j++) {
			if (lockM[i][j] != 1) return false;
		}
	}

	return true;
}


void rotateKey(VVI &key) {

	VVI tmp(keySize, vector<int>(keySize));

	for (int j = keySize - 1; j >= 0; j--) {
		for (int i = 0; i < keySize; i++) {
			tmp[i][j] = key[keySize - j - 1][i];
		}
	}

	key = tmp;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	Lock = lock;
	keySize = key.size();
	lockSize = lock.size();

	for (int r = 0; r < 4; r++) {
		for (int i = -keySize; i <= keySize + lockSize; i++) {
			for (int j = -keySize; j <= keySize + lockSize; j++) {
				if (isMatrixValid(key, i, j)) return true;
			}
		}
		rotateKey(key);
	}

	return false;
}
