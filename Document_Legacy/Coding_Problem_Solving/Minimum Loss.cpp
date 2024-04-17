long long minimumLoss(vector<long> price) {
    long long m = LLONG_MIN;

    vector<pair<long, long>> vec;
    for (int i = 0; i < price.size(); i++) {
        vec.push_back(make_pair(price[i], i));
    }
    sort(vec.begin(), vec.end(), [](pair<long, long>& lhs, pair<long, long>& rhs)
    {
        return  lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first > rhs.first;
    });

    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i].second < vec[i + 1].second) {
            if (m < vec[i + 1].first - vec[i].first) {
                m = vec[i + 1].first - vec[i].first;
            }
        }
    }

    return abs(m);
}
