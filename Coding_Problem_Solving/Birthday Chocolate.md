
Problem
===

간단히 풀 수 있는 문제, 배열 안에서 조건을 만족하는 부분 배열 갯수 출력

https://www.hackerrank.com/challenges/the-birthday-bar/problem

Submission
===

```
#define FORI(n) for(int i = 0; i < (n); i++)
int birthday(vector<int> s, int d, int m) {
	if (s.size() < m) return 0;

	int ans = 0;
	int sum = 0;
	FORI(m) {
		sum += s[i];
	}
	if (sum == d) ans++;

	for (int i = m; i < s.size(); i++) {
		sum -= s[i - m];
		sum += s[i];
		if (sum == d) ans++;
	}

	return ans;
}
```

다른 사람들은 사용한 

```
int birthday(vector<int> s, int d, int m) {
	if (s.size() < m) return 0;

	int ans = 0;

	for (int i = 1; i < s.size(); i++) {
		s[i] += s[i - 1];
	}

	if (s[m - 1] == d) ans++;

	for (int i = m; i < s.size(); i++) {
		if (s[i] - s[i - m] == d) ans++;
	}

	return ans;
}

```
