#include <iostream>
#include <vector>

using namespace std;

const int DIRS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<vector<int>> map;
vector<vector<int>> dp;
int M, N;

// dp[y][x] = (0,0)에서 부터 (y,x)좌표까지 존재하는 내리막길 경로 갯수를 메모이제이션
int make_dp(int curr_y, int curr_x) {
    int &ret = dp[curr_y][curr_x];
    if (ret != -1)
        return ret;
    ret = 0;
    for (int i = 0; i < 4; i++) {
        int next_y = curr_y + DIRS[i][0];
        int next_x = curr_x + DIRS[i][1];
        if (next_y >= M || next_x >= N || next_y < 0 || next_x < 0 || map[curr_y][curr_x] >= map[next_y][next_x])
            continue;
        ret += make_dp(next_y, next_x);
    }
    return ret;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> M >> N;
    map = vector<vector<int>>(M, vector<int>(N, 0));
    dp = vector<vector<int>>(M, vector<int>(N, -1));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
    dp[0][0] = 1;
    cout << make_dp(M - 1, N - 1) << endl;
    return 0;
}
