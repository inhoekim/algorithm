#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
	int n;
	cin >> n;
	vector<int> A, B;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		A.push_back(temp);
	}
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		B.push_back(temp);
	}
	sort(B.begin(), B.end(), greater<int>());
	sort(A.begin(), A.end());
	long long ret = 0;
	for (int i = 0; i < n; i++)
		ret += A[i] * B[i];
	cout << ret << endl;
}
