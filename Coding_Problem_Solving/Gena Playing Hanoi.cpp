#include <bits/stdc++.h>

using namespace std;

int N;
int dist[1 << 20];
queue<int> q;

int moveDir[12][2] =
{
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 0},
    {1, 2},
    {1, 3},
    {2, 0},
    {2, 1},
    {2, 3},
    {3, 0},
    {3, 1},
    {3, 2}
};

int main() {

    cin >> N;
    int startMask = 0;
    for (int i = 0; i < N; i++) {
        int k;
        cin >> k;
        startMask |= ((k - 1) << (2 * i));
    }

    fill(dist, dist + (int)(1 << 20), INT_MAX);

    dist[startMask] = 0;
    q.push(startMask);

    while (!q.empty()) {
        int mask = q.front();
        q.pop();

        if (mask == 0) break;

        int hanoiTop[] = { INT_MAX, INT_MAX, INT_MAX, INT_MAX };
        for (int i = N - 1; i >= 0; i--) {
            hanoiTop[(mask >> (2 * i)) & 3] = i;
        }

        for (auto m : moveDir) {
            if (hanoiTop[m[0]] == INT_MAX) continue;
            if (hanoiTop[m[0]] >= hanoiTop[m[1]]) continue;

            int disc = hanoiTop[m[0]];
            int newMask = mask - (m[0] << (2 * disc)) + (m[1] << (2 * disc));

            if (dist[newMask] > dist[mask] + 1) {
                dist[newMask] = dist[mask] + 1;
                q.push(newMask);
            }
        }
    }
    cout << dist[0] << '\n';
}
