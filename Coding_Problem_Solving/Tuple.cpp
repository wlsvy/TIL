#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

vector<int> answer;

struct comp {
	bool operator()(const vector<int>& l, const vector<int>& r) { return l.size() < r.size(); }
};
set<vector<int>, comp> vset;

vector<int> solution(string s) {
	auto braceStartPos = s.find('{', 1);
	while (braceStartPos != string::npos) {

		auto braceEndPos = s.find('}', braceStartPos);
		auto numStartPos = braceStartPos + 1;
		auto commaPos = s.find(',', braceStartPos);

		vector<int> tmp;

		while (commaPos != string::npos && commaPos < braceEndPos) {
			tmp.push_back(stoi(s.substr(numStartPos, commaPos - numStartPos)));
			numStartPos = commaPos + 1;
			commaPos = s.find(',', commaPos + 1);
		}
		tmp.push_back(stoi(s.substr(numStartPos, braceEndPos - numStartPos)));
		vset.insert(move(tmp));

		braceStartPos = s.find('{', braceStartPos + 1);
	}

	for(auto v : vset)
	{
		for (auto i : v) {
			if (find(answer.begin(), answer.end(), i) == answer.end()) answer.push_back(i);
		}
	}

	return answer;
}
