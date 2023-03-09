#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int n, m;
int ret = INT_MAX;
int cctv_case[5] = {4,2,4,4,1};
//direction = {상,하,좌,우}
vector<vector<vector<int>>> cctv_direction =
		{
		 {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}, //1번 cctv
		 {{0,0,1,1}, {1,1,0,0}}, //2번 cctv
		 {{1,0,0,1}, {0,1,0,1}, {0,1,1,0}, {1,0,1,0}}, //3번 cctv
		 {{1,0,1,1}, {1,1,0,1}, {0,1,1,1}, {1,1,1,0}}, //4번 cctv
		 {{1,1,1,1}} //5번 cctv
		};
//상하좌우 순
int direction[4][2] = {{-1,0}, {1,0}, {0,-1}, {0, 1}};

int search_map(vector<vector<char>> &v)
{
	int temp_ret = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if (v[i][j] == '0')
				temp_ret++;
	return temp_ret;
}

void print_map(vector<vector<char>> &v)
{
	for(int y = 0; y < n; y++){
		for(int x = 0; x < m; x++)
			printf("%c ", v[y][x]);
		printf("\n");
	}
}

void turn_on_cctv(vector<vector<char>> &v, int direction_idx, int current_y, int current_x)
{
	int cctv_idx = v[current_y][current_x] - '0' - 1;
	for (int i = 0; i < 4; i++) {
		if (cctv_direction[cctv_idx][direction_idx][i] == 1) {
			int next_y = current_y + direction[i][0];
			int next_x = current_x + direction[i][1];
			// #으로 채우는 작업시작
			while (true)
			{
				//다음 좌표의 유효성 체크
				if (next_y < 0 || next_y >= n || next_x < 0 || next_x >= m || v[next_y][next_x] == '6')
					break;
				if (v[next_y][next_x] == '0')
					v[next_y][next_x] = '#';
				next_y = next_y + direction[i][0];
				next_x = next_x + direction[i][1];
			}
		}
		else
			continue;
	}
}

void recur_search(vector<vector<char>> &v, int current_y, int current_x)
{
	vector<vector<char>> temp_v;
	if (current_x == m) {
		current_y++;
		current_x = 0;
	}
	// 종료조건
	if (current_y == n) {
		int cnt = search_map(v);
		if (cnt < ret)
			ret = cnt;
		//print_map(v);
		//printf("\n");
		return;
	}
	char ch = v[current_y][current_x];
	// 현재 좌표가 cctv일 때
	if ('1' <= ch && ch <= '5') {
		for(int i = 0; i < cctv_case[ch - '0' - 1]; i++)
		{
			temp_v  = v;
			turn_on_cctv(v,  i, current_y, current_x);
			recur_search(v, current_y, current_x + 1);
			v = temp_v; // turn_off_cctv
		}
	}
	else
		recur_search(v, current_y, current_x + 1);
}


int main() {
	scanf("%d %d", &n, &m);
	vector<vector<char>> v(n, vector<char>(m,0));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			scanf(" %c", &v[i][j]);
	}
	recur_search(v,0,0);
	printf("%d", ret);
	return 0;
}
