#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

int n, m;
stringstream ss;
vector<int> pick_nums;
vector<int> nums;
bool used[10];

void recur(int cnt){
	if (cnt == m) {
		for (int i = 0; i < m; i++) {
			if (i != m - 1)
				ss << pick_nums[i] << " ";
			else
				ss << pick_nums[i] << endl;
		}
		return;
	}
	for (int i = 0; i < n; i++) {
		if (used[i])
			continue;
		pick_nums.push_back(nums[i]);
		used[i] = true;
		recur(cnt + 1);
		pick_nums.pop_back();
		used[i] = false;
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
	recur(0);
	cout << ss.str();
}
