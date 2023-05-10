#include <iostream>
#include <queue>
#include <utility>
#define APPLE 1
#define SNAKE 2
using namespace std;

int n;
int map[100][100];
//12시, 3시, 6시, 9시 순서
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main(void) {
	//입출력 part
	int k;
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int y, x;
		cin >> y >> x;
		map[y - 1][x - 1] = APPLE;
	}
	int l;
	cin >> l;
	int dir = 1;
	int head_y = 0; int head_x = 0;
	queue<pair<int, int>> snake;
	snake.push(make_pair(0, 0));
	int ret = 0;
	map[0][0] = SNAKE;
	bool game_over = false;
	for (int i = 0; i < l; i++) {
		int time;
		char rotate;
		cin >> time >> rotate;
		int temp_ret = 0;
		for (int j = ret + 1 ; j <= time; j++) {
			temp_ret++;
			int next_y = head_y + dirs[dir][0];
			int next_x = head_x + dirs[dir][1];
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == n
				|| map[next_y][next_x] == SNAKE) {
				game_over = true;
				break ;
			}
			//사과를 못먹었다면 꼬리는 이동함
			if (map[next_y][next_x] != APPLE) {
				pair<int, int> tail = snake.front();
				snake.pop();
				map[tail.first][tail.second] = 0;
			}
			map[next_y][next_x] = SNAKE;
			snake.push(make_pair(next_y, next_x));
			head_y = next_y; head_x = next_x;
		}
		if (rotate == 'D')
			dir = (dir + 1) % 4;
		else if (rotate == 'L')
			dir = (dir + 4 - 1) % 4;
		ret += temp_ret;
		if (game_over)
			break ;
	}
	if (!game_over) {
		while (true) {
			ret++;
			int next_y = head_y + dirs[dir][0];
			int next_x = head_x + dirs[dir][1];
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == n
				|| map[next_y][next_x] == SNAKE)
				break ;
			head_y = next_y;
			head_x = next_x;
		}
	}
	cout << ret << endl;
}
