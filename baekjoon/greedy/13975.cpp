#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main(void) {
	int t;
	cin >> t;
	while(t--) {
		int k;
		cin >> k;
		priority_queue<long long> pq;
		for (int i = 0; i < k; i++) {
			int temp;
			cin >> temp;
			pq.push(temp * -1);
		}
		long long ret = 0;
		while (!pq.empty()) {
			long long a = pq.top(); pq.pop();
			long long b = pq.top(); pq.pop();
			ret += abs(a + b);
			if (!pq.empty())
				pq.push(a + b);
		}
		cout << ret << endl;
	}
}
