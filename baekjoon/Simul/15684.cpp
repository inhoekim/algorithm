	#include <algorithm>
	#include <iostream>
	#include <map>
	#include <vector>
	#include <stdio.h>
	#define MAX 987654321
	using namespace std;

	int n, m, h;
	vector<map<int, bool>> col_lines(11);
	int ret = MAX;

	bool check(){
		//주어진 세로 사다리 n개를 모두 돌려보면서 자신의 자리로 돌아가는지 체크
		for (int i = 1; i <= n; i++) {
			int curr_col_idx = i;
			int curr_row_idx = 0;
			map<int, bool>::iterator iter;
			while (true) {
				iter = col_lines[curr_col_idx].find(curr_row_idx);
				//만약 현재 위치에 이동할 수 있는 다리가 존재하지 않는다면 사다리를 타고 계속 내려가본다
				if (iter == col_lines[curr_col_idx].end())
					iter = col_lines[curr_col_idx].upper_bound(curr_row_idx);
				//사다리를 타고 계속 내려와 바닥지점까지 내려간 경우 break;
				if (iter == col_lines[curr_col_idx].end())
					break ;
				int dir = 1;
				//사다리가 좌우방향은 key의 val을 보고 판단. 우로 놓여져있는 경우 true, 좌로 놓여져있는 경우 false
				if (!(*iter).second)
					dir = -1;
				curr_col_idx = curr_col_idx + dir;
				curr_row_idx = (*iter).first + 1;
			}
			//사다리타기 결과 다른 사다리로 이동한 경우 false
			if (curr_col_idx != i)
				return (false);
		}
		//모든 사다리가 자신의 위치로 가능 경우 true
		return (true);
	}

	void select_bridge(int cnt, int curr_n, int curr_h) {
		if (cnt >= ret)
			return;
		//사다리를 1개 추가할때마다 정답이 될 수 있는지 검사
		if (check()) {
			ret = min(cnt, ret);
			return ;
		}
		//사다리를 4개 이상 추가하는 경우는 검사하지 않음
		if (cnt == 3)
			return;
		if (curr_h > h) {
			curr_n++;
			curr_h = 1;
		}
		
		//조합
		for (int i = curr_n; i < n; i++) {
			for (int j = curr_h; j <= h; j++) {
				if ((col_lines[i].find(j) != col_lines[i].end()) || (col_lines[i + 1].find(j) != col_lines[i + 1].end()))
					continue;
				col_lines[i].insert({j, true});
				col_lines[i + 1].insert({j, false});
				select_bridge(cnt + 1, i, j + 1);
				col_lines[i].erase(j);
				col_lines[i + 1].erase(j);
			}
			curr_h = 1;
		}
	}

	int main(void) {
		cin >> n >> m >> h;
		for (int i = 1; i <= m; i++) {
			int row, col;
			cin >> row >> col;
			//map :: key = row_idx , val = 정방향(true), 역방향(false)
			col_lines[col].insert({row, true});
			col_lines[col + 1].insert({row, false});
		}
		select_bridge(0, 1, 1);
		if (ret == MAX)
			ret = -1;
		cout << ret << endl;
	}
