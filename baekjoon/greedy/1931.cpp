#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class meeting {
public:
	int start, end;
	meeting(int start, int end) {
		this->start = start;
		this->end = end;
	}
};

struct cmp {
	bool operator()(meeting &a, meeting &b) {
		if (a.end == b.end) {
			return (a.start > b.start);
		}
		return (a.end > b.end);
	}
};

int main(void)
{
	priority_queue<meeting,vector<meeting>, cmp> pq;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int start, end;
		cin >> start >> end;
		pq.push(meeting(start, end));
	}
	int ret = 1;
	meeting curr = pq.top();
	pq.pop();
	while (!pq.empty()) {
		meeting next = pq.top();
		pq.pop();
		if (next.start < curr.end)
			continue;
		ret++;
		curr = next;
	}
	cout << ret << endl;
}
