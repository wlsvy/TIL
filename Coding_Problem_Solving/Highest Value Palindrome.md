Question
===
숫자로 이루어진 문자열과 횟수가 주어질 때, 해당 횟수 안에서 아래 조건에 맞게 문자열의 원소를 변경할 것. 

문자열은 가운데를 중심으로 대칭이 되어야 하며, \
만약 위의 조건을 만족하는 문자열이 다수 있다면 그 중 최댓값을 반환하면 된다.

https://www.hackerrank.com/challenges/richie-rich/problem

## Answer

```
#pragma region PRE DEFINE

using VB = vector<bool>;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using VS = vector<string>;
using UMII = unordered_map<int, int>;
using UMIVI = unordered_map<int, vector<int>>;
using MII = map<int, int>;
using LL = long long;
#define FORI(n) for(int i = 0; i < (n); i++)
#define FORJ(n) for(int j = 0; j < (n); j++)
#define FORK(n) for(int k = 0; k < (n); k++)
#define FORIR(n) for(int i = (n) - 1; i >= 0; i--)
#define FORJR(n) for(int j = (n) - 1; j >= 0; j--)
#define FORKR(n) for(int k = (n) - 1; k >= 0; k--)

#pragma endregion

string highestValuePalindrome(string s, int n, int k) {
    int mid = n / 2;
    int cnt = 0;
    VI vi = vector<int>(n, 0);

    FORI(mid) {
        if (s[i] != s[n - i - 1]) {
            k--;
            if (s[i] == '9' || s[n - i - 1] == '9') {
                s[i] = s[n - i - 1] = '9';
            }
            else {
                s[i] = s[n - i - 1] = max(s[i], s[n - i - 1]);
                cnt++;
                vi[i] = 1;
            }
        }
        else {
            if (s[i] != '9') vi[i] = 2;
        }
    }
    if (k < 0) return "-1";

    FORI(mid) {
        if (k >= vi[i] && vi[i] > 0) {
            k -= vi[i];
            s[i] = s[n - i - 1] = '9';
        }
    }
    if (k > 0 && n % 2 != 0) s[mid] = '9';
    return s;
}
```

medium 난이도 치고도 쉽지 않은 문제. 두 시간 반 걸려서 겨우 풀었다.
