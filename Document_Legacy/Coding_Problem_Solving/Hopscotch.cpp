#include <bits/stdc++.h>
using namespace std;

int row;
int Max(vector<int>& v, int except)
{
	int m = -1;
	for (int i = 0; i < 4; i++) {
		if (i == except) continue;
		m = max(v[i], m);
	}
	return m;
}

int solution(vector<vector<int> > land)
{
	row = land.size();
	for (int i = 1; i < row; i++) {
		land[i][0] += Max(land[i - 1], 0);
		land[i][1] += Max(land[i - 1], 1);
		land[i][2] += Max(land[i - 1], 2);
		land[i][3] += Max(land[i - 1], 3);
	}

    return *max_element(land[row - 1].begin(), land[row - 1].end());
}
