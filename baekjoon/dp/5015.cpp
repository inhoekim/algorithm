#include <iostream>
#include <algorithm>
#define OK 1
#define NO 0
using namespace std;

string pattern;
int dp[101][101];

int check_word(string &word, int p_idx, int w_idx) {
	if (p_idx == pattern.size() && w_idx == word.size())
		return (OK);
	//패턴이 전부 소모 되었으나(p_idx == pattern.size()에 도달한경우) 워드가 다 소모되지 않았으면 무조건 실패
	//워드가 전부 소모된 경우(w_idx == word.size()에 도달한 경우)는 남은 패턴이 '*'이면 성공할 수도 있음
	//따라서 검사를 계속 진행해야함. 검사를 진행하면서 w_idx가 word.size()보다 커지는 경우는 말이 안되는 상횡이므로 전부 NO로 귀결되게함.
	if ((p_idx == pattern.size() && w_idx < word.size()) || w_idx > word.size())
		return (NO);
	if (dp[p_idx][w_idx] != -1)
		return (dp[p_idx][w_idx]);
	if (pattern[p_idx] != '*' && (pattern[p_idx] == '?' || pattern[p_idx] == word[w_idx]))
		dp[p_idx][w_idx] = check_word(word, p_idx + 1, w_idx + 1);
	else if (pattern[p_idx] == '*')
		if (check_word(word, p_idx + 1, w_idx) == OK || check_word(word, p_idx, w_idx + 1) == OK)
			dp[p_idx][w_idx] = OK;
	else
		dp[p_idx][w_idx] = NO;
	return (dp[p_idx][w_idx]);
}

int main(void) {
	cin >> pattern;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string word;
		cin >> word;
		fill(&dp[0][0], &dp[100][101], -1);
		check_word(word, 0, 0);
		if (dp[0][0] == OK)
			cout << word << endl;
	}
}
