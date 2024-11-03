#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, k, m;
vector<vector<int>> grid;
vector<pair<int, int>> stones; // 돌 위치들
vector<pair<int, int>> startPoints; // 시작점들
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// 범위 체크
bool isInRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

// BFS로 시작점으로부터 도달 가능한 칸의 수를 계산
int bfs(vector<vector<int>>& tempGrid) {
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<pair<int, int>> q;
    
    // 모든 시작점을 큐에 넣음
    for (auto& p : startPoints) {
        q.push(p);
        visited[p.first][p.second] = true;
    }

    int reachable = 0;
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second; 
        q.pop();
        reachable++;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (isInRange(nx, ny) && !visited[nx][ny] && tempGrid[nx][ny] == 0) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    return reachable;
}

int main() {
    cin >> n >> k >> m;
    grid.resize(n, vector<int>(n));
    
    // 격자 입력 받기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                stones.push_back({i, j}); // 돌 위치 저장
            }
        }
    }
    
    // 시작점 입력 받기
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        startPoints.push_back({r - 1, c - 1});
    }

    int maxReachable = 0;
    
    // m개의 돌을 제거할 조합 탐색
    vector<int> comb(stones.size(), 0);
    fill(comb.begin(), comb.begin() + m, 1);
    do {
        // 임시 그리드 생성 후 돌 제거
        vector<vector<int>> tempGrid = grid;
        for (int i = 0; i < stones.size(); i++) {
            if (comb[i] == 1) {
                tempGrid[stones[i].first][stones[i].second] = 0; // 돌 제거
            }
        }
        
        // BFS로 도달 가능한 칸의 수 계산
        maxReachable = max(maxReachable, bfs(tempGrid));
    } while (prev_permutation(comb.begin(), comb.end()));
    
    cout << maxReachable << endl;
    return 0;
}