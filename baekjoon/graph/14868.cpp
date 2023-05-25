#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
int ret;
queue<pair<int, int>> curr_que;
queue<pair<int, int>> dfs_que;
queue<pair<int, int>> dfs_next_que;
vector<bool> finded_civil;
bool **dfs_visited;
bool **bfs_visited;
int **map;
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //상하좌우 순

void print_map() {
	for (int i = 0; i < n ; i++) {
		for (int j = 0; j < n; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "---------------------------" << endl;
}

bool check_find_civil() {
	for (int i = 0; i < finded_civil.size(); i++)
		if (!finded_civil[i])
			return false;
	return true;
}

void dfs(int curr_y, int curr_x, int area_idx, bool is_split_proc) {
	dfs_visited[curr_y][curr_x] = true;
	//만약 split_area함수에서 영역을 나누는 과정의 초기 dfs탐색이라면 실행
	if (is_split_proc)
		map[curr_y][curr_x] = area_idx;
	for (int i = 0; i < 4; i++) {
		int next_y = curr_y + dirs[i][0];
		int next_x = curr_x + dirs[i][1];
		if (next_y < 0 || next_y == n || next_x < 0 || next_x == n
			|| dfs_visited[next_y][next_x] || (map[next_y][next_x] == 0 && is_split_proc))
			continue;
		//문명지역이 병합되는 과정을 캐치한다.
		if (!is_split_proc) {
			if (map[next_y][next_x] == 0) {
				dfs_next_que.push({next_y, next_x});
				continue;
			}
			int civil_area_idx = map[next_y][next_x];
			//dfs탐색 기준 문명지역이 아닌 새로운 문명지역을 처음으로 발견한 경우 (civil_area_idx가 1인 곳은 기준점이 된 문명이다)
			if (!finded_civil[civil_area_idx - 1]) {
				finded_civil[civil_area_idx - 1] = true;
				//새로운 문명이 병합되었으니 모든 문명이 병합되었는지 체크해본다
				if (check_find_civil()) {
					cout << ret << endl;
					exit(0);
				}
			}
		}
		dfs(next_y, next_x, area_idx, is_split_proc);
	}
}

void bfs() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dfs_visited[i][j] = false;
	queue<pair<int, int>> next_que;

	do {
		//dfs탐색시작
		while (!dfs_que.empty()) {
			pair<int, int> coord = dfs_que.front();
			dfs_que.pop();
			if (!dfs_visited[coord.first][coord.second])
				dfs(coord.first, coord.second, -1, false);
		}
		//다음해가 시작되고 dfs를 돌릴 지점을 큐에 다시 담는다
		while (!dfs_next_que.empty()) {
			dfs_que.push(dfs_next_que.front());
			dfs_next_que.pop();
		}
		//다음 해를 시작하기전에 큐에 방문한 정점들을 담는다
		while (!next_que.empty()) {
			curr_que.push(next_que.front());
			next_que.pop();
		}
		//bfs탐색시작
		while (!curr_que.empty()) {
			pair<int, int> curr = curr_que.front();
			curr_que.pop();
			for (int i = 0; i < 4; i++) {
				int next_y = curr.first + dirs[i][0];
				int next_x = curr.second + dirs[i][1];
				if (next_y < 0 || next_y == n || next_x < 0 || next_x == n
					|| bfs_visited[next_y][next_x] || map[next_y][next_x] != 0)
					continue;
				map[next_y][next_x] = map[curr.first][curr.second];
				bfs_visited[next_y][next_x] = true;
				next_que.push({next_y, next_x});
			}
		}
		//한 해가 지남
		ret++;
	} while(!next_que.empty());
}

void split_area() {
	int idx = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!dfs_visited[i][j] && map[i][j] == 1) {
				if (idx == 1) {
					//기준섬이 될 1번째 인덱스의 섬의 방문여부는 true로 시작
					finded_civil.push_back(true);
					dfs_que.push({i, j});
				}
				if (idx != 1) //area_idx가 2인 지역부터 finded_civil에 false 값으로 쌓이게 됨
					finded_civil.push_back(false);
				dfs(i, j, idx, true);
				idx++;
			}
		}
	}
}

int main(void) {
	cin >> n >> k;
	map = new int*[n];
	dfs_visited = new bool*[n];
	bfs_visited = new bool*[n];
	for (int i = 0; i < n; i++) {
		map[i] = new int[n];
		dfs_visited[i] = new bool[n];
		bfs_visited[i] = new bool[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = 0;
			dfs_visited[i][j] = false;
			bfs_visited[i][j] = false;
		}
	}
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		x = x - 1;
		y = n - y;
		map[y][x] = 1;
		curr_que.push({y, x});
		bfs_visited[y][x] = true;
	}
	split_area();
	if (check_find_civil()) {
		cout << ret << endl;
		return (0);
	}
	bfs();
}
