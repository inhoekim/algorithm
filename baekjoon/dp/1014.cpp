#include <iostream>
#include <vector>
#include <algorithm>
#define EMPTY '.'

using namespace std;

int N, M;
vector<vector<char>> map;
vector<vector<int>> dp;

int check_state(int col, int curr_state, int before_state) {
    int cnt = 0;
    bool continuity = false;
    for (int i = 0; i < M; i++) {
        if (curr_state & (1 << (M - 1 - i))) {
            if (map[col][i] != EMPTY || continuity)
                return -1;
            if (before_state & (1 << (M - i)) || \
                ((M - 2 - i >= 0) && before_state & (1 << (M - 2 - i))))
                return -1;
            continuity = true;
            cnt++;
        }
        else
            continuity = false;
    }
    return cnt;
}
/* dp[col][curr_state] = col번째줄에 curr_state 상태로 학생을 앉혔을 경우, col~마지막번째 줄까지 앉힐 수 있는 최대 학생의 수를 메모이제이션 */
int make_dp(int col, int curr_state) {
    if (col == N)
        return 0;
    int &ret = dp[col][curr_state];
    if (ret != -1)
        return ret;
    for (int next_state = 0; next_state < (1 << M); next_state++) {
        int curr_man_cnt = check_state(col, curr_state, next_state);
        if (curr_man_cnt != -1)
            ret = max(ret, make_dp(col + 1, next_state) + curr_man_cnt);
    }
    return ret;
}

int main(void) {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        map = vector<vector<char>>(N, vector<char>(M, 0));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> map[i][j];
        dp = vector<vector<int>>(N, vector<int>(1 << M ,-1));
        int ret = 0;
        for (int i = 0; i < 1 << M; i++)
            ret = max(ret, make_dp(0, i));
        cout << ret << endl;
    }
    return 0;
}
