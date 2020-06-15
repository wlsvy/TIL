vector<string> m;
int row, col;
int dir[4][2] =
{
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};


int ans = 0;

void dfs(int current, int before, int k) {
    int y = current / col;
    int x = current % col;

    if (m[y][x] == '*') {
        ans = k;
        return;
    }

    stack<int> st;
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        int ny = y + dir[i][0];
        int nx = x + dir[i][1];
        int next = ny * col + nx;

        if (ny < 0 || ny >= row || nx < 0 || nx >= col) continue;
        if (m[ny][nx] == 'X') continue;
        if (next == before) continue;
        cnt++;
        st.push(next);
    }
    if (cnt > 1) {
        k++;
    }
    while (!st.empty()) {
        int next = st.top(); st.pop();
        dfs(next, current, k);
    }
}

string countLuck(vector<string> matrix, int k) {
    row = matrix.size();
    col = matrix[0].size();
    m = matrix;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (m[i][j] == 'M') {
                dfs(i * col + j, -1, 0);
                break;
            }
        }
    }
    cout << ans << " " << k << endl;
    if (ans == k) {
        return "Impressed";

    }
    return "Oops!";
}
