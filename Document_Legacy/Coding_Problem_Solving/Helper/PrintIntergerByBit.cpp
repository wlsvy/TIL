#include <algorithm>
#include <iostream>
#include <string>

void PrintBit(int n) {
	if (n == 0) {
		std::cout << '0' << std::endl;
		return;
	}
	std::string str = "";
	while (n > 0) {
		str += '0' + n % 2;
		n = n >> 1;
	}
	std::reverse(str.begin(), str.end());
	std::cout << str << std::endl;
}

template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
bool GetBit(T x, unsigned int n) {
	return x & (1 << n);
}

//컴파일러가 enable_if 지원하지 않을 때
bool GetBit(int x, unsigned int n) {
	return x & (1 << n);
}
