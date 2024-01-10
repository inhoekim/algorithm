#include <iostream>
#include <vector>
#define MOD 1000000000

using namespace std;

int N;
vector<vector<long long>> dp;

/* dp[len][last_num] = len길이에 마지막 숫자가 last_num인 경우 계단 수의 갯수를 메모이제이션 */
/* dp[len][last_num] = dp[len - 1][last_num -1] + dp[len - 1][last_num + 1] */
long long make_dp(int len, int last_num) {
    long long &ret = dp[len][last_num];
    if (ret != -1)
        return ret;
    ret = 0;
    if (last_num != 9)
        ret = (ret + make_dp(len - 1, last_num + 1)) % MOD;
    if (last_num != 0)
        ret = (ret + make_dp(len - 1, last_num - 1)) % MOD;
    return ret;
}

int main(void)
{
    cin >> N;
    dp = vector<vector<long long>>(N, vector<long long> (10, -1));
    dp[0][0] = 0;
    for (int i = 1; i < 10; i++)
        dp[0][i] = 1;

    for (int i = 0; i < 10; i++)
        make_dp(N - 1, i);

    long long ret = 0;
    for (int i = 0; i < 10; i++)
        ret = (ret + dp[N - 1][i]) % MOD;
    cout << ret << endl;
    return 0;
}
