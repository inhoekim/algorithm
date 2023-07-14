#include <iostream>
#include <algorithm>
#include <queue>
#define START first
#define END second

using namespace std;

bool compare(pair<int,int> a, pair<int,int> b) {
	if (a.END == b.END)
		return (a.START < b.START);
	return (a.END < b.END);
}

int main(void) {
	int n;
	cin >> n;
	vector<pair<int, int>> rooms;
	for (int i = 0; i < n; i++) {
		int start, end;
		cin >> start >> end;
		rooms.push_back({start, end});
	}
	sort(rooms.begin(), rooms.end(), compare);
	priority_queue<pair<int, int>> pq;
	pq.push({rooms[0].END * -1, rooms[0].START});
	int max_ret = 1;
	for (int i = 1; i < rooms.size(); i++) {
		pair<int, int> room = pq.top();
		while (room.first * -1 <= rooms[i].START && !pq.empty()) {
			pq.pop();
			room = pq.top();
		}
		pq.push({rooms[i].END * -1, rooms[i].START});
		max_ret = max(max_ret, (int)pq.size());
	}
	cout << max_ret << endl;
}
