    #include <string>
    #include <vector>
    #include <iostream>
    #include <set>
    #include <map>
    #include <algorithm>
    using namespace std;

    struct comp {
        bool operator()(const vector<int>& l, const vector<int>& r) {
            auto ld = l[1] - l[0];
            auto rd = r[1] - r[0];
            return ld == rd ? less<vector<int>>()(l, r) : ld < rd;
        }
    };
    set<vector<int>, comp> answer;

    vector<int> solution(vector<string> gems) {

        map<string, int> m;
        set<string> s = set<string>(gems.begin(), gems.end());
        auto gemCount = s.size();
        s.clear();

        int begin = 0, end = 0;
        for (; begin < gems.size(); ) {
            int prevB = begin, prevE = end;
            while (s.size() < gemCount && end < gems.size()) {
                s.insert(gems[end]);
                m[gems[end]]++;
                end++;
            }
            if (s.size() >= gemCount) {
                answer.insert({ begin + 1, end });
            }
            while (s.size() >= gemCount && begin < gems.size()) {
                m[gems[begin]]--;
                if (m[gems[begin]] <= 0) s.erase(gems[begin]);
                begin++;
            }

            if (s.size() >= gemCount - 1) {
                answer.insert({ begin, end });
            }
            if (prevB == begin && prevE == end) break;
        }

        return *answer.begin();
    }

