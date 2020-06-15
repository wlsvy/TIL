/*
==============
첫번째 방법
==============
*/
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

/*
==============
두번째 방법
==============
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> convert(string s, int n)
{
    vector<string> v;
    for(int i = 0 ; i <s.length() ; i+=n)
    {
        v.push_back(s.substr(i,n));
    }
    return v;
}

int solution(string s) {
    int answer = 0;
    vector<string> tok;
    string before;
    int cnt = 1;
    int min = s.length();
    string str="";
    for(int j = 1 ; j <= s.length()/2 ; j++)
    {
        tok = convert(s,j);
        str = "";
        before = tok[0];
        cnt = 1;
        for(int i = 1 ; i < tok.size() ; i++)
        {
            if(tok[i] == before) cnt++;
            else
            {
                if(cnt != 1) str += to_string(cnt);
                str += before;
                before = tok[i];
                cnt = 1;
            }
        }
        if(cnt != 1)str += to_string(cnt);
        str += before;  
        min = min<str.length() ? min : str.length();
    }
    cout<<str;

    return min;
}
