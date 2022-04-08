#include <vector>
#include <iostream>

using namespace std;

int direction [4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // 상하좌우순
bool visited [100][100] = {0,};
int white = 0;
int blue = 0;
int N,M;
vector<vector<char>> map;

int dfs(char color, pair<int,int> curr) {
    int cnt = 1;
    visited[curr.first][curr.second] = true;
    for (int i = 0; i < 4; i++) {
        int nextY = curr.first + direction[i][0];
        int nextX = curr.second + direction[i][1];
        if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) continue; //맵밖으로 나가는 경우 방문하지않음
        if (visited[nextY][nextX]) continue; //이미 방문한 노드인 경우 방문하지 않음
        if (map[nextY][nextX] != color) continue; // 아군 노드가 아닌 경우 방문하지 않음
        cnt += dfs(color, pair<int,int>(nextY,nextX));
    }
    return cnt;
}

int main() {
    //입력받기
    cin >> M >> N;
    map = vector<vector<char>> (N,vector<char>(M,0));
    for(int i = 0; i < N ; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    //DFS 돌리기
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(!visited[i][j]) {
                int cnt = dfs(map[i][j], pair<int,int>(i,j));
                if(map[i][j] == 'W') white += cnt * cnt;
                else if(map[i][j] == 'B') blue += cnt * cnt;
            }
        }
    }
    //결과출력
    cout << white << " " << blue << endl;
}


