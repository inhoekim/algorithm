#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

int n, m;
vector<int> nums;
vector<int> picked;
stringstream ss;

void pick_num(int cnt, int idx) {
	if (cnt == m) {
		for (int i = 0; i < m; i++) {
			if (i == m - 1)
				ss << picked[i] << endl;
			else
				ss << picked[i] << " ";
		}
		return ;
	}
	for (int i = idx; i < n; i++) {
		picked.push_back(nums[i]);
		pick_num(cnt + 1, i);
		picked.pop_back();
	}
}
int main(void) {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		nums.push_back(temp);
	}
	sort(nums.begin(), nums.end());
	pick_num(0, 0);
	cout << ss.str();
}
