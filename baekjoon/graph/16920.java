#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#define WALL #
#define EMPTY .

using namespace std;

int n, m, p;
int players[10];
int ret[10];
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
class coord;
vector<vector<char>> map;
vector<vector<coord>> new_castle(10);

class coord{
public:
	int y, x, castle_idx, dist;
	coord(int c_y, int c_x, int c_i, int c_d) {
		y = c_y;
		x = c_x;
		castle_idx = c_i;
		dist = c_d;
	}
};

void bfs(queue<coord> &que, vector<coord> &temp_castle) {
	while (!que.empty()) {
		coord curr = que.front();
		que.pop();
		if (curr.dist == players[curr.castle_idx])
			continue ;
		for (int i = 0; i < 4; i++) {
			int next_y = curr.y + dirs[i][0];
			int next_x = curr.x + dirs[i][1];
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == m
				|| map[next_y][next_x] != '.')
				continue ;
			map[next_y][next_x] = curr.castle_idx + '0';
			ret[curr.castle_idx]++;
			temp_castle.push_back(coord(next_y, next_x, curr.castle_idx, 0));
			que.push(coord(next_y, next_x, curr.castle_idx, curr.dist + 1));
		}
	}
}

int main(void) {
	//입출력 part
	cin >> n >> m >> p;
	for (int i = 1; i <= p; i++)
		cin >> players[i];
	map = vector<vector<char>>(n, vector<char>(m, 0));
	for (int i = 0; i < n ; i++) {
		string input;
		cin >> input;
		for (int j = 0; j < m; j++) {
			map[i][j] = input[j];
			if ('0' <= input[j] && input[j] <= '9'){
				new_castle[input[j] - '0'].push_back(coord(i, j, input[j] - '0', 0));
				ret[input[j] -'0']++;
			}
		}
	}
	//탐색 part
	bool flag = true;
	while(flag) {
		//새로운 성이 존재한다면 flag는 다시 true가 됨
		flag = false;
		//"플레이어 1"부터 차례대로 bfs탐색 시작
		for (int i = 1; i <= p; i++) {
			vector<coord> temp_castle;
			queue<coord> que;
			for (coord curr : new_castle[i]) {
				flag = true;
				que.push(curr);
			}
			bfs(que, temp_castle);
			new_castle[i] = temp_castle;
		}
	}
	//출력 part
	for (int i = 1; i <= p; i++) {
		if (i == p)
			cout << ret[i] << endl;
		else
			cout << ret[i] << " ";
	}
}
