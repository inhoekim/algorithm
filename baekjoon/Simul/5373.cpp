#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

char left_cube[3][3], right_cube[3][3], up_cube[3][3], down_cube[3][3], front_cube[3][3], back_cube[3][3], temp_cube[3][3];
char (*cubes[])[3] = {up_cube, down_cube, front_cube, back_cube, left_cube, right_cube};

enum cube_idx {
	UP = 0,
	DOWN = 1,
	FRONT = 2,
	BACK = 3,
	LEFT = 4,
	RIGHT = 5
};

void init_proc() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			left_cube[i][j] = 'g';
			right_cube[i][j] = 'b';
			up_cube[i][j] = 'w';
			down_cube[i][j] = 'y';
			front_cube[i][j] = 'r';
			back_cube[i][j] = 'o';
		}
}

void rotate_cube(int idx, char dir) {
	int cnt = 1;
	if (dir == '-')
		cnt = 3;
	while (cnt--) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				temp_cube[i][j] = cubes[idx][2 - j][i];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[idx][i][j] = temp_cube[i][j];
	}
}

class cube {
	public:
		void rotate_left(char dir) {
			int cnt = 1;
			if (dir == '-')
				cnt = 3;
			while (cnt--) {
				for (int i = 0; i < 3; i++) {
					char temp = cubes[UP][i][0];
					cubes[UP][i][0] = cubes[BACK][2 - i][2];
					cubes[BACK][2 - i][2] = cubes[DOWN][i][0];
					cubes[DOWN][i][0] = cubes[FRONT][i][0];
					cubes[FRONT][i][0] = temp;
				}
			}
			rotate_cube(LEFT, dir);
		}

		void rotate_right(char dir) {
			int cnt = 1;
			if (dir == '+')
				cnt = 3;
			while (cnt--) {
				for (int i = 0; i < 3; i++) {
					char temp = cubes[UP][i][2];
					cubes[UP][i][2] = cubes[BACK][2 - i][0];
					cubes[BACK][2 - i][0] = cubes[DOWN][i][2];
					cubes[DOWN][i][2] = cubes[FRONT][i][2];
					cubes[FRONT][i][2] = temp;
				}
			}
			rotate_cube(RIGHT, dir);
		}

		void rotate_front(char dir) {
			int cnt = 1;
			if (dir == '-')
				cnt = 3;
			while (cnt--) {
				for (int i = 0; i < 3; i++) {
					char temp = cubes[UP][2][i];
					cubes[UP][2][i] = cubes[LEFT][2 - i][2];
					cubes[LEFT][2 - i][2] = cubes[DOWN][0][2 - i];
					cubes[DOWN][0][2 - i] = cubes[RIGHT][i][0];
					cubes[RIGHT][i][0] = temp;
				}
			}
			rotate_cube(FRONT, dir);
		}

		void rotate_back(char dir) {
			int cnt = 1;
			if (dir == '+')
				cnt = 3;
			while (cnt--) {
				for (int i = 0; i < 3; i++) {
					char temp = cubes[UP][0][i];
					cubes[UP][0][i] = cubes[LEFT][2 - i][0];
					cubes[LEFT][2 - i][0] = cubes[DOWN][2][2 - i];
					cubes[DOWN][2][2 - i] = cubes[RIGHT][i][2];
					cubes[RIGHT][i][2] = temp;
				}
			}
			rotate_cube(BACK, dir);
		}

		void rotate_up(char dir) {
			int cnt = 1;
			if (dir == '-')
				cnt = 3;
			while (cnt--) {
				for (int i = 0; i < 3; i++) {
					char temp = cubes[FRONT][0][i];
					cubes[FRONT][0][i] = cubes[RIGHT][0][i];
					cubes[RIGHT][0][i] = cubes[BACK][0][i];
					cubes[BACK][0][i] = cubes[LEFT][0][i];
					cubes[LEFT][0][i] = temp;
				}
			}
			rotate_cube(UP, dir);
		}

		void rotate_down(char dir) {
			int cnt = 1;
			if (dir == '+')
				cnt = 3;
			while (cnt--) {
				for (int i = 0; i < 3; i++) {
					char temp = cubes[FRONT][2][i];
					cubes[FRONT][2][i] = cubes[RIGHT][2][i];
					cubes[RIGHT][2][i] = cubes[BACK][2][i];
					cubes[BACK][2][i] = cubes[LEFT][2][i];
					cubes[LEFT][2][i] = temp;
				}
			}
			rotate_cube(DOWN, dir);
		}
};

int main(void)
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cube c;
		init_proc();
		for (int i = 0; i < n; i++) {
			string oper;
			cin >> oper;
			if (oper[0] == 'L') c.rotate_left(oper[1]);
			else if (oper[0] == 'R') c.rotate_right(oper[1]);
			else if (oper[0] == 'F') c.rotate_front(oper[1]);
			else if (oper[0] == 'B') c.rotate_back(oper[1]);
			else if (oper[0] == 'U') c.rotate_up(oper[1]);
			else if (oper[0] == 'D') c.rotate_down(oper[1]);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				cout << up_cube[i][j];
			cout << endl;
		}
	}
}
