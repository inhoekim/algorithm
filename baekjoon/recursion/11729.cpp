#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int cnt = 0;
stringstream ss;

void move_disk(int start, int dest, int waypoint, int bottom_idx){
	if (bottom_idx == 1) {
		cnt++;
		ss << start << " " << dest << "\n";
		return ;
	}
	move_disk(start, waypoint, dest ,bottom_idx - 1);
	cnt++;
	ss << start << " " << dest << "\n";
	move_disk(waypoint, dest, start, bottom_idx - 1);
}

int main(void) {
	int n;
	cin >> n;
	move_disk(1, 3, 2, n);
	cout << cnt << endl;
	cout << ss.str();
}
