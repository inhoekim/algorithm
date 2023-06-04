#include <iostream>
#include <deque>

using namespace std;
int y, x;

int weight[4][4][2] = {{{0, 0}, {1, 0}, {1, 1}, {0, 1}},
					   {{0, 0}, {0, 1}, {1, 1}, {1, 0}},
					   {{1, 1}, {0, 1}, {0, 0}, {1, 0}},
					   {{1, 1}, {1, 0}, {0, 0}, {0, 1}}

};

int rotation(int area_idx, int rotate) {
	if (rotate == 0 || rotate == 2) {
		if (area_idx == 0)
			rotate = (rotate + 1) % 4;
		if (area_idx == 3)
			rotate = (4 + rotate - 1) % 4;
	}
	else if (rotate == 1 || rotate == 3) {
		if (area_idx == 0)
			rotate = (4 + rotate - 1) % 4;
		if (area_idx == 3)
			rotate = (rotate + 1) % 4;
	}
	return (rotate);
}

void get_coord(int n, int m, int rotate) {
	if (n == 2) {
		y += weight[rotate][m][0];
		x += weight[rotate][m][1];
		return;
	}
	int next_m = m % (n * n / 4);
	int area_idx = m / (n * n / 4);
	y += (weight[rotate][area_idx][0] * n / 2);
	x += (weight[rotate][area_idx][1] * n / 2);
	rotate = rotation(area_idx, rotate);
	get_coord(n / 2,next_m, rotate);
}

int main(void) {
	int n, m;
	cin >> n >> m;
	get_coord(n, m - 1, 0);
	cout << x + 1 << " " << y + 1 << endl;
}
