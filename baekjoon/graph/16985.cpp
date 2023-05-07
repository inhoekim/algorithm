#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#define MAX 987654321

using namespace std;

int map[6][5][5];
int map_by_case[5][5][5];
int dist[5][5][5];
int directions[6][3] = {{0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}, {-1, 0, 0}, {1, 0, 0}};
int ret = MAX;

class Coord {
public:
	int h,y,x;
	Coord(int input_h, int input_y, int input_x) {
		h = input_h;
		y = input_y;
		x = input_x;
	}
};

int bsq() {
	for (int h = 0; h < 5; h++)
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				dist[h][y][x] = MAX;
	queue<Coord> queue;
	queue.push(Coord(0, 0, 0));
	dist[0][0][0] = 0;
	while (!queue.empty()) {
		if (dist[4][4][4] != MAX)
			return (dist[4][4][4]);
		Coord curr = queue.front();
		queue.pop();
		for (int i = 0; i < 6; i++) {
			int next_h = curr.h + directions[i][0];
			int next_y = curr.y + directions[i][1];
			int next_x = curr.x + directions[i][2];
			if (next_h < 0 || next_h == 5 || next_y < 0 || next_y == 5 || next_x < 0 || next_x == 5
				|| dist[next_h][next_y][next_x] != MAX || map_by_case[next_h][next_y][next_x] == 0)
				continue;
			dist[next_h][next_y][next_x] = dist[curr.h][curr.y][curr.x] + 1;
			queue.push(Coord(next_h, next_y, next_x));
		}
	}
	return (MAX);
}

void rotate_block(int block_idx) {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++)
			map[5][y][x] = map[block_idx][4 - x][y];
	}
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++)
			map[block_idx][y][x] = map[5][y][x];
	}
}

void order_block() {
	vector<int> permutation_lst = {0,1,2,3,4};
	//주어진 5개의 블록을 순서의 모든 경우의 수를 구해 쌓고 bsq를 전부 시도
	do{
		if (map[permutation_lst[0]][0][0] == 0 || map[permutation_lst[4]][4][4] == 0)
			continue ;
		for (int i = 0; i < 5; i++) {
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++)
					map_by_case[i][y][x] = map[permutation_lst[i]][y][x];
			}
		}
		ret = min(ret, bsq());
	}while(next_permutation(permutation_lst.begin(), permutation_lst.end()));
}

void get_recur_all_case(int curr_h) {
	//5개의 블럭에 대해서 회전을 전부 시도하고 난 뒤, 판을 쌓을 순서를 정해서 bsq를 돌린다
	if (curr_h == 5) {
		order_block();
		return ;
	}
	//5개의 block을 전부 회전시켜봄 (모든 경우의 수를 전부 구한다)
	for (int i = 0; i < 4; i++) {
		rotate_block(curr_h);
		get_recur_all_case(curr_h + 1);
	}
}

int main(void){
	for (int h = 0; h < 5; h++) {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++)
				cin >> map[h][y][x];
		}
	}
	get_recur_all_case(0);
	if (ret == MAX)
		ret = -1;
	cout << ret << endl;
}
