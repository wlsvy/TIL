#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;

int solution(vector<vector<int>> board)
{
    if (board.size() == 1 || board.front().size() == 1) return 1;
    
	int answer = 0;
	for (uint i = 0; i < board.size(); i++) {
		for (uint j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) continue;
			if (i - 1 >= board.size() || j - 1 >= board[i].size()) continue;
			board[i][j] += min(board[i - 1][j - 1], min(board[i - 1][j], board[i][j - 1]));
			answer = max(answer, board[i][j] * board[i][j]);
		}
	}

    return answer;
}
