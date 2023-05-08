#include <algorithm>
#include <queue>
#include <iostream>
#define MAX 987654321
#define MORNING 0
#define WALL 1
using namespace std;

int ****dist;
int **map;
int n, m, k;
int ret = MAX;
const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int ok[2][1][6][4];

class coord {
	public:
		int y, x, remain, day;
		coord(int _remain, int _y, int _x, int _day) {
			y = _y;
			x = _x;
			remain = _remain;
			day = _day;
		}
};

void bfs() {
	queue<coord> que;
	que.push(coord(k, 0, 0, 0));
	dist[MORNING][k][0][0] = 1;
	while (!que.empty()) {
		coord curr = que.front();
		que.pop();
		//움직이지 않고 하루밤 대기하는 경우
		if (dist[(curr.day + 1) % 2][curr.remain][curr.y][curr.x] > dist[curr.day][curr.remain][curr.y][curr.x] + 1) {
			dist[(curr.day + 1) % 2][curr.remain][curr.y][curr.x] =  dist[curr.day][curr.remain][curr.y][curr.x] + 1;
			que.push(coord(curr.remain, curr.y, curr.x, (curr.day + 1) % 2));
		}
		for (int i = 0; i < 4; i++) {
			int next_y = curr.y + dirs[i][0];
			int next_x = curr.x + dirs[i][1];
			int next_day = (curr.day + 1) % 2;
			int next_dist = dist[curr.day][curr.remain][curr.y][curr.x] + 1;
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == m
				|| dist[next_day][curr.remain][next_y][next_x] != MAX)
				continue ;
			//벽을 부술 수 있는 상황에서 벽을 만났을 때
			if (map[next_y][next_x] == WALL && curr.remain != 0) {
				//벽을 부술 힘이 있어도 이미 다른 루트에서 벽을 부수고 방문된 노드면 스킵
				if (dist[next_day][curr.remain - 1][next_y][next_x] != MAX)
					continue;
				//낮일때만 벽을 부술 수 있다
				if (curr.day == MORNING) {
					dist[next_day][curr.remain - 1][next_y][next_x] = next_dist;
					que.push(coord(curr.remain - 1, next_y, next_x, next_day));
				}
			}
			//벽 아님
			if (map[next_y][next_x] != WALL) {
				if (dist[next_day][curr.remain][next_y][next_x] != MAX)
					continue ;
				dist[next_day][curr.remain][next_y][next_x] = next_dist;
				que.push(coord(curr.remain, next_y, next_x, next_day));
			}
		}
	}
}

int main(void) {
	//입출력 part
	cin >> n >> m >> k;
	map = new int *[n];
	// dist는 4차원 배열 -> dist[day_night][remain_power][y][x]
	dist = new int ***[2];
	dist[0] = new int **[k + 1];
	dist[1] = new int **[k + 1];
	for (int i = 0; i < k + 1; i++) {
		dist[0][i] = new int *[n];
		dist[1][i] = new int *[n];
		for (int j = 0; j < n; j++) {
			dist[0][i][j] = new int[m];
			dist[1][i][j] = new int[m];
			if (i == 0)
				map[j] = new int[m];
		}
	}
	for (int remain = 0; remain < k + 1; remain++) {
		for (int y = 0; y < n; y++) {
			string input;
			if (remain == 0)
				cin >> input;
			for (int x = 0; x < m; x++) {
				dist[0][remain][y][x] = MAX;
				dist[1][remain][y][x] = MAX;
				if (remain == 0)
					map[y][x] = input[x] - '0';
			}
		}
	}
	bfs();
	for (int i = 0; i < k + 1; i++) {
		int temp_ret = min(dist[0][i][n - 1][m - 1], dist[1][i][n - 1][m - 1]);
		ret = min(ret, temp_ret);
	}
	if (ret == MAX)
		ret = -1;
	cout << ret << endl;
	return 0;
}
