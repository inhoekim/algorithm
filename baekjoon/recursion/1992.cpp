#include <iostream>
#include <algorithm>
#include <utility>
#include <sstream>

using namespace std;

stringstream ss;
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
	ss << color;
	return (true);
}

void recur(int width, pair<int, int> curr) {
	bool is_union = union_check(width, curr);
	int next_width = width / 2;
	int c_y = curr.first;
	int c_x = curr.second;
	if (!is_union) {
		ss << '(';
		for (int y = 0; y <= next_width; y+= next_width)
			for (int x = 0; x <= next_width; x+= next_width)
				recur(next_width, make_pair(c_y + y, c_x + x));
		ss << ')';
	}
}

int main(void) {
	int n;
	cin >> n;
	map = new int*[n];
	for (int i = 0; i < n; i++)
		map[i] = new int[n];
	string input;
	for (int i = 0; i < n; i++) {
		cin >> input;
		for (int j = 0; j < n; j++)
			map[i][j] = input[j] - '0';
	}
	recur(n, make_pair(0, 0));
	cout << ss.str() << endl;
}
