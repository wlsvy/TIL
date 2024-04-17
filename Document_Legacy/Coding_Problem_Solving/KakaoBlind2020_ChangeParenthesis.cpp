#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>

using namespace std;

bool isValid(string & s) {
	stack<char> st;
	for (auto c : s) {
		switch (c) {
		case '(' : st.push(c); break;
		case ')':
		{
			if (st.empty()) return false;
			st.pop();
			break;
		}
		}
	}
	return st.empty();
}

void split(string & inS, string & outU, string & outV) {
	outU = "";
	outV = "";

	int i0 = 0, i1 = 0;
	for (int i = 0; i < inS.size(); i++) {
		if (inS[i] == '(') i0++;
		else i1++;

		if (i0 == i1) {
			outU = inS.substr(0, i + 1);
			outV = inS.substr(i + 1);
			break;
		}
	}
}

void flip(string & s) {
	for (auto& c : s) {
		c = (c == '(' ? ')' : '(');
	}
}

string Process(string s) {
	if (s == "") return s;

	string u, v;
	split(s, u, v);
	if (isValid(u)) {
		u += Process(v);

		return u;
	}
	else {
		string tmp = "(" + Process(v) + ")";
		u.erase(u.begin());
		u.erase(u.end() - 1);
		flip(u);
		tmp += u;
		return tmp;
	}
}

string solution(string p) {
	if (isValid(p)) return p;

	return Process(p);
}
