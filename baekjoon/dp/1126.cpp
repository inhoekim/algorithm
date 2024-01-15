#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321
using namespace std;

int N;
vector<int> blocks;
vector<vector<int>> dp;

/* dp[curr_block_idx][height_diff] = 현재 curr_block_idx를 선택할 차례에 두 탑의 높이 차이가 height_diff일 때, N번_idx까지 진행했을 때 만들 수 있는 같은 높이의 탑의 최대 높이를 메모이제이션 */
// dp[curr_block_idx][height_diff] = max(dp[curr_block_idx + 1][height_diff + block_hegiht] , dp[curr_block_idx + 1][height_diff - block_height]);
int make_dp(int curr_block_idx, int h_diff) {
    if (curr_block_idx == N) {
        if (h_diff == 0)
            return 0;
        else
            return -INF;
    }
    int &ret = dp[curr_block_idx][h_diff];
    if (ret != -1)
        return ret;
    ret = make_dp(curr_block_idx + 1, h_diff + blocks[curr_block_idx]) + blocks[curr_block_idx];
    int temp_ret = make_dp(curr_block_idx + 1, abs(h_diff - blocks[curr_block_idx]));
    if (h_diff - blocks[curr_block_idx] < 0) {
        temp_ret += abs(h_diff - blocks[curr_block_idx]);
    }
    ret = max(ret , temp_ret);
    ret = max(ret, make_dp(curr_block_idx + 1, h_diff));
    return ret;
}

int main(void) {
    cin >> N;
    int total_num = 0;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        blocks.push_back(num);
        total_num += num;
    }
    dp = vector<vector<int>>(N, vector<int>(total_num + 1, -1));
    int ret = make_dp(0, 0);
    if (ret <= 0)
        ret = -1;
    cout << ret << endl;
    return 0;
}
