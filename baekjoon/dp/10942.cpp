#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<char>> dp;
vector<int> nums;

char check_palindrome(int left_idx, int right_idx) {
    char &ret = dp[left_idx][right_idx];
    if (ret != 0)
        return ret;
    if (left_idx >= right_idx)
        return ret = '1';
    if (nums[left_idx] != nums[right_idx])
        return ret = '0';
    ret = check_palindrome(left_idx + 1, right_idx -1);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    cin >> M;
    dp = vector<vector<char>>(N, vector<char>(N, 0));
    stringstream ss;
    for (int i = 0; i < M; i++) {
        int left_ptr, right_ptr;
        cin >> left_ptr >> right_ptr;
        if (dp[left_ptr - 1][right_ptr - 1] == 0)
            check_palindrome(left_ptr - 1, right_ptr - 1);
        ss << dp[left_ptr - 1][right_ptr - 1] << '\n';
    }
    cout << ss.str();
    return 0;
}
