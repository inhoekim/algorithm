#include <iostream>
#include <sstream>
#include <algorithm>
#define INF 987654321

using namespace std;

int dp[1000001];
int order[1000001];

int make_dp(int num) {
	int &ret = dp[num];
	if (ret != INF)
		return ret;
	if (num % 3 == 0){
		int temp = make_dp(num / 3) + 1;
		if (ret > temp) {
			ret = temp;
			order[num] = num / 3;
		}
	}
	if (num % 2 == 0) {
		int temp = make_dp(num / 2) + 1;
		if (ret > temp) {
			ret = temp;
			order[num] = num / 2;
		}
	}
	int temp = make_dp(num - 1) + 1;
	if (ret > temp) {
		ret = temp;
		order[num] = num - 1;
	}
	return ret;
}

void print_order(int num) {
	stringstream ss;
	ss << num;
	num = order[num];
	while(num >= 1) {
		ss << " " << num;
		num = order[num];
	}
	cout << ss.str() << endl;
}

int main(void) {
	int N;
	cin >> N;
	fill(&dp[0], &dp[1000001], INF);
	dp[0] = 0;
	dp[1] = 0;
	order[1] = 0;
	cout << make_dp(N) << endl;
	print_order(N);
	return 0;
}
