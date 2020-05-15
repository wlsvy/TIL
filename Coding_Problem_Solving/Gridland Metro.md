# problem
- [해커랭크 문제 링크](https://www.hackerrank.com/challenges/gridland-metro/problem)

세로 크기 n, 가로 크기 m 인 격자판(grid)에 대해서 (1 <= n, m <= 10^9)  

특정 조건에 따라 특정 격자의 판을 색칠한다고 하면

최종적으로 색칠되지 않은 칸의 갯수를 구하는 문제.


* 가로/세로 크기가 각각 최대 10^9 까지 될 수 있기 때문에, for문으로 전체 칸을 순회하는 방법은 불가능

# Submission
```
void Merge(vector<pair<int, int>> & vp, vector<int> & t) {
    auto src = make_pair(t[1], t[2]);

    if(vp.size() == 0) {
      vp.push_back(src); 
      return;
    }
      
    auto& p = vp.back();
    if (p.second >= src.second) {
        return;
    }
    else {
        if (p.second < src.first) {
            vp.push_back(src);
        }
        else {
            p.second = src.second;
        }
    }
}

long long gridlandMetro(int n, int m, int k, vector<vector<int>> track) {

    sort(track.begin(), track.end());
    
    map<int, vector<pair<int, int>>> rowMap;

    for (auto& t : track) {
        Merge(rowMap[t[0]], t);
    }

    long long ans = 0;
    for(auto & v : rowMap){
        for(auto &p :  v.second){
            ans += p.second - p.first + 1;
        }
    }

    ans = (long long)m * n - ans;
    return ans;
}

```
