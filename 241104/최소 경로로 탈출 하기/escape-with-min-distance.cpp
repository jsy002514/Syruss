#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> arr;
vector<vector<bool>> visited;
vector<vector<int>> step;

bool can_go(int x, int y) {
    // 격자 안에 있어야 하고, 뱀이 없으며, 방문하지 않은 점이어야 함
    if (x < 0 || x >= n || y < 0 || y >= m)
        return false;
    if (arr[x][y] == 0 || visited[x][y])
        return false;
    return true;
}

void push(queue<pair<int, int>> &qe, int x, int y, int s) {
    qe.push({x, y});
    visited[x][y] = true;
    step[x][y] = s;
}

int main() {
    cin >> n >> m;

    arr.resize(n, vector<int>(m));
    visited.resize(n, vector<bool>(m, false));
    step.resize(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }

    queue<pair<int, int>> qe;
    push(qe, 0, 0, 0);  // 시작점을 (0, 0)으로 초기화, 첫 번째 스텝은 1부터 시작

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!qe.empty()) {
        int x = qe.front().first;
        int y = qe.front().second;
        qe.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (can_go(nx, ny)) {
                push(qe, nx, ny, step[x][y] + 1);
            }
        }
    }

    // 우측 하단까지 도달했는지 확인
    if (visited[n - 1][m - 1]) {
        cout << step[n - 1][m - 1] << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}