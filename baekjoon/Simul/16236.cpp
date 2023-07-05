#include <iostream>
#include <queue>
#include <utility>
#define Y first
#define X second

using namespace std;

int map[20][20];
int dist[20][20];
int dirs[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int n, ret, temp_ret;
int s_size = 2;
pair<int, int> start;

void bfs() {
	fill(&dist[0][0], &dist[19][20], -1);
	map[start.Y][start.X] = 0;
	dist[start.Y][start.X] = 0;
	queue<pair<int, int>> que;
	que.push({start.Y, start.X});
	while (!que.empty()) {
		pair<int, int> curr = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int ny = curr.Y + dirs[i][0];
			int nx = curr.X + dirs[i][1];
			if (ny < 0 || ny == n || nx < 0 || nx == n
			|| dist[ny][nx] != -1 || map[ny][nx] > s_size)
				continue;
			if (map[ny][nx] != 0 && map[ny][nx] < s_size && temp_ret == 0)
				temp_ret = dist[curr.Y][curr.X] + 1;
			dist[ny][nx] = dist[curr.Y][curr.X] + 1;
			que.push({ny, nx});
		}
	}
}

void set_next_start(int target) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (dist[i][j] == target && map[i][j] < s_size && map[i][j] != 0) {
				start = {i, j};
				return ;
			}
		}
}

int	main(void) {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9)
				start = {i, j};
		}

	int eat_cnt = 0;
	while (true) {
		bfs();
		ret += temp_ret;
		if (temp_ret != 0) {
			set_next_start(temp_ret);
			temp_ret = 0;
		}
		else
			break;
		eat_cnt++;
		if (eat_cnt == s_size) {
			eat_cnt = 0;
			s_size++;
		}
	}
	cout << ret << endl;
	return (0);
}
