#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#define Y first
#define X second

using namespace std;

enum dirs{
	UP = 1, DOWN = 2, RIGHT = 3, LEFT = 4
};
class shark{
public:
	int s, d, z;
	shark(int s, int d, int z) {
		this->s = s;
		this->d = d;
		this->z = z;
	}
};

int r, c;
shark* map[100][100];
shark* temp_map[100][100];

int fishing_start(int idx) {
	for (int i = 0; i < r; i++) {
		//해당칸에 상어가 없는 경우
		if (map[i][idx] == NULL)
			continue;
		//처음만난 상어를 잡는다
		else {
			int size = ((shark *)map[i][idx])->z;
			map[i][idx] = NULL;
			return (size);
		}
	}
	return (0);
}

pair<int, int> cal_move(pair<int, int> curr, shark *shk) {
	int mv_cnt;
	int next_y = curr.Y; int next_x = curr.X;

	if (shk->d == UP) {
		mv_cnt = shk->s % (2 * r - 2) * -1;
		next_y = curr.Y + mv_cnt;
		if (next_y < 0) {
			next_y = next_y * -1;
			if (next_y >= r)
				next_y = (2 * r) - next_y - 2;
			else
				shk->d = DOWN;
		}
	}
	else if (shk->d == DOWN) {
		mv_cnt = shk->s % (2 * r - 2);
		next_y = curr.Y + mv_cnt;
		if (next_y >= r) {
			next_y = (2 * r) - next_y - 2;
			if (next_y < 0 )
				next_y *= -1;
			else
				shk->d = UP;
		}
	}
	else if (shk->d == LEFT) {
		mv_cnt = shk->s % (2 * c - 2) * -1;
		next_x = curr.X + mv_cnt;
		if (next_x < 0) {
			next_x = next_x * -1;
			if (next_x >= c)
				next_x = (2 * c) - next_x - 2;
			else
				shk->d = RIGHT;
		}
	}
	else if (shk->d == RIGHT) {
		mv_cnt = shk->s % (2 * c - 2);
		next_x = curr.X + mv_cnt;
		if (next_x >= c) {
			next_x = (2 * c) - next_x - 2;
			if (next_x < 0)
				next_x *= -1;
			else
				shk->d = LEFT;
		}
	}
	return (make_pair(next_y, next_x));
}

void move_shark() {
	fill(&temp_map[0][0], &temp_map[99][100], nullptr);
	for (int y = 0; y < r; y++) {
		for (int x = 0; x < c; x++) {
			shark *shk = (shark *)map[y][x];
			if (shk == nullptr)
				continue;
			pair<int, int> coord = cal_move({y, x}, shk);
			if (temp_map[coord.Y][coord.X] != nullptr) {
				shark *shk2 = (shark *)temp_map[coord.Y][coord.X];
				if ((*shk).z < (*shk2).z)
					shk = shk2;
			}
			temp_map[coord.Y][coord.X] = shk;
		}
	}
	for (int y = 0; y < r; y++)
		for (int x = 0; x < c; x++)
			map[y][x] = temp_map[y][x];
}

int main(void) {
	int m;
	int ret = 0;
	cin >> r >> c >> m;
	for (int i = 0; i < m; i++) {
		int y, x, s, d, z;
		cin >> y >> x >> s >> d >> z;
		shark* shk = new shark(s, d, z);
		map[y - 1][x - 1] = shk;
	}
	//본 로직 (낚시 -> 상어 이동)
	for (int i = 0; i < c; i++) {
		ret += fishing_start(i);
		move_shark();
	}
	cout << ret << endl;
}
