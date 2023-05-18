#include <iostream>
#include <algorithm>

using namespace std;

int a, b, c;

long long recur(int base, int power) {
	if (power == 1)
		return (base % c);
	long long ret = recur(base, power / 2);
	//지수가 짝수인 경우
	if (power % 2 == 0)
		return (ret * ret % c);
	//지수가 홀수인 경우
	else
		return ((ret * ret) % c * base % c);
}

int main(void) {
	cin >> a >> b >> c;
	cout << recur(a, b) << endl;
}
