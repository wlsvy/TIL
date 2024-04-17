#include <bits/stdc++.h>
using namespace std;

constexpr int MaxSize = 1000003;
bool isPrime[MaxSize];

void searchPrime() {
	fill(isPrime + 2, isPrime + MaxSize, true); //0과 1은 소수 X
	for (int n = 2; n < MaxSize; n++) {
		if (isPrime[n]) {
			for (int i = n * 2; i < MaxSize; i += n) isPrime[i] = false;
		}
	}
}
int solution(int n) {
	searchPrime();
	return count_if(isPrime, isPrime + n + 1, [](bool b) {return b; });
}
