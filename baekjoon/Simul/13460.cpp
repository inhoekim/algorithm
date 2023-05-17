#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 987654321
using namespace std;

char map[10][10];
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //상하좌우순
class bead{
public:
	int y, x;
	bool end, goal;
	char color;
	bead(int y, int x, char color) {
		this->y = y;
		this->x = x;
		this->color = color;
		this->end = false;
		this->goal = false;
	}
	bead(){};
};
bead *beads[2];
bead *red; bead *blue;
int ret = MAX;

void move_bead(bead *b, int dir) {
	int b_ny = b->y + dirs[dir][0];
	int b_nx = b->x + dirs[dir][1];
	if (map[b_ny][b_nx] == '#' || map[b_ny][b_nx] == 'B' || map[b_ny][b_nx] == 'R'){
		b->end = true;
		return ;
	}
	if (map[b_ny][b_nx] == 'O') {
		map[b->y][b->x] = '.';
		b->end = true;
		b->goal = true;
		return ;
	}
	map[b->y][b->x] = '.';
	map[b_ny][b_nx] = b->color;
	b->y = b_ny;
	b->x = b_nx;
}

void get_move_order(int dir) {
	if ((dir == 0 && red->y > blue->y) || //북쪽으로 기울일 때
		(dir == 1 && red->y < blue->y) || //남쪽으로 기울일 때
		(dir == 2 && red->x > blue->x) || //서쪽으로 기울일 때
		(dir == 3 && red->x < blue->x)) { //동쪽으로 기울일 때
		//파란색 구슬이 먼저 굴러가도록 순서를 조정한다
		beads[0] = blue;
		beads[1] = red;
	}
	else {
		beads[0] = red;
		beads[1] = blue;
	}
}

void recur(int n) {
	if (n == 11)
		return ;
	for(int dir = 0; dir < 4; dir++) {
		red->end = false; red->goal = false;
		blue->end = false; blue->goal = false;
		//temp_red와 temp_blue에 이동시키기전 구슬의 상태를 저장해놓음
		bead temp_red = bead(red->y, red->x, 'R');
		bead temp_blue = bead(blue->y, blue->x, 'B');
		//temp_map에 이동시키기전 map 상태를 저장해놓음
		char temp_map[10][10];
		copy(&map[0][0], &map[9][9], &temp_map[0][0]);
		get_move_order(dir);
		while (!(red->end && blue->end)) {
			if (!beads[0]->end)
				move_bead(beads[0], dir);
			if (!beads[1]->end)
				move_bead(beads[1], dir);
		}
		//만약 빨간구슬이 구멍에 들어가고 파란색 구슬은 들어가지 못한 경우 정답
		if (red->goal && !blue->goal)
			ret = min(ret, n);
		//구슬 두개 모두가 구멍에 들어가지 못한 경우 재귀로 들어가 다시 한번 맵을 기울여본다
		if (!red->goal && !blue->goal)
			recur(n+1);
		//두 구슬이 모두 구멍에 들어가버리거나,파란구슬만 구멍에 들어간 경우 다른 방향으로 맵을 기울여본다
		copy(&temp_map[0][0], &temp_map[9][9], &map[0][0]);
		red->y = temp_red.y; red->x = temp_red.x;
		blue->y = temp_blue.y; blue->x = temp_blue.x;
	}
}

int main(void) {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R')
				red = new bead(i, j, 'R');
			if (map[i][j] == 'B')
				blue = new bead(i, j, 'B');
		}
	}
	beads[0] = red; beads[1] = blue;
	recur(1);
	if (ret == MAX)
		ret = -1;
	cout << ret << endl;
	return (0);
}
