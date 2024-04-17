int n, Rot;
vector<vector<int>> input;
vector<vector<int>> output;


void RotateLayer(int by, int bx, int row, int col) {
    int y = 0;
    int x = 0;
    int layerSize = (row + col - 2) * 2;
    vector<int> layer;

    for (int i = 0; i < col - 1; i++) {
        layer.push_back(y * col + x);
        x++;
    }
    for (int i = 0; i < row - 1; i++) {
        layer.push_back(y * col + x);
        y++;
    }
    for (int i = 0; i < col - 1; i++) {
        layer.push_back(y * col + x);
        x--;
    }
    for (int i = 0; i < row - 1; i++) {
        layer.push_back(y * col + x);
        y--;
    }
    int r = Rot % layerSize;
    r = r > 0 ? r : layerSize + r;
    
    for (int i = 0; i < layerSize; i++) {
        y = layer[i] / col;
        x = layer[i] % col;
        int ny = layer[(i + r) % layerSize] / col;
        int nx = layer[(i + r) % layerSize] % col;
        output[by + ny][bx + nx] = input[by + y][bx + x];
    }
}


void matrixRotation(vector<vector<int>> matrix, int r) {
    int row = matrix.size();
    int col = matrix[0].size();
    int maxDepth = min(row, col) / 2;

    input = matrix;
    output = matrix;
    Rot = -r;

    for (int i = 0; i < maxDepth; i++) {
        RotateLayer(i, i, row - 2 * i, col - 2 * i);
    }

    for (auto vs : output) {
        for (int i = 0; i < vs.size(); i++) {
            cout << vs[i];
            if (i != vs.size() - 1) {
                cout << ' ';
            }
        }
        cout << endl;
    }
}
