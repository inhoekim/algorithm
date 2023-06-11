#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

int n, m;
vector<int> map;
bool used[10];
stringstream ss;

void recur(int cnt) {
	if (cnt == m) {
		for (int i = 0; i < map.size(); i++) {
			if (i == map.size() - 1)
				ss << map[i] << endl;
			else
				ss << map[i] << " ";
		}
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (used[i])
			continue;
		used[i] = true;
		map.push_back(i);
		recur(cnt + 1);
		used[i] = false;
		map.pop_back();
	}

}

int main(void) {
 	cin >> n >> m;
	recur(0);
	cout << ss.str();
}
