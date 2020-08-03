/*
  접근법에 대한 이해가 없으면 코드가 굉장히 어려우니 https://www.hackerrank.com/challenges/lego-blocks/problem 를 참조할 것.
*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr LL MOD = 1000000007;

LL power(LL num, int p) {

    if (p == 0) return 1;
    if (p == 1) return num;

    LL number = num;
    for (int i = 2; i <= p; i++) {
        num *= number;
        num %= MOD;
    }
    return num;
}

int main() {

    int N, M;

    vector<LL> T(1001);
    vector<LL> H(1001);
    vector<LL> G(1001);

    T[0] = T[1] = 1;
    T[2] = 2;
    T[3] = 4;
    T[4] = 8;

    G[0] = G[1] = 1;

    for (int i = 5; i <= 1000; i++)
        T[i] = (T[i - 1] + T[i - 2] + T[i - 3] + T[i - 4]) % MOD;

    H[0] = 1;
    H[1] = 1;

    LL sum;
    int Tt;
    cin >> Tt;

    for (int t = 0; t < Tt; t++) {
        cin >> N >> M;

        for (int i = 0; i <= M; i++)
            G[i] = power(T[i], N);

        for (int i = 2; i <= M; i++) {
            sum = 0;
            for (int j = 1; j < i; j++) {
                sum = (sum + H[j] * G[i - j]) % MOD;
            }
            H[i] = (G[i] - sum + MOD) % MOD;    //빼기 연산을 수행할 때는 음수의 경우를 고려해 MOD 활용에 주의할 것. S[i] = (G[i] - sum) % MOD; (잘못된 예)
        }
        cout << H[M] << endl;
    }
}
