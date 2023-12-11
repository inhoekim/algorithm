#include <iostream>
#include <vector>
#include <algorithm>
#define NOWAY 0
#define INF 987654321

using namespace std;

int N;
vector<vector<int>> adjacency_matrix;
vector<vector<int>> dp;

/* dp[here][visited] == visited 노드들을 방문한 상태로 here에 왔을때의 최소값 */
int make_dp(int here, int visited) {
    if (visited == (1 << N) - 1) {
		if (adjacency_matrix[here][0] == NOWAY)
			return INF;
        return adjacency_matrix[here][0];
	}
	int &ret = dp[here][visited];
	if (ret != -1) return ret;
	ret = INF;
    for (int next_node = 1; next_node < N; next_node++) {
        if (visited & (1 << next_node) || adjacency_matrix[here][next_node] == NOWAY) continue;
		int next_visited = visited | (1 << next_node);
        ret = min(ret, make_dp(next_node, next_visited) + adjacency_matrix[here][next_node]);
    }
	return (ret);
}

int main(void) {
    cin >> N;
    adjacency_matrix = vector<vector<int>>(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> adjacency_matrix[i][j];
    dp = vector<vector<int>>(N, vector<int>((1 << N) - 1, -1));
    make_dp(0, 1);
    cout << dp[0][1] << endl;
    return 0;
}
