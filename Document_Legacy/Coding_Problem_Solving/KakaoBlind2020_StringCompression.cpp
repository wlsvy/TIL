/*
==============
첫번째 방법
==============
*/
#include <bits/stdc++.h>
using namespace std;

int solution(string s) {
    int answer = s.length();
    for (int len = s.length() / 2; len >= 1; len--) {
        int cnt = 1;
        string sub = s.substr(0, len);
        string temp = "";
        for (int j = len; j <= s.length(); j += len) {
            if (sub == s.substr(j, len)) {
                cnt++;
            }
            else {
                if (cnt == 1)
                    temp += sub;
                else
                    temp += (to_string(cnt) + sub);
                sub = s.substr(j, len);
                cnt = 1;
            }
            if (j + len > s.length()) {
                temp += s.substr(j, s.length());
                break;
            }
        }
        answer = min(answer, (int)temp.length());
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
