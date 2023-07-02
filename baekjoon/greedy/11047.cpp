#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


int main(void)
{
	int n, k;
	cin >> n >> k;
	vector<int> lst(n);
	for (int i = 0; i < n; i++)
		cin >> lst[i];
	int ret = 0;
	for (int i = lst.size() - 1; i >= 0; i--) {
		ret += k / lst[i];
		k = k % lst[i];
	}
	cout << ret << endl;
}
