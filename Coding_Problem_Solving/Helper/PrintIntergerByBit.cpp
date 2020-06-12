#include <iostream>
#include <string>
void PrintBit(int n) {
	using namespace std;
	if (n == 0) {
		cout << '0' << endl;
		return;
	}
	string str = "";
	while (n > 0) {
		str += '0' + n % 2;
		n = n >> 1;
	}
	for (auto iter = str.rbegin(); iter != str.rend(); iter++) {
		cout << *iter;
	}
	cout << endl;
}
