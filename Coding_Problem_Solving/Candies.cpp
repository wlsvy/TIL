long long candies(int n, vector<int> arr) {

    stack<int> st, rst;
    vector<long long> candyCnt(arr.size(), 0);

    for (int i = 0; i < arr.size(); ) {
        if (st.empty() || st.top() < arr[i]) {
            st.push(arr[i]);
            candyCnt[i] = st.size();
            i++;
            continue;
        }

        if (st.top() == arr[i]) {
            while (!st.empty()) st.pop();
            st.push(arr[i]);
            candyCnt[i] = st.size();

            i++;
            continue;
        }

        int j = i;
        while (arr[j - 1] > arr[j]) {
            j++;
            if (j >= arr.size())  break;
        }
        int next = --j;
        //cout << "next " << next << " i : " << i << endl;
        while (j >= i - 1) {
            rst.push(arr[j]);
            candyCnt[j] = max(candyCnt[j], (long long)rst.size());

            j--;
        }

        i = next;

        while (!st.empty()) st.pop();
        while (!rst.empty()) rst.pop();
    }

    long long sum = 0;
    for (auto c : candyCnt) {
        sum += c;
    }

    return sum;
}
