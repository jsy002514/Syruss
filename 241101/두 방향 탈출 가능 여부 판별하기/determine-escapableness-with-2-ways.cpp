#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isPathToExit(int n, int m, vector<vector<int>>& grid) {
    // BFS를 위한 큐, 시작 위치 (0, 0)에서 출발
    queue<pair<int, int>> q;
    q.push({0, 0});

    // 방문 여부를 저장하는 2차원 배열
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    visited[0][0] = true;

    // 이동할 수 있는 방향 (오른쪽, 아래쪽)
    int dx[2] = {0, 1}; // x축: 오른쪽 이동
    int dy[2] = {1, 0}; // y축: 아래쪽 이동

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 도착 위치에 도달했을 경우 경로가 있으므로 1 반환
        if (x == n - 1 && y == m - 1) {
            return true;
        }

        // 오른쪽과 아래쪽으로 이동 가능한지 확인
        for (int i = 0; i < 2; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 격자 안에 있으며 뱀이 없고, 방문하지 않은 경우에만 이동
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    // 경로가 없다면 0 반환
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // 경로가 있으면 1, 없으면 0을 출력
    cout << (isPathToExit(n, m, grid) ? 1 : 0) << endl;
    return 0;
}