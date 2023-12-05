#include <iostream>
#define MOD 9901
​
using namespace std;
​
int main(void) {
    int N;
    cin >> N;
    /*dp[N][0] = N번째 울타리에서 사자를 배치하지 않았을 경우의 모든 경우의 수*/
    /*dp[N][1] = N번째 울타리에서 왼쪽에 사자를 배치했을 때의 모든 경우의 수*/
    /*dp[N][2] = N번째 울타리에서 오른쪽으로 사자를 배치했을 때의 모든 경우의 수*/
    int dp[N + 1][3];
    dp[0][0] = 1;
    dp[0][1] = 1;
    dp[0][2] = 1;
    for(int i = 1; i <= N; i++) {
        dp[i][0] = ((dp[i-1][0] + dp[i-1][1]) % MOD + dp[i-1][2]) % MOD;
        dp[i][1] = (dp[i-1][2] + dp[i-1][0]) % MOD;
        dp[i][2] = (dp[i-1][1] + dp[i-1][0]) % MOD;
    }
    cout << dp[N][0] << endl;
    return 0;
}
