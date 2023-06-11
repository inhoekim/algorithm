#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, s;
vector<int> nums;
int ret;

void pick_num(int num_idx, int sum, bool is_pick) {
	if (sum == s && is_pick)
		ret++;
	if (num_idx == n)
		return;
	//현재 수를 뽑았을 때의 가지
	pick_num(num_idx + 1, sum + nums[num_idx], true);
	//현재 수를 뽑지 않았을 때의 가지
	pick_num(num_idx + 1, sum, false);
}

int main(void) {
 	cin >> n >> s;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		nums.push_back(temp);
	}
	pick_num(0, 0, false);
	cout << ret << endl;
}
