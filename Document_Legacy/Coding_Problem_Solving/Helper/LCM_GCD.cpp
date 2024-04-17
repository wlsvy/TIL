int gcd(int a, int b) {
	int maxval = max(a, b);
	int minval = min(a, b);

	int rest = maxval % minval;
	while (rest != 0) {
		maxval = minval;
		minval = rest;
		rest = maxval % minval;
	}

	return minval;
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
}
