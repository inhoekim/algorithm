#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
	int n;
	cin >> n;
	vector<int> P;
	P.push_back(0);
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		P.push_back(temp);
	}

	sort(P.begin(), P.end());
	long long ret = 0;
	for (int i = 1; i < n + 1; i++) {
		P[i] = P[i] + P[i - 1];
		ret += P[i];
	}
	cout << ret << endl;
}
