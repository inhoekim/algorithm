#include <algorithm>
#include <iostream>

using namespace std;
int ret = 0;
int n, l;
int map[100][100];
bool check[100][100];
void check_col()
{
	for (int x = 0; x < n; x++) {
		int temp_ret = ret;
		ret++;
		int same_cnt = 1;
		for (int y = 0; y < n - 1; y++) {
			if (map[y][x] == map[y + 1][x])
				same_cnt++;
			//높이차이가 2이상 나는 경우 건너가는것에 실패
			if (abs(map[y][x] - map[y + 1][x]) > 1)
				ret--;
				//하방향 경사로 설치확인
			else if (map[y][x] > map[y + 1][x]) {
				int range = y + l;
				for (int i = y + 1; i < range; i++) {
					if (i + 1 >= n || map[i][x] != map[i + 1][x]) {
						ret--;
						break;
					}
					check[y][i] = true;
				}
				y = range - 1;
				check[y + 1][x] = true;
				same_cnt = 1;
			}
			//상방향 경사로 설치확인
			else if (map[y][x] < map[y + 1][x]) {
				if (same_cnt < l || check[y + 1 - l][x] || check[y][x])
					ret--;
				same_cnt = 1;
			}
			if (temp_ret == ret)
				break;
		}
	}
}

void check_row() {
	for (int y = 0; y < n; y++) {
		int temp_ret = ret;
		ret++;
		int same_cnt = 1;
		for (int x = 0; x < n - 1; x++) {
			if (map[y][x] == map[y][x + 1])
				same_cnt++;
			//높이차이가 2이상 나는 경우 건너가는것에 실패
			if (abs(map[y][x] - map[y][x + 1]) > 1)
				ret--;
			//우방향 경사로 설치확인
			else if (map[y][x] > map[y][x + 1]) {
				int range = x + l;
				for (int i = x + 1; i < range; i++) {
					if (i + 1 >= n || map[y][i] != map[y][i + 1]) {
						ret--;
						break;
					}
					check[y][i] = true;
				}
				x = range - 1;
				check[y][x + 1] = true;
				same_cnt = 1;
			}
			//좌방향 경사로 설치확인
			else if (map[y][x] < map[y][x + 1]) {
				if (same_cnt < l || check[y][x + 1 - l] || check[y][x])
					ret--;
				same_cnt = 1;
			}
			if (temp_ret == ret)
				break;
		}
	}
}

int main(void) {
	cin >> n >> l;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];
	check_row();
	fill(&check[0][0], &check[n - 1][n], false);
	check_col();
	cout << ret << endl;
}
