#include <algorithm>
#include <iostream>
using namespace std;
using LL = long long;

LL gcd(LL a, LL b) {
	LL maxval = max(a, b);
	LL minval = min(a, b);

	LL rest = maxval % minval;
	while (rest != 0) {
		maxval = minval;
		minval = rest;
		rest = maxval % minval;
	}

	return minval;
}

LL solution(int w, int h) {
    LL area = (LL)w * h;
	LL gcdVal = gcd(w, h);

	return area - ((LL)w / gcdVal + (LL)h / gcdVal - 1) * gcdVal;
}
