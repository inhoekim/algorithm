#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

long long recur(int n, int r, int c){
	long width = pow(2, n - 1);
	int curr_z_idx = (r / width) * 2 + (c / width); // 4등분된 상자의 인덱스(0,1,2,3)
	if (width == 1)
		return (curr_z_idx);
	return (curr_z_idx * width * width) + recur (n - 1, r % width, c % width);
}

int main(void) {
	int n, r, c;
	cin >> n >> r >> c;
	cout << recur(n, r, c) << endl;
}
