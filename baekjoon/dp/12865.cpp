#include <iostream>
#include <vector>
#include <algorithm>
#define W first 
#define K second

using namespace std;
int N, K;
vector<pair<int, int>> object;

/* dp[물건_idx][무게][물건_idx를 사용한 경우와 하지 않은 경우] = 물건_idx번째를 이용해서 주어진 무게만큼의 최대값 */
int dp[101][100001][2];

void make_dp() {
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= K; j++) {
			int curr_w = object[i].W;
			int curr_k = object[i].K;
			//i번째 물건을 사용하지 않은 경우
			dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]);
			//i번째 물건을 사용한 경우
			if (j - curr_w >= 0)
				dp[i][j][1] = dp[i][j-curr_w][0] + curr_k;
		}
	}
}

int main(void) 
{
	cin >> N >> K;
	object.push_back(make_pair(0, 0));
	for (int i = 0; i < N; i++) {
		int w, v;
		cin >> w >> v;
		object.push_back(make_pair(w, v));
	}
	make_dp();
	cout << max(dp[N][K][0], dp[N][K][1]) << endl;
}
