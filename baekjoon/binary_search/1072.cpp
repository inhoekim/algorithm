#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

long long X, Y, Z;

int binary_search(int min_len, int max_len) {
	while (min_len != max_len) {
		long long temp_result = (min_len + max_len) / 2;
		long long temp_z = (Y + temp_result) * 100 / (X + temp_result);
		if (temp_z == Z)
			min_len = temp_result + 1;
		else
			max_len = temp_result;
	}
	if ((Y + min_len) * 100 / (X + min_len) == Z) 
		return -1;
	return min_len;
}

int main(void) {
	cin >> X >> Y;
	Z = Y * 100 / X;
	cout << binary_search(0, 1000000000) << endl;
	return 0;
}
