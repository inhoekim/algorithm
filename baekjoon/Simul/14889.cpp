#include <algorithm>
#include <iostream>
#define MAX 987654321
using namespace std;

int n;
int team[20][20];
int ret = MAX;
int all_bit = 0;

int cal_score(int a_team) {
	int score_a = 0;
	int score_b = 0;
	int b_team = all_bit ^ a_team;
	for (int i = 0; i < n; i++) {
		int member_bit = 1 << i;
		for (int j = 0; j < n; j++) {
			int member2_bit = 1 << j;
			if (((a_team & member_bit) == member_bit) && ((a_team & member2_bit) == member2_bit))
				score_a += team[i][j];
			if (((b_team & member_bit) == member_bit) && ((b_team & member2_bit) == member2_bit))
				score_b += team[i][j];
		}
	}
	return abs(score_a - score_b);
}

void pick_team(int cnt, int target_idx, int a_team){
	if (cnt == n / 2) {
		ret = min(cal_score(a_team), ret);
		return;
	}
	if (target_idx == n)
		return;
	int target_bit = 1 << target_idx;
	pick_team(cnt + 1, target_idx + 1, a_team | target_bit);
	pick_team(cnt, target_idx + 1, a_team);
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> team[i][j];
	int pick_b = 0;
	for (int i = 0; i < n; i++)
		all_bit = all_bit | (1 << i) ;
	pick_team(0, 0, 0);
	cout << ret << endl;
}
