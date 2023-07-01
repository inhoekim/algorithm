#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int N, M, K;
int a[10][10];
int m[10][10];
int breeding[10][10];
int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, \
			 {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
vector<vector<deque<int>>> trees;

void winter_proc() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			m[i][j] += a[i][j];
}

void autumn_proc() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (breeding[y][x] <= 0)
				continue;
			for (int i = 0; i < 8; i++) {
				int ny = y + dirs[i][0];
				int nx = x + dirs[i][1];
				if (ny < 0 || ny == N || nx < 0 || nx == N)
					continue;
				for (int j = 0; j < breeding[y][x]; j++)
					trees[ny][nx].push_front(1);
			}
		}
	}
}

void spring_proc() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int tree_cnt = trees[y][x].size();
			int die_cnt = 0;
			int died_idx = -1;
			for (int i = 0; i < tree_cnt; i++) {
				//양분 흡수
				if (m[y][x] - trees[y][x][i] >= 0) {
					m[y][x] -= trees[y][x][i];
					trees[y][x][i]++;
					//새로운 번식가능 나무가 생성된 경우
					if (trees[y][x][i] % 5 == 0)
						breeding[y][x]++;
					else if ((trees[y][x][i] - 1) % 5 == 0)
						breeding[y][x]--;
				}
				//양분이 없는 경우
				else {
					died_idx = i;
					break;
				}
			}
			//죽은 나무를 제거한다
			if (died_idx != -1) {
				for (int i = trees[y][x].size() - 1; i >= died_idx; i--) {
					die_cnt += trees[y][x][i] / 2;
					if (trees[y][x][i] % 5 == 0)
						breeding[y][x]--;
					trees[y][x].pop_back();
				}
			}
			//여름(죽은 나무는 양분이 된다)
			m[y][x] += die_cnt;
		}
	}
}

void turn_proc(int remain) {
	while (remain--) {
		//봄(모든 나무에게 양분을 분배한다)
		spring_proc();
		//가을(번식)
		autumn_proc();
		//겨울(양분추가)
		winter_proc();
	}
}

int main(void)
{
	cin >> N >> M >> K;
	trees = vector<vector<deque<int>>>(N);
	for (int i = 0; i < N; i ++) {
		trees[i] = vector<deque<int>>(N);
		for (int j = 0; j < N; j++)
			cin >> a[i][j];
	}
	for (int i = 0; i < M; i++) {
		int y, x, old;
		cin >> y >> x >> old;
		trees[y - 1][x - 1].push_back(old);
		if (old % 5 == 0)
			breeding[y - 1][x - 1]++;
	}
	fill(&m[0][0], &m[9][10], 5);
	turn_proc(K);
	int ret = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			ret += trees[i][j].size();
	cout << ret << endl;
	return 0;
}
