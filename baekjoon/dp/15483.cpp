#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
	string a,b;
	cin >> a >> b;
	int len_a = a.length() + 1;
	int len_b = b.length() + 1;
	int **dp = new int*[len_a];
	for (int i = 0; i < len_a; i++)
		dp[i] = new int[len_b];
	for (int i = 0; i < len_a; i++)
		dp[i][0] = i;
	for (int i = 0; i < len_b; i++)
		dp[0][i] = i;

	for (int i = 1; i < len_a; i++)
		for (int j = 1; j < len_b; j++) {
			int c = 1;
			if (a.at(i - 1) == b.at(j - 1))
				c = 0;
			dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
			dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + c);
		}
	cout << dp[len_a - 1][len_b - 1] << endl;
}
