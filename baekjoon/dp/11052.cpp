#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[1002];

void make_dp(int end_idx) {
    for (int i = 1; i <= end_idx; i++) {
        int mid = i / 2;
        for (int j = i - 1; j >= mid; j--) {
            dp[i] = max(dp[i], dp[j] + dp[i - j]);
        }
    }
}

int main(void) {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int value;
        cin >> value;
        dp[i] = value;
    }
    dp[0] = -1;
    make_dp(N);
    cout << dp[N] << endl;
}
