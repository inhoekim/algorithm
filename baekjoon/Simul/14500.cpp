#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int map[500][500];

vector<vector<pair<int, int>>> tetromino = {
	{{0,1},{0,2},{0,3}}, // ㅡ 모양
	{{1,0},{2,0},{3,0}}, // ㅣ 모양
	{{0,1},{1,0},{1,1}}, // ㅁ 모양
	{{1,0},{2,0},{2,1}}, // L 모양
	{{1,0},{2,0},{2,-1}}, // L 모양(reverse)
	{{0,1},{0,2},{1,0}}, // L 모양 (90도 회전)
	{{0,1},{0,2},{1,2}}, // L 모양 (90도 회전 ,reverse)
	{{0,1},{1,1},{2,1}}, //L 모양 (180도 회전)
	{{0,1},{1,0},{2,0}}, //L 모양 (180도 회전, reverse)
	{{0,1},{0,2},{-1,2}}, // L 모양 (270도 회전)
	{{1,0},{1,1},{1,2}}, // L 모양 (270도 회전, reverse)
	{{1,0},{1,1},{2,1}}, // ㄴㄱ모양
	{{1,0},{1,-1},{2,-1}}, // ㄴㄱ모양(reverse)
	{{0,1},{-1,1},{-1,2}}, // ㄴㄱ모양(90도 회전)
	{{0,1},{1,1},{1,2}}, // ㄴㄱ모양(90도 회전, reverse)
	{{0,1},{1,1},{0,2}}, // ㅜ 모양
	{{1,0},{1,1},{2,0}}, // ㅏ 모양
	{{1,0},{1,-1},{2,0}}, // ㅓ 모양
	{{0,1},{-1,1},{0,2}} // ㅗ 모양
};

using namespace std;
int main(void) {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			cin >> map[i][j];
	int ret = -1;
	for (vector<pair<int, int>> coords: tetromino) {
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++) {
				int temp_ret = map[y][x];
				bool is_err = false;
				for (pair<int,int> coord : coords) {
					int c_y = coord.first + y;
					int c_x = coord.second + x;
					if (c_y < 0 || c_y >= n || c_x < 0 || c_x >= m) {
						is_err = true;
						break;
					}
					temp_ret += map[c_y][c_x];
				}
				if (!is_err)
					ret = max(ret, temp_ret);
			}
		}
	}
	cout << ret;
}
