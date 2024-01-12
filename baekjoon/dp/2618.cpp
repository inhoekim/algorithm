#include <iostream>
#include <vector>
#include <sstream>
#define Y first
#define X second

using namespace std;

int N, W;
vector<pair<int, int>> cases;
vector<vector<vector<int>>> dp;
stringstream ss;

int get_dist(pair<int, int> a, pair<int, int> b) {
    return abs(a.Y - b.Y) + abs(a.X - b.X);
}

// dp[a_idx][b_idx] = 경찰차 a가 마지막으로 해결한 사건이 a_idx이고 경찰차 b가 마지막으로 해결한 사건이 b_idx일 때 -> 마지막 사건 idx까지 진행했을 때의 최소 이동거리를 메모이제이션
/*
 * dp[a_idx][b_idx] = min {
 *                      dp[next_case][b_idx] + (next_case 사건위치와 a_idx 사건위치의 이동거리)
 *                      dp[a_idx][next_case] + (next_case 사건위치와 b_idx 사건위치의 이동거리)
 *                   }
*/
vector<int> make_dp(int a_idx, int b_idx) {
    vector<int> &ret = dp[a_idx][b_idx];
    if (ret[0] != -1)
        return ret;
    int next_case = max(a_idx, b_idx) + 1;
    if (next_case == W + 2) {
        ret[0] = 0;
        return ret;
    }
    vector<int> a_dist = make_dp(next_case, b_idx);
    a_dist[0] += get_dist(cases[next_case], cases[a_idx]);
    vector<int> b_dist = make_dp(a_idx, next_case);
    b_dist[0] += get_dist(cases[next_case], cases[b_idx]);
    ret = min(a_dist, b_dist);
    if (a_dist[0] < b_dist[0]) {
        ret[1] = next_case;
        ret[2] = b_idx;
    }
    else {
        ret[1] = a_idx;
        ret[2] = next_case;
    }
    return ret;
}

void get_order() {
    vector<int> curr_vec = dp[0][1];
    int curr_case = 2;
    while (curr_case < W + 2) {
        if (curr_case == curr_vec[1])
            ss << "1\n";
        else if (curr_case == curr_vec[2])
            ss << "2\n";
        curr_case++;
        curr_vec = dp[curr_vec[1]][curr_vec[2]];
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> W;
    cases.push_back({0, 0});
    cases.push_back({N - 1, N - 1});
    for (int i = 0; i < W; i++) {
        int y, x;
        cin >> y >> x;
        cases.push_back({y - 1, x - 1});
    }
    dp = vector<vector<vector<int>>>(W + 2, vector<vector<int>>(W + 2, vector<int>(3, -1)));
    cout << make_dp(0, 1)[0] << endl;
    get_order();
    cout << ss.str();
    return 0;
}
