#include <algorithm>
#include <queue>
#include <unordered_map>
#include <utility>
#include <iostream>

using namespace std;

int directions[3] = {0, -1, 1};
unordered_map<int, pair<int, int>> visited;

//재귀적으로 현재 node의 이전 node를 찾아가서 출력한다. 마지막 출력의 공백을 처리하기 위해서 매개변수에 최초 함수를 호출한 first node를 같이 넘겨줌.
void print_path(int node, int first) {
	int before_node = visited.find(node)->second.first;
	if (before_node == -1) {
		cout << node << " ";
		return ;
	}
	print_path(before_node, first);
	//print_path함수를 최초로 호출한 node였다면 공백 없이 출력
	if (node == first)
		cout << first;
	else
		cout << node << " ";
}

void bfs(int start, int end) {
	visited.insert(make_pair(start, make_pair(-1, 0))); //key : 현재노드, val = (이전노드, 걸린 시간)
	queue<int> que;
	que.push(start);
	while (!que.empty()) {
		int curr = que.front();
		if (curr == end) {
			cout << visited.find(curr)->second.second << endl;
			print_path(curr, curr);
			cout << endl;
			return ;
		}
		que.pop();
		directions[0] = curr;
		for (int i = 0; i < 3; i++) {
			int next = curr + directions[i];
			if (next < 0 || next > 100000 || visited.find(next) != visited.end())
				continue ;
			int time = visited.find(curr)->second.second;
			visited.insert(make_pair(next, make_pair(curr, time + 1)));
			que.push(next);
		}
	}
}

int main(void){
	//입출력 part
	int n, k;
	cin >> n >> k;
	bfs(n, k);
}
