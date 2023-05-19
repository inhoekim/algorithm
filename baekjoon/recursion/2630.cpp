#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

int ret[2];
int **map;

bool union_check(int width, pair<int, int> check_point){
	int c_y = check_point.first;
	int c_x = check_point.second;
	int color = map[c_y][c_x];
	for (int y = 0; y < width; y++)
		for (int x = 0; x < width; x++)
			if (color != map[c_y + y][c_x + x])
				return (false);
	ret[color]++;
	return (true);
}

void recur(int width, pair<int, int> curr) {
	bool is_union = union_check(width, curr);
	int next_width = width / 2;
	int c_y = curr.first;
	int c_x = curr.second;
	if (!is_union) {
		for (int y = 0; y <= next_width; y+= next_width)
			for (int x = 0; x <= next_width; x+= next_width)
				recur(next_width, make_pair(c_y + y , c_x + x));
	}
}

int main(void) {
	int n;
	cin >> n;
	map = new int*[n];
	for (int i = 0; i < n; i++)
		map[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];
	recur(n, make_pair(0, 0));
	cout << ret[0] << endl;
	cout << ret[1] << endl;
}
