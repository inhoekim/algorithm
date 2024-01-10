#include <iostream>
#include <vector>

using namespace std;

string A, B;
vector<vector<int>> dp;

// dp[a_idx][b_idx] = 문자열 a와 b를 각각 a_idx와 b_idx부터 읽을때 만들 수 있는 LCS 값을 메모이제이션
// dp[a_idx][b_idx] = if (a_idx와 b_idx의 문자가 같다면) dp[a_idx + 1][b_idx + 1] + 1
//                       else max(dp[a_idx + 1][b_idx], dp[a_idx][b_idx + 1])
int make_dp(int a_idx, int b_idx) {
    if (a_idx == A.length() || b_idx == B.length())
        return 0;
    int &ret = dp[a_idx][b_idx];
    if (ret != -1)
        return ret;
    if (A[a_idx] == B[b_idx])
        ret = make_dp(a_idx + 1, b_idx + 1) + 1;
    else
        ret = max(make_dp(a_idx, b_idx + 1), make_dp(a_idx + 1, b_idx));
    return ret;
}

int main(void)
{
    cin >> A >> B;
    dp = vector<vector<int>>(A.length(), vector<int>(B.length(), -1));
    int ret = make_dp(0, 0);
    cout <<  ret << endl;
    int a_idx = 0;
    int b_idx = 0;
    while (b_idx < B.size() && a_idx < A.size() && dp[a_idx][b_idx] > 0) {
        if (dp[a_idx][b_idx] != dp[a_idx][b_idx + 1]) {
            cout << B[b_idx];
            while (A[a_idx] != B[b_idx])
                a_idx++;
            a_idx++;
            b_idx++;
        } else
            b_idx++;
    }
    if (ret != 0)
        cout << endl;
    return 0;
}
