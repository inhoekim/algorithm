#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class egg {
	public :
		int s, w;
		egg(int s, int w) {
			this->s = s;
			this->w = w;
		}
};

vector<egg> eggs;
int n;
int ret;

void recur(int curr, int temp_ret) {
	//3단계 - 종료확인 -> 2단계
	if (curr == n)
	{
		ret = max(ret, temp_ret);
		return ;
	}
	//현재 계란이 깨진 계란이라면 넘긴다
	if (eggs[curr].s <= 0)
		recur(curr + 1, temp_ret);
	else {
		//박살낼 계란 선택
		bool is_all_broken = true;
		for (int i = 0; i < n; i++) {
			if (i == curr || eggs[i].s <= 0)
				continue;
			is_all_broken = false;
			//백트래킹 이후 되돌리기 위해 현재 상태를 임시변수에 담음
			egg temp = egg(eggs[curr].s, eggs[curr].w);
			egg temp2 = egg(eggs[i].s, eggs[i].w);
			//계란 충돌
			eggs[curr] = egg(temp.s - temp2.w, temp.w);
			eggs[i] = egg(temp2.s - temp.w, temp2.w);
			if (eggs[curr].s <= 0)
				temp_ret++;
			if (eggs[i].s <= 0)
				temp_ret++;
			//다음단계
			recur(curr + 1, temp_ret);
			//상태복구
			if (eggs[curr].s <= 0)
				temp_ret--;
			if (eggs[i].s <= 0)
				temp_ret--;
			eggs[curr] = temp;
			eggs[i] = temp2;
		}
		if (is_all_broken)
			recur(curr + 1, temp_ret);
	}
}

int	main(void)
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		eggs.push_back(egg(a, b));
	}
	recur(0, 0);
	cout << ret << endl;
	return (0);
}
