#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
	string s;
	cin >> s;
	int zero_cnt = 0;
	int one_cnt = 0;
	char before_ch = 0;
	for (auto ch : s) {
		if (before_ch != ch) {
			if (ch == '0')
				zero_cnt++;
			else
				one_cnt++;
			before_ch = ch;
		}
	}
	cout << min(zero_cnt, one_cnt) << endl;
}
