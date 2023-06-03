#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int n, max_bit;
bool visited[1000001];
queue<long long> que;
queue<long long> next_que;

//땅따먹기 시작
int bfs() {
	int turn = -1;
	while (!que.empty()) {
		//다음턴을 시작
		turn++;
		while (!que.empty()) {
			long long curr = que.front();
			que.pop();
			//다음 방문 정점을 탐색 (bit 개수가 1개 차이가 나면 서로 간선이 연결되어있다고 봄)
			for (int i = 0; i < max_bit; i++) {
				long long next_curr = curr ^ (1 << i);
				if (next_curr > n || visited[next_curr])
					continue;
				next_que.push(next_curr);
				visited[next_curr] = true;
			}
		}
		while (!next_que.empty()) {
			que.push(next_que.front());
			next_que.pop();
		}
	}
	return (turn);
}

int get_max_bit(int n) {
	int bit_cnt = 0;
	while (n != 0) {
		bit_cnt++;
		n /= 2;
	}
	return (bit_cnt);
}

int main(void) {
	int m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int num;
		cin >> num;
		visited[num] = true;
		que.push(num);
	}
	//n의 bit개수를 계산
	max_bit = get_max_bit(n);
	int ret = bfs();
	cout << ret << endl;
}
