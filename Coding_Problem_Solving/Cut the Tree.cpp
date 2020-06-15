struct node {
    int weight;
    int childrenWeight = 0;
    vector<int> adjacent;
};

vector<node> nodes;
int answer = INT_MAX;
int allNodeWeight = 0;

void dfs(int index, int parent) {
    for (auto a : nodes[index].adjacent) {
        if (a == parent) continue;

        dfs(a, index);
        nodes[index].childrenWeight += nodes[a].weight + nodes[a].childrenWeight;
    }
    int totalWeight = nodes[index].weight + nodes[index].childrenWeight;
    
    if (index != 0 && answer > abs(allNodeWeight - 2 * totalWeight)) {
        answer = abs(allNodeWeight - 2 * totalWeight);
    }
}

int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    for (auto d : data) {
        nodes.push_back(node());
        nodes.back().weight = d;
        allNodeWeight += d;
    }
    
    for (auto& e : edges) {
        nodes[e[1] - 1].adjacent.push_back(e[0] - 1);
        nodes[e[0] - 1].adjacent.push_back(e[1] - 1);
    }

    dfs(0, -1);
    
    return answer;
}
