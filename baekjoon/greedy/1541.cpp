#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int main(void) {

	stringstream ss; string str;
	cin >> str;
	bool is_open_bracket = false;
	long long ret = 0;
	long long temp = 0;
	for (int i = 0; i < str.size(); i++) {
		//현재 인덱스가 연산자인 case
		if (str[i] == '-' || str[i] == '+') {
			int num = stoi(ss.str());
			ss = stringstream();
			if (str[i] == '-') {
				if (!is_open_bracket) {
					ret += num;
					is_open_bracket = true;
				}
				else {
					ret += (temp + num) * -1;
					temp = 0;
				}
			}
			else if (str[i] == '+' && is_open_bracket)
				temp += num;
			else if (str[i] == '+' && !is_open_bracket)
				ret += num;
		}
		//현재 인덱스가 숫자인 case
		else
			ss << str[i];
	}
	if (is_open_bracket)
		temp += stoi(ss.str());
	else
		ret += stoi(ss.str());
	cout << ret + (temp * -1) << endl;
	//10-10+20-10+20
}
