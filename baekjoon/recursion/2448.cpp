#include <algorithm>
#include <iostream>

using namespace std;
char **picture;

void print_star(int n, int start_y, int start_x){
	if (n == 3) {
		//꼭지점 좌표 == (point_y, start_x)
		int point_y = start_y - 2;
		//꼭지점
		picture[point_y][start_x] = '*';
		//중간부
		picture[point_y + 1][start_x - 1] = '*';
		picture[point_y + 1][start_x + 1] = '*';
		//하단부
		for (int i = 0; i < 5; i++)
			picture[point_y + 2][start_x - 2 + i] = '*';
		return;
	}
	//영역을 4등분해서 재귀적으로 별을 그린다 (삼각형 3개가 둘러싸는 가운데는 빈영역)
	print_star(n / 2, start_y - (n / 2), start_x);
	print_star(n / 2, start_y, start_x - (n / 2));
	print_star(n / 2, start_y, start_x + (n / 2));
}

int main(void) {
	int n;
	cin >> n;
	picture = new char*[n];
	for (int i = 0; i < n; i++) {
		picture[i] = new char[n * 2];
		fill(&picture[i][0], &picture[i][n * 2], ' ');
	}
	print_star(n, n - 1, n - 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++)
			cout << picture[i][j];
		cout << endl;
	}
}
