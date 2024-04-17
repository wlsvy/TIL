#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    static int last = 2;
    static set<int> prime = { last };
    for (; last <= n; last++)
    {
         if (all_of(prime.begin(), prime.end(), [](int p) { return last % p != 0; })) {
            prime.insert(last);
        }
    }
    return prime.find(n) != prime.end();
}

int solution(vector<int> nums) {
    int answer = 0;

    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            for (int k = j + 1; k < nums.size(); k++) {
                auto sum = nums[i] + nums[j] + nums[k];
                if (isPrime(sum)) {
                    answer++;
                }
            }
        }
    }

    //for (auto i : prime) cout << i << " "; cout << endl;

    return answer;
}
