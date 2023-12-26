	#include <iostream>
	#include <vector>
	#define Y first
	#define X second
	#define INF 987654321

	using namespace std;

	int map[10][10];

	bool can_change(pair<int ,int> lt, int idx) {
		for (int y = 0; y < idx + 1; y++)
			for (int x = 0; x < idx + 1; x++)
				if (lt.Y + y >= 10 || lt.X + x >= 10 || !map[lt.Y + y][lt.X + x]) 
					return false;
		return true;
	}

	void change_map(pair<int, int> lt, int idx, bool is_reverse) {
		if (is_reverse) {
			for (int y = 0; y < idx + 1; y++)
				for (int x = 0; x < idx + 1; x++)
					map[lt.Y + y][lt.X + x] = 1;
		}
		else {
			for (int y = 0; y < idx + 1; y++)
				for (int x = 0; x < idx + 1; x++)
					map[lt.Y + y][lt.X + x] = 0;
		}
	}

	pair<int, int> get_left_top() {
		for (int y = 0; y < 10; y++) 
			for (int x = 0; x < 10; x++) 
				if (map[y][x] == 1)
					return {y, x};
		return {-1, -1};
	}

	int recur(vector<int> &remain_paper, int remain_one, int cnt) {
		pair<int, int> left_top = get_left_top();
		if (remain_one <= 0)
			return cnt;
		if (remain_paper[5] == 0)
			return INF;
		int ret = INF;
		for (int idx = 0; idx < 5; idx++) {
			if (remain_paper[idx] == 0)
				continue;
			if (!can_change(left_top, idx))
				continue;
			change_map(left_top, idx, false);
			remain_paper[idx]--; remain_paper[5]--;
			ret = min(ret, recur(remain_paper, remain_one - (idx + 1) * (idx + 1), cnt + 1));
			remain_paper[idx]++; remain_paper[5]++;
			change_map(left_top, idx, true);
		}
		return ret;
	}

	int main(void) {
		int num = 0;
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				cin >> map[y][x];
				if (map[y][x])
					num++;
			}
		}
		vector<int> remain_paper = {5, 5, 5, 5, 5, 25};
		int ret = recur(remain_paper, num, 0);
		if (ret == INF)
			cout << -1 << endl;
		else
			cout << ret << endl;
	}
