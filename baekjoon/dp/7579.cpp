#include <iostream>
#include <vector>
#include <algorithm>
#define MEM first
#define COST second
using namespace std;

int N, M;
vector<pair<int, int>> apps;

// dp[app_lst][total_cost] = 주어진 cost를 이용해서 해제할 수 있는 최대메모리를 메모이제이션
//                         = max(dp[app_lst - 1][total_cost], dp[app_lst -1][total_cost - cost[app_idx]] + mem[app_idx])
int dp[100][10001];

int make_dp(int app_lst, int total_cost) {
    if (app_lst < 0)
        return 0;
    int &ret = dp[app_lst][total_cost];
    if (ret != -1)
        return ret;
    ret = make_dp(app_lst - 1, total_cost);
    if (total_cost >= apps[app_lst].COST)
        ret = max(ret, make_dp(app_lst - 1, total_cost - apps[app_lst].COST) + apps[app_lst].MEM);
    return ret;
}

int main(void) {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int memory;
        cin >> memory;
        apps.push_back({memory, 0});
    }
    for (int i = 0; i < N; i++) {
        int cost;
        cin >> cost;
        apps[i].COST = cost;
    }
    fill(&dp[0][0], &dp[99][10001], -1);
    for (int i = 0; i <= 10000; i++) {
        int mem = make_dp(N - 1, i);
        if (mem >= M) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
