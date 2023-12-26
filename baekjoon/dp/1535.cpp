#include <vector>
#include <iostream>
#include <algorithm>
#define INF 987654321
using namespace std;

int N;
vector<int> hps, happys;
int dp[21][101];

int make_dp(int human_idx, int hp) {
	if (hp <= 0)
		return -INF;
	if (human_idx < 0)
		return 0;
	int &ret = dp[human_idx][hp];
	if (ret != -INF)
		return ret;
	ret = max(make_dp(human_idx - 1, hp), make_dp(human_idx - 1, hp - hps[human_idx]) + happys[human_idx]);
	return ret;
}

int main(void) {
	cin >> N;
	for (int j = 0; j < N; j++) {
		int num;
		cin >> num;
		hps.push_back(num);
	}
	for (int j = 0; j < N; j++) {
		int num;
		cin >> num;
		happys.push_back(num);
	}
	fill(&dp[0][0], &dp[20][101], -INF);
	cout << make_dp(N - 1, 100) << endl;
	return 0;
}
