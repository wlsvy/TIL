#include <bits/stdc++.h>
using namespace std;

vector<float> start, finish;

int solution(vector<string> lines) {
	auto N = lines.size();

	for (auto& line : lines) {
		auto secPos = line.find('s');
		auto h = stof(line.substr(11, 2));
		auto m = stof(line.substr(14, 2));
		auto s = stof(line.substr(17, 6));
		auto t = stof(line.substr(24, secPos - 24));
		start.push_back(h * 3600 + m * 60 + s - t + 0.001f);
		finish.push_back(h * 3600 + m * 60 + s);
	}
	
	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		auto testTarget =
		{
			start[i] - 0.999f, 
			start[i], 
			finish[i] - 0.999f,
			finish[i]
		};
		for (auto t : testTarget) {
			int tmp = 0;
			for (int j = 0; j < N; j++) {

				if ((t <= start[j] && start[j] < t + 1.0f) ||
					(t <= finish[j] && finish[j] < t + 1.0f) ||
					(t <= start[j] && finish[j] < t + 1.0f) ||
					(start[j] <= t && t + 1.0f <= finish[j]))
				{
					tmp++;
				}
			}
			answer = max(answer, tmp);
		}
	}

	return answer;
}
