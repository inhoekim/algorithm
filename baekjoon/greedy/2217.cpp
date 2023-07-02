#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
	int n;
	cin >> n;
	vector<int> rope(n);
	for (int i = 0; i < n; i++)
		cin >> rope[i];
	int ret = 0;
	sort(rope.begin(), rope.end());
	for (int i = 0; i < n; i++) {
		int size = n - i;
		ret = max(rope[i] * size, ret);
	}
	cout << ret << endl;
}
