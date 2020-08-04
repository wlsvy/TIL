#include <bits/stdc++.h>
using namespace std;

vector<float> vf[2];

int solution(vector<string> lines) {
	auto N = lines.size();

	for (auto& line : lines) {
		auto secPos = line.find('s');
		auto h = stof(line.substr(11, 2));
		auto m = stof(line.substr(14, 2));
		auto s = stof(line.substr(17, 6));
		auto t = stof(line.substr(24, secPos - 24));
		vf[0].push_back(h * 3600 + m * 60 + s - t + 0.001f);
		vf[1].push_back(h * 3600 + m * 60 + s);
	}
	
	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		auto testTarget =
		{
			vf[0][i] - 0.999f, 
			vf[0][i], 
			vf[1][i] - 0.999f, 
			vf[1][i]
		};
		for (auto t : testTarget) {
			int tmp = 0;
			for (int j = 0; j < N; j++) {

				if ((t <= vf[0][j] && vf[0][j] < t + 1.0f) ||
					(t <= vf[1][j] && vf[1][j] < t + 1.0f) ||
					(t <= vf[0][j] && vf[1][j] < t + 1.0f) ||
					(vf[0][j] <= t && t + 1.0f < vf[1][j]))
				{
					tmp++;
				}
			}
			answer = max(answer, tmp);
		}
	}

	return answer;
}
