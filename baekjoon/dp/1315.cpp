#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

typedef struct quest {
    int demand_str;
    int demand_int;
    int pnt;
}quest;

int N;
vector<quest> quest_list;
vector<vector<int>> dp;
vector<bool> visited;

// dp[str_val][int_val] = 힘수치가 str_val이고, 지능수치가 int_val일 때, 깰 수 있는 최대 quest를 메모이제이션
int make_dp(int curr_str, int curr_int) {
    int &ret = dp[curr_str][curr_int];
    if (ret != -1)
        return ret;
    int cnt = 0;
    int pnt = 0;
    vector<int> idx_cache;
    for (int i = 0; i < N; i++) {
        if ((quest_list[i].demand_str <= curr_str || quest_list[i].demand_int <= curr_int)) {
            cnt++;
            if (visited[i])
                continue;
            pnt += quest_list[i].pnt;
            visited[i] = true;
            idx_cache.push_back(i);
        }
    }
    ret = cnt;
    for (int i = 0; i <= pnt; i++) {
        int next_str = min(1000, curr_str + i);
        int next_int = min(1000, curr_int + pnt - i);
        ret = max(ret, make_dp(next_str, next_int));
    }
    for (int i : idx_cache)
        visited[i] = false;
    return ret;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        quest q;
        cin >> q.demand_str >> q.demand_int >> q.pnt;
        quest_list.push_back(q);
    }
    dp = vector<vector<int>>(1001, vector<int>(1001, -1));
    visited = vector<bool>(N, false);
    cout << make_dp(1, 1) << endl;
    return 0;
}
