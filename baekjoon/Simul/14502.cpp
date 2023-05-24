#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> empty_room;
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n, m;
int map[8][8];
bool visited[8][8];
int wall[3];
int temp_ret;
bool is_safe;
int answer;

int check_safe_area(int curr_y, int curr_x){
	int ret = 1;
	visited[curr_y][curr_x] = true;
	for (int i = 0; i < 4; i++) {
		int next_y = curr_y + dirs[i][0];
		int next_x = curr_x + dirs[i][1];
		if (next_y < 0 || next_y == n || next_x < 0 || next_x == m
		|| visited[next_y][next_x] || map[next_y][next_x] == 1)
			continue;
		if (map[next_y][next_x] == 2) {
			is_safe = false;
			continue;
		}
		ret += check_safe_area(next_y, next_x);
	}
	return (ret);
}

void init_dfs() {
	fill(&visited[0][0], &visited[7][8], false);
	temp_ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] == false && map[i][j] == 0) {
				is_safe = true;
				int ret = check_safe_area(i, j);
				if (is_safe)
					temp_ret += ret;
			}
		}
	}
	answer = max(answer, temp_ret);
}

void pick_wall(int picked_cnt, int idx) {
	if (picked_cnt == 3) {
		//뽑은 벽을 맵에 세운다
		for(int i = 0; i < 3; i++) {
			map[empty_room[wall[i]].first][empty_room[wall[i]].second] = 1;
		}
		//dfs로 모든 좌표를 탐색하면서 안전영역 개수를 cnt한다
		init_dfs();
		//벽을 다시 철거한다
		for(int i = 0; i < 3; i++)
			map[empty_room[wall[i]].first][empty_room[wall[i]].second] = 0;
		return;
	}
	//조합으로 벽을 뽑아 wall 배열에 담음
	for (int i = idx; i < empty_room.size(); i++) {
		wall[picked_cnt] = i;
		pick_wall(picked_cnt + 1, i + 1);
	}
}

int main(void) {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)
				empty_room.push_back({i , j});
		}
	}
	pick_wall(0, 0);
	cout << answer << endl;
}
