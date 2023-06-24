#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int k;
stringstream ss;
vector<int> nums;
vector<int> picked_nums;

void pick_num(int cnt, int idx, int n) {
	if (cnt == 6) {
		for (int i = 0; i < 6; i++) {
			if (i == 5)
				ss << picked_nums[5] << endl;
			else
				ss << picked_nums[i] << " ";
		}
		return;
	}

	for (int i = idx; i < n; i++) {
		picked_nums[cnt] = nums[i];
		pick_num(cnt + 1, i + 1, n);
	}
}

int main(void) {
	while(true) {
		int n;
		cin >> n;
		if (n == 0)
			break;

		nums = vector<int>(n);
		picked_nums = vector<int>(6);
		for (int i = 0; i < n; i++)
			cin >> nums[i];
		pick_num(0, 0, n);
		ss << endl;
	}
	cout << ss.str();
}
