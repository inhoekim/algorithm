1#include <iostream>
#include <vector>
#define MOD 1000007

using namespace std;

int N, M, C;
vector<vector<int>> map;
vector<vector<vector<vector<long long>>>> dp;

/*
	dp[y][x][지나온_오락실갯수(cnt)][갈수있는_오락실_idx_범위] -> 지나온 오락실의 갯수가 cnt, 갈수있는_오락실_idx_범위인 상태로 (y,x)좌표에 방문하는 경우의 수를 메모이제이션
	dp[y][x][지나온_오락실갯수(cnt)][갈수있는_오락실_idx_범위] = dp[y-1][x][지나온_오락실갯수] + dp[y][x-1][지나온_오락실갯수] (y,x가 오락실이 아닌경우)
	dp[y][x][지나온_오락실갯수(cnt)][갈수있는_오락실_idx_범위] = dp[y-1][x][지나온_오락실갯수 - 1] + dp[y][x-1][지나온_오락실갯수 - 1] (y,x가 오락실인 경우)
*/
long long make_dp(int y, int x, int cnt, int idx) {
	if (y < 0 || x < 0 || cnt < 0)
		return 0;
	long long &ret = dp[y][x][cnt][idx];
	if (ret != -1)
		return ret;
	// 현재 좌표가 오락실인 경우
	if (map[y][x]) {
		//오락실을 오름차순으로 방문할 수 있는 경우
		if (map[y][x] <= idx)
			ret = (make_dp(y-1,x, cnt-1, map[y][x]) + make_dp(y,x-1,cnt-1, map[y][x])) % MOD;
		//오락실을 오름차순으로 방문할 수 없는 경우
		else
			return ret = 0;
	}
	// 현재 좌표가 오락실이 아닌 경우
	else
		ret = (make_dp(y-1, x, cnt, idx) + make_dp(y, x-1, cnt, idx)) % MOD;
	return ret %= MOD;
}

int main(void) {
	cin >> N >> M >> C;
	dp = vector<vector<vector<vector<long long>>>>(N, vector<vector<vector<long long>>>(M, vector<vector<long long>>(C + 1, vector<long long>(C + 1, -1))));
	map = vector<vector<int>>(N, vector<int>(M, 0));
	for (int i = 0; i < C; i++) {
		int y, x;
		cin >> y >> x;
		map[y-1][x-1] = i + 1;
	}
	if (map[0][0])
		for (int i = map[0][0]; i < C + 1; i++)
			dp[0][0][1][i] = 1;
	else
		for (int i = 0; i < C + 1; i++)
			dp[0][0][0][i] = 1;
	int last_idx = map[N-1][M-1];
	if (last_idx == 0)
		last_idx = C;
	for (int i = 0; i <= C; i++ ) {
		if (i != C)
			cout << make_dp(N-1, M-1, i, last_idx) << " ";
		else
			cout << make_dp(N-1, M-1, i, last_idx) << endl;
	}
	return 0;
}
