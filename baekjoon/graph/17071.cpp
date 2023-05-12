#include <iostream>
#include <queue>
#include <utility>
#include <string.h>
#define MAX 987654321

using namespace std;

int dp[1000];
int n, k;
int dirs[3] = {0, -1, 1};
int visited[2][500001];

int recur_get_seq(int num) {
	if (dp[num] != -1)
		return (dp[num]);
	dp[num] = recur_get_seq(num - 1) + num;
	return (dp[num]);
}

void bfs(){
	queue<pair<int, int>> que;
	que.push(make_pair(n, 0));
	visited[0][n] = 0;
	int location_k;
	while (!que.empty()) {
		pair<int, int> curr = que.front();
		que.pop();
		location_k = recur_get_seq(curr.second) + k;
		//만약 동생의 위치가 예외조건을 넘긴다면 버린다
		if (location_k > 500000)
			continue ;
		//동생의 위치와 수빈이의 위치가 같아졌을 때 리턴
		if (location_k == curr.first)
			return ;
		dirs[0] = curr.first;
		for(int i = 0; i < 3; i++) {
			int next = curr.first + dirs[i];
			int next_time = curr.second + 1;
			if (next < 0 || next > 500000 || visited[next_time % 2][next] != -1)
				continue ;
			//짝수시간대, 홀수시간대로 나눠 각각 가장 빨리 도착된 시간을 기록
			visited[next_time % 2][next] = next_time;
			que.push(make_pair(next, next_time));
		}
	}
}

int main(void) {
	//입출력 part
	cin >> n >> k;
	memset(visited, -1, sizeof(visited));
	memset(dp, -1, sizeof(dp));
	dp[0] = 0; dp[1] = 1;
	int ret = MAX;
	bfs();
	//동생이 오기전에 수빈이가 해당 좌표에 먼저 도착한 경우, 움직이지않고 동생이 올때까지 2초동안 대기하는게 가능함
	//따라서 짝수시간대, 홀수시간대로 나눠 각각 2초씩 기달려봤을 때 최소값 경우에 계산
	for (int i = 0; i < 1000; i++) {
		int location_k = k + recur_get_seq(i);
		if (location_k <= 500000 && (visited[0][location_k] != -1 || visited[1][location_k] != -1)) {
			for (int j = 0; j < 2; j++) {
				if (visited[j][location_k] == -1)
					continue ;
				int time_diff = i - visited[j][location_k];
				//동생이 해당 좌표에서 먼저 방문해서 지나간 경우는 continue
				if (time_diff < 0)
					continue ;
				//2초씩 대기하면서 동생이 올때까지 기다릴 수 있는 경우 i를 return, 기다려도 동생이 올 수 없다면 continue
				if (visited[j][location_k] % 2 != i % 2)
					continue ;
				ret = min(i, ret);
			}
		}
	}
	if (ret == MAX)
		ret = -1;
	cout << ret << endl;
}
