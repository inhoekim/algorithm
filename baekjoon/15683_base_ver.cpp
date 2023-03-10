#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int n, m;
int ret = INT_MAX;
int cctv_case[5] = {3,1,3,3,0};
vector<vector<int>> cctvs;
//direction = {상,하,좌,우}
vector<vector<vector<int>>> cctv_directions =
		{
		 {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}, //1번 cctv
		 {{0,0,1,1}, {1,1,0,0}}, //2번 cctv
		 {{1,0,0,1}, {0,1,0,1}, {0,1,1,0}, {1,0,1,0}}, //3번 cctv
		 {{1,0,1,1}, {1,1,0,1}, {0,1,1,1}, {1,1,1,0}}, //4번 cctv
		 {{1,1,1,1}} //5번 cctv
		};
//상하좌우 순
int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0, 1}};

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

void turn_on_cctv(vector<vector<char>> v, int case_num)
{
	int direction, cctv_type, next_y, next_x;

	for (int i = 0; i < cctvs.size(); i++){
		direction = case_num % 4;
		cctv_type = cctvs[i][0];
		//해당 cctv가 가리킬 수 없는 방향일 경우 그냥 종료
		if (direction > cctv_case[cctv_type])
			return ;
		//cctv 키는 작업 시작
		for (int j = 0; j < 4; j++){
			if (cctv_directions[cctv_type][direction][j] == 1){
				next_y = cctvs[i][1] + directions[j][0];
				next_x = cctvs[i][2] + directions[j][1];
				while (true)
				{
					//다음 좌표의 유효성 체크
					if (next_y < 0 || next_y >= n || next_x < 0 || next_x >= m || v[next_y][next_x] == '6')
						break;
					if (v[next_y][next_x] == '0')
						v[next_y][next_x] = '#';
					next_y += directions[j][0];
					next_x += directions[j][1];
				}
			}
		}
		case_num = case_num / 4;
	}
	int temp_ret = search_map(v);
	if (ret > temp_ret)
		ret = temp_ret;
}

int main() {
	//전체 경우의수
	int total_case = 1;
	scanf("%d %d", &n, &m);
	vector<vector<char>> v(n, vector<char>(m,0));
	//맵 입력 part
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &v[i][j]);
			//cctv인 경우, cctv 배열에 등록
			if('1' <= v[i][j] && v[i][j] <= '5')
				cctvs.push_back({v[i][j] - '0' - 1, i, j});
		}
	}
	//핵심 로직 part
	if (cctvs.size() == 0){
		ret = search_map(v);
	}
	else{
		for(int i = 0; i < cctvs.size(); i++)
			total_case *= 4;
		for (int i = 0; i < total_case; i++) {
			vector<vector<char>> temp_v = v;
			turn_on_cctv(temp_v, i);
		}
	}
	//출력 part
	printf("%d", ret);
	return 0;
}
