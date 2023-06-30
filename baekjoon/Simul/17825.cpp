#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class player {
	public:
		int path;
		int pos = -1;
		bool is_end;
		player(int path, int pos, bool is_end) {
			this->path = path;
			this->pos = pos;
			this->is_end = is_end;
		};
		player(void){
			this->path = 0;
			this->pos = -1;
			this->is_end = false;
		}
};
vector<int> path1 = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40};
vector<int> path2 = {13,16,19,25,30,35,40};
vector<int> path3 = {22,24,25,30,35,40};
vector<int> path4 = {28,27,26,25,30,35,40};
vector<vector<int>> paths = {path1, path2, path3, path4};
int ret = -1;
int order[10];
player players[4];

bool check_dup(int p, int path, int pos) {
	
	for (int i = 0; i < 4; i++) {
		if (i == p || players[i].is_end)
			continue;
	
		if (players[i].path == path && players[i].pos == pos)
			return (true);
		
		if ((paths[path][pos] == 25 || paths[path][pos] == 35 || paths[path][pos] == 40) \
		&& (paths[players[i].path][players[i].pos] == paths[path][pos]))
			return (true);
		
		if (paths[path][pos] == 30 && path != 0 && \
		paths[players[i].path][players[i].pos] == 30 && players[i].path != 0)
		return (true);
	}
	return (false);
}

void move_player(int o_idx, int score) {
	if (o_idx == 10) {
		ret = max(ret, score);
		return;
	}
	for (int p = 0; p < 4; p++) {
		if (players[p].is_end)
			continue;
		//재귀가 끝나고 상태를 되돌리기 위해 임시변수 선언
		player temp_player = player(players[p].path, players[p].pos, players[p].is_end);
		int temp_score = score;
	
		//만약 이동시킬려는 플레이어가 교차로(경로를 바꿀 수 있는 점)에 있는경우 -> 경로를 변경해준다
		if (players[p].path == 0 && \
		(players[p].pos == 4 || players[p].pos == 9 || players[p].pos == 14))
		{
			if (players[p].pos == 4)
				players[p].path += 1;
			if (players[p].pos == 9)
				players[p].path += 2;
			if (players[p].pos == 14)
				players[p].path += 3;
			players[p].pos = -1;
		}
		//선택된 플레이어를 order만큼 움직인다
		players[p].pos += order[o_idx];
		if (players[p].pos >= paths[players[p].path].size()) {
			players[p].is_end = true;
			move_player(o_idx + 1, score);
		}
		//이미 다른 플레이어가 해당 위치에 존재하는 지 검사
		else {
			if (!check_dup(p, players[p].path, players[p].pos)) {
				//만약 도착점에 도착한 경우
				score += paths[players[p].path][players[p].pos];
				move_player(o_idx + 1, score);
			}
		}
		//조작한 점수와 플레이어를 다시 되돌린다
		score = temp_score;
		players[p] = temp_player;
	}
}

int main(void)
{
	for (int i = 0; i < 10; i++)
		cin >> order[i];
	move_player(0, 0);
	cout << ret << endl;
	return (0);
}
