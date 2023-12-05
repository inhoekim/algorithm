#include <iostream>
#include <algorithm>
#define MOD 1000000000
using namespace std;

/* dp[i][k] = k개를 더해서 i를 만드는 경우의 수의 갯수 */
int dp[202][202];

int main(void) {
    fill(&dp[0][0], &dp[200][201], 0);
    for (int i = 0; i < 201; i++) {
        dp[0][i + 1] = 1;
        dp[i][1] = 1;
    }
    int N, K;
    cin >> N >> K;
    for (int k = 2; k <= K; k++) {
        for (int n = 1; n <= N; n++) {
            int result = 0;
            for (int cal_n = n; cal_n >= 0; cal_n--) {
                    int a, b;
                    a = dp[cal_n][k - 1];
                    b = dp[n - cal_n][1];
                    result = (result + (a * b) % MOD) % MOD;
            }
            dp[n][k] = result;
        }
    }
    cout << dp[N][K] << endl;
}
