#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#define Y first 
#define X second
using namespace std;

int ret;
int n;
int max_idx;
int map[10][10];
bool l_diagonal[20];
bool r_diagonal[20];

void get_ret(int idx, int cnt, vector<vector<pair<int, int>>> &lst)
{
	if (idx == max_idx) {
		ret = max(cnt, ret);
		return;
	}
	if (cnt == max_idx)
	{
		cout << cnt << endl;
		exit(1);
	}
	bool nothing = true;
	for (int i = 0; i < lst[idx].size(); i++) {
		pair<int, int> curr = lst[idx][i];
		int l_diag_idx = (curr.Y - curr.X + max_idx) % max_idx;
		int r_diag_idx = (curr.Y + curr.X + max_idx) % max_idx;
		if (l_diagonal[l_diag_idx] || r_diagonal[r_diag_idx])
			continue ;
		nothing = false;
		l_diagonal[l_diag_idx] = true;
		r_diagonal[r_diag_idx] = true;
		get_ret(idx + 1, cnt + 1, lst);
		l_diagonal[l_diag_idx] = false;
		r_diagonal[r_diag_idx] = false;
	}
  //이거 조건 디버깅 없이 어떻게 찾을 수 있을까.. 자꾸 안되길래 디버깅 돌리고 추가해서 ac 맞은 조건
	if (nothing)
		get_ret(idx + 1, cnt, lst);
}

int main(void)
{
	cin >> n;
	max_idx = (2 * n) - 1;
	vector<vector<pair<int, int>>> l_lst = vector<vector<pair<int, int>>>(max_idx);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
			{
				int idx = (i - j + max_idx) % max_idx;
				int idx2 = (i + j + max_idx) % max_idx;
				l_lst[idx].push_back(make_pair(i, j));
			}
		}
	}
	get_ret(0, 0, l_lst);
	cout << ret << endl;
}
