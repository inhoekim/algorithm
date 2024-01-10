#include <iostream>
#include <vector>
#define MOD 1000000000

using namespace std;

int N;
vector<vector<vector<long long>>> dp;

/* dp[len][last_num][used_num] = len길이에 마지막 숫자가 last_num이고 지금까지 사용하는 수의 종류가 used_num 일때 -> 길이 N까지 진행하는 동안 생기는 계단 수의 갯수를 메모이제이션 */
/* dp[len][last_num][used_num] = dp[len - 1][last_num -1] + dp[len - 1][last_num + 1] */
long long make_dp(int len, int last_num, int used_num) {
    if (len == N) {
        if (used_num == 1023)
            return 1;
        else
            return 0;
    }
    long long &ret = dp[len][last_num][used_num];
    if (ret != -1)
        return ret;
    ret = 0;
    if (last_num != 9)
        ret = (ret + make_dp(len + 1, last_num + 1, used_num | (1 << last_num + 1))) % MOD;
    if (last_num != 0)
        ret = (ret + make_dp(len + 1, last_num - 1, used_num | 1 << (last_num - 1))) % MOD;
    return ret;
}

int main(void)
{
    cin >> N;
    dp = vector<vector<vector<long long>>>(N + 1, vector<vector<long long>>(10, vector<long long>(1024, -1)));
    long long ret = 0;
    for (int i = 1; i < 10; i++)
        ret = (ret + make_dp(1, i, 1 << i)) % MOD;
    cout << ret << endl;
    return 0;
}
