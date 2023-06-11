#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

int n, m;
stringstream ss;
vector<int> nums;

void recur(int cnt, int idx){
	if (cnt == m) {
		for (int i = 0; i < nums.size(); i++) {
			if (i != nums.size() - 1)
				ss << nums[i] << " ";
			else
				ss << nums[i] << endl;
		}
		return;
	}
	for (int i = idx; i <= n; i++) {
		nums.push_back(i);
		recur(cnt + 1, i + 1);
		nums.pop_back();
	}
}

int main(void) {
	cin >> n >> m;
	recur(0, 1);
	cout << ss.str();
}
