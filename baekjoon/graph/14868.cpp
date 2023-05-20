#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int r, c;
char **map;
bool **bfs_visited;
bool **dfs_visited;
queue<pair<int, int>> que;
queue<pair<int, int>> next_dfs;
queue<pair<int, int>> temp_next_dfs;
int dirs[4][2] = {{-1, 0},{1, 0},{0, -1},{0, 1}};
pair<int, int> l1, l2;
int day;

// l1백조를 기준으로 l2 백조를 발견할때까지 dfs를 진행한다
void dfs(pair<int, int> curr){
	dfs_visited[curr.first][curr.second] = true;
	//만약 다른 백조를 발견하면 결과를 출력하고 프로그램 종료
	if (map[curr.first][curr.second] == 'L') {
		cout << day << endl;
		exit(0);
	}
	for (int i = 0; i < 4; i++) {
		int next_y = curr.first + dirs[i][0];
		int next_x = curr.second + dirs[i][1];
		if (next_x < 0 || next_x == c || next_y < 0 || next_y == r
		|| dfs_visited[next_y][next_x])
			continue;
		if (map[next_y][next_x] == 'X') {
			temp_next_dfs.push({next_y, next_x});
			continue;
		}
		dfs({next_y, next_x});
	}
}

void bfs(){
	dfs(l1);
	queue<pair<int, int>> next_que;
	do {
		//하루가 지나고 새로운 턴 시작
		while (!next_que.empty()) { //먼저 전날 녹은 빙하들을 꺼내와 해당 점부터 bfs탐색을 이어서 시작함
			que.push(next_que.front());
			next_que.pop();
		}
		//하루가 지남을 카운트
		day++;
		//빙하를 녹이는 작업시작
		while (!que.empty()) {
			int curr_y = que.front().first;
			int curr_x = que.front().second;
			que.pop();
			for (int i = 0; i < 4; i++) {
				int next_y = curr_y + dirs[i][0];
				int next_x = curr_x + dirs[i][1];
				if (next_x < 0 || next_x == c || next_y < 0 || next_y == r
					|| bfs_visited[next_y][next_x])
					continue;
				//녹은 빙하는 next_que에 저장해서 다음턴에 다시 bfs탐색을 이어간다
				if (map[next_y][next_x] == 'X') {
					map[next_y][next_x] = '.';
					bfs_visited[next_y][next_x] = true;
					next_que.push({next_y, next_x});
				}
			}
		}
		//빙하를 녹인 후 다음턴을 시작하기전에 l2 백조가 발견되었는지 dfs를 통해 확인
		while (!temp_next_dfs.empty()) {
			next_dfs.push(temp_next_dfs.front());
			temp_next_dfs.pop();
		}
		while (!next_dfs.empty()) {
			pair<int, int> new_water = next_dfs.front();
			next_dfs.pop();
			if (!dfs_visited[new_water.first][new_water.second])
				dfs({new_water.first, new_water.second});
		}
	}while(!next_que.empty());
}

int main(void) {
	//입력 파트
	cin >> r >> c;
	map = new char*[r];
	bfs_visited = new bool*[r];
	dfs_visited = new bool*[r];
	for (int i = 0; i < r; i++) {
		map[i] = new char[c];
		bfs_visited[i] = new bool[c];
		dfs_visited[i] = new bool[c];
	}
	fill(&bfs_visited[0][0], &bfs_visited[r - 1][c], false);
	fill(&dfs_visited[0][0], &dfs_visited[r - 1][c], false);
	bool is_first = false;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'L') {
				if (!is_first) {
					is_first = true;
					l1 = {i, j};
					map[i][j] = '.';
				}
				else
					l2 = {i, j};
			}
			if (map[i][j] != 'X') {
				que.push({i, j});
				bfs_visited[i][j] = true;
			}
		}
	}
	//탐색 파트
	bfs();
}
