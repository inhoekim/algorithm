#include <iostream>
#include <vector>
#include <algorithm>

#define Y first
#define X second

using namespace std;

int N, M;
vector<vector<int>> dp;
vector<vector<char>> map;
vector<vector<bool>> is_making_dp;
bool is_cycle = false;

const int DIRS[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int make_dp(pair<int,int> here) {
    if (is_cycle)
        return -1;
    int &ret = dp[here.Y][here.X];
    ret = 1;
    is_making_dp[here.Y][here.X] = true;
    for (int i = 0; i < 4; i++) {
        int next_y = here.Y + ((map[here.Y][here.X] - '0') * DIRS[i][0]);
        int next_x = here.X + ((map[here.Y][here.X] - '0') * DIRS[i][1]);
        if (next_y < 0 || next_y >= N || next_x < 0 || next_x >= M || map[next_y][next_x] == 'H')
            continue;
        if (dp[next_y][next_x] != -1) {
            if (is_making_dp[next_y][next_x]) {
                is_cycle = true;
                return -1;
            }
            ret = max(ret, dp[next_y][next_x] + 1);
        }
        else
            ret = max(ret, make_dp({next_y, next_x}) + 1);
    }
    is_making_dp[here.Y][here.X] = false;
    return ret;
}

int main(void) {
    cin >> N >> M;
    dp = vector<vector<int>>(N, vector<int>(M, -1));
    map = vector<vector<char>>(N, vector<char>(M, 0));
    is_making_dp = vector<vector<bool>>(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    make_dp({0, 0});
    if (is_cycle)
        cout << -1 << endl;
    else
        cout << dp[0][0] << endl;
    return 0;
}
