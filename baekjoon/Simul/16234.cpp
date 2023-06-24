#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#define Y first
#define X second

using namespace std;

int n, l, r;
int map[50][50];
int temp_map[50][50];
int	dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool visited[50][50];
vector<pair<int, int>> lst;

int dfs(int y, int x) {
	int total = temp_map[y][x];
	lst.push_back(make_pair(y, x));
	visited[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int ny = y + dirs[i][0];
		int nx = x + dirs[i][1];
		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			continue;
		int diff = abs(temp_map[ny][nx] - map[y][x]);
		if (visited[ny][nx] || diff < l || diff > r)
			continue;
		total += dfs(ny, nx);
	}
	return (total);
}

void copy_map()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp_map[i][j] = map[i][j];
}

int	main(void) {
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			temp_map[i][j] = map[i][j];
		}
	}
	int ret = -1;
	while (true) {
		ret++;
		fill(&visited[0][0], &visited[49][50], false);
		bool is_moved = false;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!visited[i][j]){
					lst = vector<pair<int, int>>();
					int total = dfs(i, j);
					if (lst.size() > 1) {
						is_moved = true;
						for (int k = 0; k < lst.size(); k++)
							map[lst[k].Y][lst[k].X] = total / lst.size();
					}
				}
			}
		}
		if (!is_moved)
			break;
		copy_map();
	}
	cout << ret << endl;
}
