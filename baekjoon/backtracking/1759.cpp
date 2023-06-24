#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

stringstream ss;
vector<char> chars;
vector<char> picked;

int l, c;

void pick_chars(int idx, int a, int b) {
	if (picked.size() == l) {
		if (a >= 1 && b >= 2) {
			for (int i = 0; i < picked.size(); i++)
				ss << picked[i];
			ss << endl;
		}
		return;
	}
	for (int i = idx; i < c; i++) {
		picked.push_back(chars[i]);
		if (chars[i] == 'a' || chars[i] == 'e' || chars[i] == 'i'
		|| chars[i] == 'o' || chars[i] == 'u')
			pick_chars(i + 1, a + 1, b);
		else
			pick_chars(i + 1, a, b + 1);
		picked.pop_back();
	}
}

int main(void) {
	cin >> l >> c;
	chars = vector<char>(c);
	for (int i = 0; i < c; i++)
		cin >> chars[i];
	sort(chars.begin(), chars.end());
	pick_chars(0, 0, 0);
	cout << ss.str();
}
