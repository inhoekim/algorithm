#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int T,W;
vector<int> trees;
int dp[1001][31][2];

int make_dp(int time, int w, int tree_idx) {
	if (time == 0) return 0;
	int &ret = dp[time][w][tree_idx];
	if (ret != -1)
		return (ret);
	int next_tree_idx = (tree_idx + 1) % 2;
	int can_eat = 0;
	if(trees[time - 1] == tree_idx)
		can_eat = 1;
	ret = max(ret, make_dp(time - 1, w, tree_idx) + can_eat);
	if (w > 0)
		ret = max(ret, make_dp(time - 1, w - 1, next_tree_idx) + can_eat);
	return ret;
}

int main(void) {
	cin >> T >> W;
	for (int i = 0; i < T; i++) {
		int n;
		cin >> n;
		trees.push_back(n - 1);
	}
	reverse(trees.begin(), trees.end());
	trees.push_back(-1);
	fill(&dp[0][0][0], &dp[1000][30][2], -1);
	cout << make_dp(T + 1, W, 0) << endl;
}
