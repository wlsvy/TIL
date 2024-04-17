#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

using ULL = unsigned long long;

const ULL mod = 1000000007;

ULL shortPalindrome(string s) {
	ULL arr[26][26][4] = { 0, };

	for (auto c: s) {
		int i = c - 'a';
		for (int j = 0; j < 26; j++) {
			arr[i][j][3] += arr[i][j][2] % mod;
			arr[j][i][2] += arr[j][i][1] % mod;
			arr[j][i][1] += arr[j][i][0] % mod;
			arr[i][j][0]++;
		}
	}

	ULL sum = 0;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			sum += arr[i][j][3] % mod;
		}
	}
	return sum % mod;
}
