#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

int solution(string s) {
	int len = s.size();
	int answer = len;

	for (int i = 1; i <= len / 2; i++) {
		string result = "";
		auto target = s.substr(0, i);
		int cnt = 2;

		for (int j = i; j <= len; j += i) {
			if (s.substr(j, i) == target) {
				cnt++;
			}
			else {
				if (cnt > 2)result += to_string(cnt);
				result += target;
				cnt = 2;
				target = s.substr(j, i);
			}


		}
		if (len / i != 0) result += s.substr((len / i)*i);
		answer = min(answer, (int)result.size());
	}


	return answer;
}

