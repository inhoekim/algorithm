#include <algorithm>
#include <queue>
#include <iostream>
#define MAX 987654321
#define LAND 1
using namespace std;

int ret = MAX;
int map[100][100];
int island_idx[100][100];
bool visited[100][100];
int directions[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
int n;

class Coord {
	public:
		int y, x, dist;

		Coord(int curr_y, int curr_x, int curr_dist) {
			y = curr_y;
			x = curr_x;
			dist = curr_dist;
		}
};

void dfs(int y, int x, int land_idx) {
	visited[y][x] = true;
	island_idx[y][x] = land_idx;
	for (int i = 0; i < 4; i++) {
		int next_y = y + directions[i][0];
		int next_x = x +directions[i][1];
		if (next_x < 0 || next_x == n || next_y < 0 || next_y == n
			|| visited[next_y][next_x] || map[next_y][next_x] != LAND)
			continue ;
		dfs(next_y, next_x, land_idx);
	}
}

void bfs(int start_y, int start_x, int land_idx) {
	//visited 배열 초기화
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			visited[y][x] = false;
	queue<Coord> que;
	que.push(Coord(start_y, start_x, 0));
	while (!que.empty()) {
		Coord curr = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int next_y = curr.y + directions[i][0];
			int next_x = curr.x +directions[i][1];
			//예외처리
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == n || visited[next_y][next_x])
				continue ;
			//만약 땅을 발견하면 새로운 섬인지 확인. 새로운 섬이 아니라면 continue
			if (map[next_y][next_x] == LAND) {
				if (island_idx[next_y][next_x] != land_idx) {
					ret = min(ret, curr.dist);
					return ;
				}
				continue ;
			}
			//바다라면 bfs 탐색 진행
			visited[next_y][next_x] = true;
			que.push(Coord(next_y, next_x, curr.dist + 1));
		}
	}
}


int main(void){
	cin >> n;
	//입출력 part
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			cin >> map[y][x];
	//map을 전부 dfs 탐색하면서 각 섬마다 idx를 부여
	int land_idx = 0;
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			if (!visited[y][x] && map[y][x] == LAND)
				dfs(y, x, land_idx++);
	//모든 좌표를 시작점으로 bfs를 돌리면서 최소값 찾기
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			if (map[y][x] == LAND)
				bfs(y, x, island_idx[y][x]);
	cout << ret << endl;
}
