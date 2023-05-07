#include <algorithm>
#include <queue>
#include <unordered_map>
#include <utility>
#include <iostream>

using namespace std;

int directions[3] = {0, -1, 1};

void bfs(int start, int end) {
	unordered_map<int, int> visited;
	visited.insert(make_pair(start, 0));
	queue<int> que;
	que.push(start);
	while (!que.empty()) {
		int curr = que.front();
		if (curr == end) {
			cout << visited.find(curr)->second << endl;
			return ;
		}
		que.pop();
		directions[0] = curr;
		for (int i = 0; i < 3; i++) {
			int next = curr + directions[i];
			if (next < 0 || next > 100000 || visited.find(next) != visited.end())
				continue ;
			int time = visited.find(curr)->second;
			//순간이동시 0초 (항상 순간이동이 먼저 큐에 삽입되기 때문에 최단시간이 출력됨)
			if (i == 0)
				visited.insert(make_pair(next, time));
			//걸어가면 1초
			else
				visited.insert(make_pair(next, time + 1));
			que.push(next);
		}
	}
}

int main(void){
	int n, k;
	cin >> n >> k;
	//입출력 part
	bfs(n, k);
}
