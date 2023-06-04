#include <iostream>
#include <algorithm>

using namespace std;

int n;
bool row[15];
bool left_diagonal[30];
bool right_diagonal[30];
int ret;

void recur(int cnt) {
	if (cnt == n) {
		ret++;
		return;
	}
	int ld_idx;
	int rd_idx;
	for (int i = 0; i < n; i++) {
		ld_idx = cnt - i;
		if (ld_idx < 0)
			ld_idx = n + abs(ld_idx);
		rd_idx = cnt + i;
		if (row[i] || left_diagonal[ld_idx] || right_diagonal[rd_idx])
			continue;
		row[i] = true;
		left_diagonal[ld_idx] = true;
		right_diagonal[rd_idx] = true;
		recur(cnt + 1);
		row[i] = false;
		left_diagonal[ld_idx] = false;
		right_diagonal[rd_idx] = false;
	}
}

int main(void) {
	cin >> n;
	recur(0);
	cout << ret;
}
