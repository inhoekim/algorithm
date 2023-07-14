#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 987654321
using namespace std;

int main(void) {
	int N;
	cin >> N;
	vector<int> nums;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		nums.push_back(num);
	}
	nums.push_back(MAX);
	int ret = 0;
	for (int i = N - 1; i >= 0; i--) {
		if (nums[i] >= nums[i + 1]) {
			ret += (nums[i] - nums[i + 1]) + 1;
			nums[i] = nums[i + 1] - 1;
		}
	}
	cout << ret << endl;
}
