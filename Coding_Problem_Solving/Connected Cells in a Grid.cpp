vector<vector<bool>> check;
vector<vector<int>> M;
int row;
int col;
int maxVal = 1;

int dir[8][2] =
{
    {0, 1},
    {1, 0},
    {1, 1},
    {0, -1},
    {-1, 0},
    {-1, -1},
    {-1, 1},
    {1, -1}
};

void FindAdjacent(int y, int x, int& size) {
    for (int i = 0; i < 8; i++) {
        int nx = dir[i][0] + x;
        int ny = dir[i][1] + y;

        if (nx < 0 || nx >= col || ny < 0 || ny >= row) continue;
        if (check[ny][nx]) continue;

        if (M[ny][nx] == 1) {
            check[ny][nx] = true;
            size++;
            FindAdjacent(ny, nx, size);
        }
    }
}

int connectedCell(vector<vector<int>> matrix) {
    M = matrix;
    row = matrix.size();
    col = matrix[0].size();
    check = vector<vector<bool>>(row, vector<bool>(col, false));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == 0) continue;
            if (check[i][j]) continue;

            check[i][j] = true;
            int size = 1;
            FindAdjacent(i, j, size);
            if (size > maxVal) {
                maxVal = size;
            }

        }
    }

    return maxVal;
}
