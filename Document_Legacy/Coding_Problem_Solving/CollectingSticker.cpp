#include <bits/stdc++.h>
using namespace std;

/*
    아래 두개의 배열은, 첫번째 스티커를 뗐느냐, 떼지 않았느냐에 따라 경우를 분리한 것입니다.
    
    첫 번째 스티커를 뗀 경우 -> dp0 : dp0[0] = dp0[1] = sticker[0], (어차피 두 번째 스티커는 뗄 수 없습니다.)
    두 번째 스티커를 뗀 경우 -> dp1 : dp0[0] = 0, dp[1] = sticker[1]
    
    이후 두 개의 배열을 대상으로 연산을 진행한 뒤, 두 개의 배열 중에서 가장 큰 값을 반환하면 됩니다.
    -> 첫 번째 스티커를 뗀 경우, 마지막 스티커를 뗄 수 없으니, 이 부분은 주의하셔야 합니다.
*/

int dp0[100002];
int dp1[100002];

int solution(vector<int> sticker)
{
	int n = sticker.size();
	if (n == 1) return sticker[0];
	if (n == 2) return max(sticker[0], sticker[1]);

	dp0[0] = sticker[0];
	dp0[1] = sticker[0];
	dp1[0] = 0;
	dp1[1] = sticker[1];

	for (int i = 2; i < n - 1; i++) {
		dp0[i] = max(dp0[i - 1], dp0[i - 2] + sticker[i]);
	}
	for (int i = 2; i < n; i++) {
		dp1[i] = max(dp1[i - 1], dp1[i - 2] + sticker[i]);
	}

    return max(dp0[n -2], dp1[n-1]);
}
