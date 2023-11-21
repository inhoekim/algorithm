#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

int main(void) {
	int cnt_a, cnt_b;
	cin >> cnt_a >> cnt_b;
	unordered_set<int> um_a, um_b;
	for (int i = 0; i < cnt_a; i++) {
		int temp;
		cin >> temp;
		um_a.insert(temp);
	}

	for (int i = 0; i < cnt_b; i++) {
		int temp;
		cin >> temp;
		um_b.insert(temp);
	}
	int result = 0;
	int cnt = 0;
	for (auto element : um_b) {
		if (um_a.find(element) != um_a.end())
		cnt++;
	}
	result += um_a.size() - cnt;
	cnt = 0;
	for (auto element : um_a) {
		if (um_b.find(element) != um_b.end())
		cnt++;
	}
	result += um_b.size() - cnt;
	cout << result << endl;
	return 0;
}
