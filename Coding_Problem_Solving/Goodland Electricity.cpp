int pylons(int k, vector<int> arr) {
    auto prev = vector<int>(arr.size(), -1);

    int last = -1;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1) last = i;
        prev[i] = last;
    }

    int ans = 0;
    for (int i = 0; i < arr.size();) {
        int take = prev[min(i + k - 1, (int)arr.size() - 1)];
        if (take == -1 || take + k <= i) return -1;
        i = take + k; 
        ans++;
    }

    return ans;
}
