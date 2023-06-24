  #include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int	ret = 0;
int player[50][9];
int	order[9];
bool picked[9];

void game_start() {
	int	temp_ret = 0;
	int inning = 0;
	int idx = 0;
	while (inning < n) {
		bool base[3] = {false,};
		int out_cnt = 0;
		while (out_cnt < 3) {
			int hit = player[inning][order[idx]];
			idx = (idx + 1) % 9;
			//아웃
			if (hit == 0) {
				out_cnt++;
				continue ;
			}
			for (int i = 2; i >= 0; i--) {
				//만약 루상에 주자가 있을 경우
				if (base[i]) {
					if (i + hit >= 3) //현재 안타로 홈까지 갈 수 있는 경우
						temp_ret++;
					else //홈까지 갈수 없는 경우
						base[i + hit] = true;
					base[i] = false;
				}
			}
			//홈런
			if (hit == 4)
				temp_ret++;
			else
				base[hit - 1] = true;
		}
		inning++;
	}
	ret = max(ret, temp_ret);
}

void decide_order(int idx)
{
	if (idx == 3) {
		decide_order(idx + 1);
		return ;
	}
	//9명의 타순을 다 정했다면 게임스타트
	if (idx == 9) {
		game_start();
		return;
	}
	
	for (int i = 1; i <= 8; i++) {
		if (picked[i])
			continue;
		picked[i] = true;
		order[idx] = i;
		decide_order(idx + 1);
		picked[i] = false;
	}
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 9; j++)
			cin >> player[i][j];
	//4번타자는 첫번째 선수가 고정
	order[3] = 0;
	decide_order(0);
	cout << ret << endl;
}
