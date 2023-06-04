#include <algorithm>
#include <iostream>
#include <deque>
#include <utility>

using namespace std;
bool	map[101][101];

int dirs[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
class coord{
	public:
		int y, x, dir;

		coord(int y, int x, int dir) {
			this->y = y;
			this->x = x;
			this->dir = dir;
		}

};
pair<int, int> make_dragon(deque<coord> &dragon, pair<int, int> last) {
	for (int i = dragon.size() - 1; i >= 0; i--) {
		coord target = dragon[i];
		int next_dir = (target.dir + 1) % 4;
		int next_y = last.first + dirs[next_dir][0];
		int next_x = last.second + dirs[next_dir][1];
		map[next_y][next_x] = true;
		dragon.push_back(coord(next_y, next_x, next_dir));
		last.first = next_y;
		last.second = next_x;
	}
	return (last);
}

int get_square() {
	int square_cnt = 0;
	for (int y = 0; y < 100; y++)
		for (int x = 0; x < 100; x++)
			if (map[y][x] && map[y+1][x] && map[y][x+1] && map[y+1][x+1])
				square_cnt++;
	return (square_cnt);
}

int main(void) {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		deque<coord> dragon;
		dragon.push_back(coord(y, x, d));
		map[y][x] = true;
		map[y + dirs[d][0]][x + dirs[d][1]] = true;
		pair<int, int> last = make_pair(y + dirs[d][0], x + dirs[d][1]);
		for (int j = 0; j < g; j++)
			last = make_dragon(dragon, last);
	}
	cout << get_square() << endl;
}
