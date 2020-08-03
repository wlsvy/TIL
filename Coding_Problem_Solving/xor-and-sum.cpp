#include <bits/stdc++.h>

using namespace std;
using ULL = unsigned long long;

constexpr ULL mod = 1000000007;
constexpr int T = 314159;
constexpr int M = T + 100001;

ULL A[M], accumB[M];
ULL p[M] = { 1, };

ULL sum(int index) {
    if (index < T + 1) return accumB[index];
    else return accumB[index] - accumB[index - T - 1];
}

void solve() {
    ULL ans = 0;
    for (int i = 0; i < M; ++i)
    {
        if (A[i] == 0)
            ans = (ans + p[i] * sum(i)) % mod;
        else    // T + 1 - sum(i) 의 의미를 모르겠습니다. bit flip 이라면 다른 방식이 있었을 텐데요.
            ans = (ans + p[i] * (T + 1 - sum(i))) % mod;
    }
    cout << ans << "\n";
}

int main() {

    string a, b;
    cin >> a >> b;

    for (int i = 0; i < a.size(); ++i)
        A[a.size() - 1 - i] = a[i] - '0';

    for (int i = 0; i < b.size(); ++i)
        accumB[b.size() - 1 - i] = b[i] - '0';
    for (int i = 1; i < M; ++i)
        accumB[i] += accumB[i - 1];

    generate(p + 1, p + M, [count = 0]()mutable{ return (p[count++] * 2) % mod; });
    solve();

    return 0;
}
