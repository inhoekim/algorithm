#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int A[100][100];
int r, c, k;
int row_size = 3;
int col_size = 3;
int nums_cnt[101];
int ret = -1;

bool compare(int a, int b) {
	if (nums_cnt[a] == nums_cnt[b]) {
		return (a < b);
	}
	return (nums_cnt[a] < nums_cnt[b]);
};

bool proc() {
	if (A[r][c] == k)
		return (true);
	int temp_max_row = 0;
	int temp_max_col = 0;
	// R연산
	if (row_size >= col_size) {
		for (int i = 0; i < row_size; i++) {
			//R연산을 위한 등장 숫자 카운팅 이후 정렬단계
			vector<int> nums;
			fill(&nums_cnt[0], &nums_cnt[101], 0);
			for (int j = 0; j < col_size; j++) {
				int num = A[i][j];
				if (num == 0)
					continue;
				if (nums_cnt[num] == 0)
					nums.push_back(num);
				nums_cnt[num]++;
			}
			sort(nums.begin(), nums.end(), compare);
			//새로운 배열 만들기
			temp_max_col = max(temp_max_col, (int)nums.size() * 2);
			int nums_size = nums.size();
			if (nums_size > 50) {
				nums_size = 50;
				temp_max_col = 100;
			}
			for (int k = 0; k < nums_size; k++) {
				A[i][2 * k] = nums[k];
				A[i][(2 * k) + 1] = nums_cnt[nums[k]];
			}
			for (int k = nums_size * 2; k < row_size; k++)
				A[i][k] = 0;
		}
		col_size = temp_max_col;
	}
	// C연산
	else {
		for (int i = 0; i < col_size; i++) {
			//R연산을 위한 등장 숫자 카운팅 이후 정렬단계
			vector<int> nums;
			fill(&nums_cnt[0], &nums_cnt[101], 0);
			for (int j = 0; j < row_size; j++) {
				int num = A[j][i];
				if (num == 0)
					continue;
				if (nums_cnt[num] == 0)
					nums.push_back(num);
				nums_cnt[num]++;
			}
			sort(nums.begin(), nums.end(), compare);
			//새로운 배열 만들기
			temp_max_row = max(temp_max_row, (int)nums.size() * 2);
			int nums_size = nums.size();
			if (nums_size > 50) {
				nums_size = 50;
				temp_max_row = 100;
			}
			for (int k = 0; k < nums_size; k++) {
				A[2 * k][i] = nums[k];
				A[(2 * k) + 1][i] = nums_cnt[nums[k]];
			}
			for (int k = nums_size * 2; k < row_size; k++)
				A[k][i] = 0;
		}
		row_size = temp_max_row;
	}
	return (false);
}

int main(void) {
	cin >> r >> c >> k;
	r--;
	c--;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> A[i][j];
	do {
		ret++;
		if (ret == 101) {
			ret = -1;
			break;
		}
	}while(!proc());
	cout << ret << endl;
}
