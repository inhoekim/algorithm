#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main(void) {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		vector<long long> nums;
		for (int i = 0; i < N; i++) {
			int num;
			cin >> num;
			nums.push_back(num);
		}
		long long ret = 0;
		long long max_value = -1;
		for (int i = N - 1; i >= 0; i--) {
			if (nums[i] > max_value)
				max_value = nums[i];
			else
				ret += max_value - nums[i];
		}
		cout << ret << endl;
	}
}
