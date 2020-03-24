Problem
===

https://www.hackerrank.com/challenges/maximum-palindromes/problem

특정 문자열에서 대칭을 이루는 가장 긴 문자열 갯수 찾기

modulo 10^9 + 7 로 결과값의 나머지를 구하는 것이 포인트
풀이 방법을 찾는것은 크게 어렵지는 않지만, 풀이식은 생각보다 간단하지만 그 과정에서

수십 수백만 번째 팩토리얼 값을 '나누기 연산' 할 때가 문제다.    
  #
  
  
이 부분은 실제로 값을 나누는 것이 아닌, 나머지값을 활용하는 것이 중요.

초기화할때 InverseFactorial 을 구하는 과정을 중점적으로 보도록 하자.

Answer
===

```
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD=1e9+7;
const int MAXSIZE=1e5+2;

string str;
int allAlphabet[26][MAXSIZE];

ll factorial[MAXSIZE];
ll InverseFactorial[MAXSIZE];

ll power(ll x, ll y){
    ll res = 1;
    while(y){
        if(y & 1){
            res = (res * x) % MOD;
            y--; 
        }
        else {
            x = (x * x) % MOD;
            y /= 2;
        }
    }
    return res;
}

int main(){
    cin >> str;

    for(int i = 0; i < str.size(); i++){
        allAlphabet[str[i] - 'a'][i]++;
    }
    for(int i = 0; i < 26; i++){
        for(int j = 1; j< str.size(); j++){
            allAlphabet[i][j] += allAlphabet[i][j - 1];
        }
    }
    
    factorial[0] = 1;
    InverseFactorial[0] = 1;
    for(ll i = 1; i < MAXSIZE; i++){
        factorial[i] = (i * factorial[i - 1]) % MOD;
        InverseFactorial[i] = power(factorial[i], MOD - 2);
    }

    int query; 
    cin >> query;

    while(query--){
        int l, r;
        cin >> l >> r;
        l--, r--;

        int alphabet[26] = {0, };
        for(int i = 0; i < 26; i++){
            alphabet[i] = allAlphabet[i][r] - (l ? allAlphabet[i][l - 1] : 0);
        }

        int odd = 0, even = 0;
        for(int i = 0; i < 26; i++){
            even += alphabet[i] / 2;
            odd += alphabet[i] & 1;
            alphabet[i] /= 2;
        }

        ll ans = (factorial[even] * (ll)max(1, odd)) % MOD;
        for(int i = 0; i < 26; i ++){
            ans = (ans * InverseFactorial[alphabet[i]]) % MOD;
        }

        cout << ans << endl;
    }
}
```

Reference
---

참조(Fermat's Theorem and Inverse factorials) : https://blogarithms.github.io/articles/2019-01/fermats-theorem
