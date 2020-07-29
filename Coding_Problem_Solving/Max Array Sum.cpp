#include <bits/stdc++.h>

using namespace std;

int dp[100005];

int maxSubsetSum(vector<int> arr) {

    dp[0] = max(0, arr[0]);
    if (arr.size() == 1) return dp[0];

    dp[1] = max(dp[0], arr[1]);
    if (arr.size() == 2) return dp[1];
    
    for (int i = 2; i < arr.size(); i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + arr[i]);
    }

    return max(dp[arr.size() - 1], dp[arr.size() - 2]);
}
