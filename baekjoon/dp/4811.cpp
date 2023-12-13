#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*  
    dp[선택한_알약_종류(idx)][1개짜리 알약갯수(a)][0.5개짜리 알약갯수(b)]

    (dp정의)
    현재 종수가 선택한 알약의 종류가 idx이고, 현재 약통에 존재하는 1개짜리 알약갯수가 a, 0.5개짜리 알약갯수가 b일떄
    나올 수 있는 경우의 수

    (점화식)
    dp[idx][a][b] = dp[(idx + 1) % 2][a-1][b+1] + dp[(idx + 1) % 2][a][b-1]
*/
long long dp[2][31][31];

long long make_dp(int idx, int one_cnt, int half_cnt) {
    long long &ret = dp[idx][one_cnt][half_cnt];
	long long a = 0;
	long long b = 0;
	int next_idx = (idx + 1) % 2;
	if (one_cnt > 0) {
		a = dp[next_idx][one_cnt - 1][half_cnt + 1];
		if (a == -1)
			a = make_dp(next_idx, one_cnt - 1, half_cnt + 1);
	}
    if (half_cnt > 0) {
		b = dp[next_idx][one_cnt][half_cnt - 1];
		if (b == -1)
			b = make_dp(next_idx, one_cnt, half_cnt - 1);
	}
	ret = a + b;
    return ret;
}

int main(void) {
	int N;
	cin >> N;
	while (N != 0) {
		fill(&dp[0][0][0], &dp[1][30][31], -1);
		dp[0][0][0] = 1;
		cout << make_dp(0, N ,0) << endl;
		cin >> N;
	}
}
