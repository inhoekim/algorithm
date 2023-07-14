#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
	int n;
	cin >> n;
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		nums.push_back(temp);
	}
	sort(nums.begin(), nums.end());
	long long ret = 0;
	//음수부터 해결 (음수끼리 그리디하게 최대한 묶는게 이득이다, 음수와 0이 짝지어지는 것도 포함)
	int idx = 0;
	for (int i = 0; i < nums.size(); i+=2) {
		if (i + 1 == nums.size() || nums[i + 1] > 0) {
			idx = i;
			break;
		}
		ret += (long long)nums[i] * nums[i + 1];
	}

	//양수들을 해결
	for (int i = nums.size() - 1; i >= idx; i-=2) {
		if (i - 1 < idx)
			ret += nums[i];
		else {
			if ((long long)nums[i] * nums[i - 1] > (long long)nums[i] + nums[i - 1])
				ret += (long long)nums[i] * nums[i - 1];
			else
				ret += (long long)nums[i] + nums[i - 1];
		}
	}
	cout << ret << endl;
}
