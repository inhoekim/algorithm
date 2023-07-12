#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define Y first
#define X second
#define NOT_VISITED -1
#define WALL 1
#define MAX 987654321

using namespace std;

int n, m;
int map[50][50];
int dist[50][50];
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int ret = MAX;
vector<pair<int, int>> possible;
deque<pair<int, int>> virus;

int check_virus() {
	int max_dist = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((map[i][j] == 0 || map[i][j] == 2) && dist[i][j] == NOT_VISITED)
				return (MAX);
			max_dist = max(max_dist, dist[i][j]);
		}
	}
	return (max_dist);
}

int bfs() {
	fill(&dist[0][0], &dist[49][50], NOT_VISITED);
	queue<pair<int, int>> que;
	for(int i = 0; i < virus.size(); i++) {
		dist[virus[i].Y][virus[i].X] = 0;
		que.push(virus[i]);
	}
	while (!que.empty()) {
		pair<int, int> curr = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int ny = curr.Y + dirs[i][0];
			int nx = curr.X + dirs[i][1];
			if (ny < 0 || ny == n || nx < 0 || nx == n
			|| dist[ny][nx] != NOT_VISITED || map[ny][nx] == WALL)
				continue;
			dist[ny][nx] = dist[curr.Y][curr.X] + 1;
			que.push({ny, nx});
		}
	}
	return (check_virus());
}

void place_virus(int cnt, int idx) {
	if (virus.size() == m) {
		ret = min(ret, bfs());
		return ;
	}
	for (int i = idx; i < possible.size(); i++) {
		virus.push_back(possible[i]);
		place_virus(cnt + 1, i + 1);
		virus.pop_back();
	}
}

int main(void) {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2)
				possible.push_back({i, j});
		}
	place_virus(0, 0);
	if (ret == MAX)
		ret = -1;
	cout << ret << endl;
}
