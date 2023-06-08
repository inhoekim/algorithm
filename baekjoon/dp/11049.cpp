#include <iostream>
#include <algorithm>
#include <limits.h>
#define col first
#define row second

using namespace std;

long long dp[500][500];
pair<int, int> matrix[500];
int n;

long long recur(int left, int right) {
	if (abs(left - right) == 1)
		dp[left][right] = matrix[left].row * matrix[left].col * matrix[right].row;
	if (left == right || dp[left][right] != LONG_MAX)
		return (dp[left][right]);
	for (int k = left; k < right; k++) {
		long long merge_cnt = matrix[left].col * matrix[k].row * matrix[right].row;;
		if (left == k)
			merge_cnt = matrix[left].col * matrix[k + 1].col * matrix[right].row;
		if (right == k + 1)
			merge_cnt = matrix[left].col * matrix[k].row * matrix[right].row;
		dp[left][right] = min(recur(left, k) + recur(k + 1, right) + merge_cnt, dp[left][right]);
	}
	return (dp[left][right]);
}

int main(void) {
	cin >> n;
	fill(&dp[0][0], &dp[499][500], LONG_MAX);
	for (int i = 0; i < n; i++) {
		int row, col;
		cin >> row >> col;
		matrix[i] = {row, col};
		dp[i][i] = 0;
	}
	cout << recur(0, n - 1);
}
