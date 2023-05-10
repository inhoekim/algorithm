#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>
#include <queue>
#define LIGHT 1

using namespace std;

int n, m;
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int ret;
int map[101][101];
bool visited[101][101];
unordered_set<int> dark_rooms;
vector<vector<int>> switch_lst;

pair<int, int> make_coord(int idx) {
	int y = idx / n;
	int x = idx % n;
	return (make_pair(y, x));
}

int make_idx(int y, int x) {
	return ((y * n) + x);
}

void on_switch(pair<int, int> curr, queue<pair<int,int>> &que) {
	for (int idx : switch_lst[make_idx(curr.first, curr.second)]) {
		pair<int, int> room = make_coord(idx);
		if(map[room.first][room.second] != LIGHT) {
			map[room.first][room.second] = LIGHT;
			ret++;
			//만약 이전에 어두워서 방문하지 못했던 방이 존재했다면 불이 켜졌으니 방문 queue에 삽입시킴
			if (!visited[room.first][room.second]
				&& dark_rooms.find(idx) != dark_rooms.end())
			{
				visited[room.first][room.second] = true;
				que.push(room);
			}
		}
	}
}

void bfs(){
	queue<pair<int,int>> que;
	que.push(make_pair(0, 0));
	while (!que.empty()) {
		pair<int, int> curr = que.front();
		que.pop();
		on_switch(curr, que);
		for (int dir = 0; dir < 4; dir++) {
			int next_y = curr.first + dirs[dir][0];
			int next_x = curr.second + dirs[dir][1];
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == n
				|| visited[next_y][next_x])
				continue ;
			//불이 꺼져있어서 방문하지 못할 경우 방문대기 목록에 넣고 continue
			if (map[next_y][next_x] != LIGHT) {
				dark_rooms.insert(make_idx(next_y, next_x));
				continue ;
			}
			//방문할 수 있을경우 방문
			visited[next_y][next_x] = true;
			que.push(make_pair(next_y, next_x));
		}
	}
}

int main(void) {
	//입출력 part
	cin >> n >> m;
	switch_lst = vector<vector<int>>(n * n);
	for (int i = 0; i < m; i++) {
		int y, x, a, b;
		cin >> y >> x >> a >> b;
		switch_lst[make_idx(y - 1, x - 1)].push_back(make_idx(a - 1, b - 1));
	}
	map[0][0] = LIGHT;
	visited[0][0] = true;
	ret = 1;
	bfs();
	cout << ret << endl;
}
