#include <iostream>
#include <vector>
#include <algorithm>
#define C first
#define P second

using namespace std;

int n;
double m;

void make_dp(vector<vector<int>> &dp, vector<pair<int, int>> &candys) {
	for (int candy_idx = 1; candy_idx <= n; candy_idx++) {
		for (int budget = 0; budget <= m; budget++) {
			dp[candy_idx][budget] = dp[candy_idx - 1][budget];
			if (budget >= candys[candy_idx].P)
				dp[candy_idx][budget] = max(dp[candy_idx][budget] = dp[candy_idx - 1][budget], dp[candy_idx][budget - candys[candy_idx].P] + candys[candy_idx].C);
		}
	}
}

int main(void) 
{
	cin >> n >> m;
	m *= 100;
	while (n != 0 && m != 0) {
		vector<pair<int, int>> candys;
		candys.push_back({0, 0});
		vector<vector<int>> dp(n + 1, vector<int>((int)m + 1, 0));
		for (int i = 0; i < n; i++) {
			int calorie;
			double price;
			cin >> calorie >> price;
			candys.push_back({calorie, (int)(price * 100 + 0.5)});
		}
		make_dp(dp, candys);
		cout << dp[n][m] << endl;
		cin >> n >> m;
		m *= 100;
	}
}
