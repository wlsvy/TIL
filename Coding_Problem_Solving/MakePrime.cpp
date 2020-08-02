#include <bits/stdc++.h>
using namespace std;

set<int> prime = { 2 };

bool isPrime(int n) {

    for (int i = *(--prime.end()) + 1; i <= n; i++)
    {
         if (all_of(prime.begin(), prime.end(), [i](int p) { return i % p != 0; })) {
            prime.insert(i);
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
