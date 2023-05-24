#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;
stringstream ss;
char **picture;

void print_star(int n, int start_y, int start_x){
	if (n == 1)
		return;
	//영역을 9등분해서 재귀적으로 별을 그린다
	for (int i = 0; i < 9; i++) {
		int next_y = start_y + ((i / 3) * (n / 3));
		int next_x = start_x + ((i % 3) * (n / 3));
		if (i != 4)
			print_star(n / 3, next_y, next_x);
		//9등분된 영역의 중간부(idx == 5)는 빈 공백으로 채워진다
		else {
			for (int i = 0; i < n / 3; i++)
				for (int j = 0; j < n / 3; j++)
					picture[next_y + i][next_x + j] = ' ';
		}
	}
}

int main(void) {
	int n;
	cin >> n;
	picture = new char*[n];
	for (int i = 0; i < n; i++) {
		picture[i] = new char[n];
		fill(&picture[i][0], &picture[i][n], '*');
	}
	print_star(n, 0, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << picture[i][j];
		cout << endl;
	}
}
