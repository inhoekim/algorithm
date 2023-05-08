#include <algorithm>
#include <iostream>
#include <vector>
#define WALL 1
#define CLEAR 2
using namespace std;

int n, m;
int room[50][50];
//북,동,남,서 순서
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class robot {
	public:
		int curr_y, curr_x, dir_idx;
		robot(int y, int x, int dir) {
			curr_y = y;
			curr_x = x;
			dir_idx = dir;
		}
		void rotate(){
			dir_idx += 4;
			dir_idx = (dir_idx - 1) % 4;
		}
};

int cleaning(robot rb){
	int ret = 0;
	vector<int> trash;
	while(true){
		int next_y, next_x, back_dir;
		//현재 칸이 아직 청소되지 않는 경우 청소함
		if (room[rb.curr_y][rb.curr_x] == 0) {
			room[rb.curr_y][rb.curr_x] = CLEAR;
			ret++;
		}
		trash.clear();
		//주변 4칸을 검사
		for (int dir = 0; dir < 4; dir++) {
			next_y = rb.curr_y + dirs[dir][0];
			next_x = rb.curr_x + dirs[dir][1];
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == m || room[next_y][next_x] == WALL)
				continue ;
			if (room[next_y][next_x] == 0)
				trash.push_back(dir);
		}
		//청소해야할 칸이 있는 경우
		if (!trash.empty()) {
			rb.rotate();
			for (int trash_dir : trash) {
				if (rb.dir_idx == trash_dir) {
					next_y = rb.curr_y + dirs[rb.dir_idx][0];
					next_x = rb.curr_x + dirs[rb.dir_idx][1];
					rb.curr_y = next_y;
					rb.curr_x = next_x;
					break;
				}
			}
		}
		//청소해야할 칸이 없는 경우
		else {
			back_dir = (rb.dir_idx + 2) % 4;
			next_y = rb.curr_y + dirs[back_dir][0];
			next_x = rb.curr_x + dirs[back_dir][1];
			//후진할 수 없는 경우 로봇 작동 중지
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == m || room[next_y][next_x] == WALL)
				break;
			rb.curr_y = next_y;
			rb.curr_x = next_x;
		}
	}
	return (ret);
}

int main(void) {
	int curr_y, curr_x, dir;
	cin >> n >> m >> curr_y >> curr_x >> dir;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> room[i][j];
	int ret = 0;
	ret = cleaning(robot(curr_y, curr_x, dir));
	cout << ret << endl;
}
