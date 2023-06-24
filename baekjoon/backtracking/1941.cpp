#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

stringstream ss;
int ret;
char v_map[25];
bool visited[5][5];
int picked[7];
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int n) {
	int y = n / 5;
	int x = n % 5;
	visited[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int ny = y + dirs[i][0];
		int nx = x + dirs[i][1];
		if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5 || visited[ny][nx])
			continue;
		for (int i = 0; i < 7; i++)
			if (picked[i] == ((ny * 5) + nx))
				dfs((ny * 5) + nx);
	}
}

int chk_princess(int s)
{
	if (s < 4)
		return (0);
	fill(&visited[0][0], &visited[4][5], false);
	dfs(picked[0]);
	for (int i = 0; i < 7; i++) {
		int y = picked[i] / 5;
		int x = picked[i] % 5;
		if (!visited[y][x])
			return (0);
	}
	return (1);
}

void pick_node(int cnt, int idx, int s) {
	if (cnt == 7) {
		ret += chk_princess(s);
		return ;
	}
	for (int i = idx; i < 25; i++) {
		picked[cnt] = i;
		if (v_map[i] == 'S')
			pick_node(cnt + 1, i + 1, s + 1);
		else
			pick_node(cnt + 1, i + 1, s);
	}
}

int main(void) {
	for (int i = 0; i < 25; i++) 
		cin >> v_map[i];
	pick_node(0, 0, 0);
	cout << ret << endl;
}
