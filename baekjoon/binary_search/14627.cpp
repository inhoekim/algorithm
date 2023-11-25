#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#define ll long long

using namespace std;

int S, C;
vector<ll> heights;

ll binary_search(ll min_len, ll max_len) {
	int test = 100;
	while (min_len != max_len && test--) {
		ll temp_result = (ll)ceil((min_len + max_len) / 2.0);
		int cnt = 0;
		for (int i = 0; i < heights.size(); i++)
			cnt += heights[i] / temp_result;
		if (cnt >= C)
			min_len = temp_result;
		else
			max_len = temp_result - 1;
	}
	return min_len;
}

int main(void) {
	cin >> S >> C;
	ll sum_height = 0;
	ll max_height = 0;
	for (int i = 0; i < S; i++) {
		ll temp;
		cin >> temp;
		heights.push_back(temp);
		max_height = max(max_height, temp); 
		sum_height += temp;
	}
	ll max_result = binary_search(1, max_height);
	ll result = 0;
	int cnt = 0;
	for (int i = 0; i < S; i++) {
		cnt += heights[i] / max_result;
		result += heights[i] % max_result;
	}
	if (cnt > C)
		result += (cnt - C) * max_result;
	cout << result << endl;
	return 0;
}

