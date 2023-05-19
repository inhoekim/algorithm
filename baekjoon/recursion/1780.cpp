#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#define ERR 2
using namespace std;

int ret[3];
int **map;

int check_union(int width, pair<int ,int> check_point){
	int s_y = check_point.first;
	int s_x  = check_point.second;
	int target_num = map[s_y][s_x];
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < width; x++) {
			if(map[s_y + y][s_x + x] != target_num)
				return (ERR);
		}
	}
	return (target_num);
}

void recur(int width, pair<int, int> check_point){
	int element_num = check_union(width, check_point);
	//만약 종이가 같은수로만 채워져있지 않다면 9등분 작업시작
	if (element_num == ERR) {
		int next_width = width / 3;
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				recur(width / 3, make_pair(check_point.first + (y * next_width), check_point.second + (x * next_width)));
	}
	else
		ret[element_num + 1]++;
}

int main(void) {
	int n;
	//입출력 part
	cin >> n;
	map = new int*[n];
	for (int i = 0; i < n; i++)
		map[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n ; j++)
			cin >> map[i][j];
	//9등분 시작
	recur(n, make_pair(0, 0));
	//결과 출력
	for (int i = 0; i < 3; i++)
		cout << ret[i] << endl;
}
