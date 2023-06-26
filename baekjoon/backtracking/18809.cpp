#include <iostream>
#include <queue>
#include <algorithm>
#include <deque>
#include <vector>

#define Y first
#define X second
using namespace std;


enum data{
	WALL = 0,
	EMPTY = 1,
	POS = 2,
	GREEN = 3,
	RED = 4
};

class seed {
public:
	int y, x, color;
	seed(int y, int x, int color) {
		this->y = y;
		this->x = x;
		this->color = color;
	}
};

int n, m ,g ,r;
int map[50][50];
int dist[50][50];
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int ret;
vector<pair<int, int>> plant_lst;
deque<seed> dq;
deque<seed> temp_dq;

int bfs(int temp_map[50][50], deque<seed> t_dq) {
	int flower_cnt = 0;
	//dq -> 배양액 리스트
	while (!t_dq.empty()) {
		seed curr = t_dq.front();
		t_dq.pop_front();
		//꽃으로 변한 배양액은 더이상 전염시키지 못한다
		if (temp_map[curr.y][curr.x] == WALL)
			continue;
		for (int i = 0; i < 4; i++) {
			int ny = curr.y + dirs[i][0];
			int nx = curr.x + dirs[i][1];
			//맵밖이거나 호수, 꽃이 자라있다면 continue
			if (ny < 0 || ny >= n || nx < 0 || nx >= m || temp_map[ny][nx] == WALL)
				continue;
			//같은 배양액이 이미 자라있다면 continue
			if ((temp_map[ny][nx] == RED && curr.color == RED) || \
			(temp_map[ny][nx] == GREEN && curr.color == GREEN))
				continue;
			//다른 배양액이 자라있는 case -> 꽃을 피우고 continue 또는 그냥 continue
			if ((temp_map[ny][nx] == RED && curr.color == GREEN) || \
			(temp_map[ny][nx] == GREEN && curr.color == RED)) {
				if (abs(dist[curr.y][curr.x] - dist[ny][nx]) == 1) {
					temp_map[ny][nx] = WALL;
					flower_cnt++;
				}
				continue;
			}
			temp_map[ny][nx] = curr.color;
			dist[ny][nx] = dist[curr.y][curr.x] + 1;
			t_dq.push_back(seed(ny, nx, curr.color));
		}
	}
	return (flower_cnt);
}

void container_copy(int (*temp_arr)[50], deque<seed> &temp_dq) {
	for(int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			temp_arr[i][j] = map[i][j];

	for (int i = 0; i < dq.size(); i++)
		temp_dq.push_back(dq[i]);
}

void plant_seed(int r_cnt, int g_cnt, int idx) {
	if (r_cnt == r && g_cnt == g) {
		int t_ret = 0;
		fill(&dist[0][0], &dist[49][50], 0);
		int t_map[50][50];
		deque<seed> t_dq;
		container_copy(t_map, t_dq);
		t_ret = bfs(t_map, t_dq);
		ret = max(t_ret, ret);
		return;
	}
	if (idx == plant_lst.size() || r_cnt > r || g_cnt > g)
		return;
	int y = plant_lst[idx].Y;
	int x = plant_lst[idx].X;
	//초록 씨앗을 심었을 경우
	map[y][x] = GREEN;
	dq.push_back(seed(y, x,GREEN));
	plant_seed(r_cnt, g_cnt + 1, idx + 1);
	//붉은 씨앗을 심었을 경우
	map[y][x] = RED;
	dq.pop_back();
	dq.push_back(seed(y, x,RED));
	//아무것도 안심고 넘어가는 경우
	plant_seed(r_cnt + 1, g_cnt, idx + 1);
	dq.pop_back();
	map[y][x] = POS;
	plant_seed(r_cnt, g_cnt, idx + 1);
}

int main(void) {
	cin >> n >> m >> g >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == POS)
				plant_lst.push_back(make_pair(i, j));
		}
	}
	plant_seed(0, 0, 0);
	cout << ret << endl;
}

