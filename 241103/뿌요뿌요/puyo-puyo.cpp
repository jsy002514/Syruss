#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> arr;
vector<vector<bool>> isVisited;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// 범위 검사
bool isRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

// DFS로 블록의 크기를 구하는 함수
int dfs(int x, int y, int num) {
    isVisited[x][y] = true;
    int size = 1;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (isRange(nx, ny) && !isVisited[nx][ny] && arr[nx][ny] == num) {
            size += dfs(nx, ny, num);
        }
    }
    
    return size;
}

int main() {
    cin >> n;
    arr.resize(n, vector<int>(n, -1));
    isVisited.resize(n, vector<bool>(n, false));
    
    // 격자 입력 받기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    
    int blockCount = 0;     // 터지는 블록의 수
    int maxBlockSize = 0;   // 최대 블록 크기
    int maxBlockNum = 0;    // 최대 블록의 숫자

    // 모든 칸을 탐색하며 블록 크기 구하기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!isVisited[i][j]) {
                int num = arr[i][j];
                int blockSize = dfs(i, j, num);
                
                // 블록 크기가 4 이상인 경우 터지게 처리
                if (blockSize >= 4) {
                    blockCount++;
                    // 최대 블록 크기와 숫자 갱신
                    if (blockSize > maxBlockSize) {
                        maxBlockSize = blockSize;
                        maxBlockNum = num;
                    }
                }
            }
        }
    }

    cout << blockCount <<" " << maxBlockSize << endl;
    return 0;
}