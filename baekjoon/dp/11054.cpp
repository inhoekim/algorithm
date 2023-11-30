#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int dp[1001][2];
int N;
vector<int> nums;

/* dp[idx][0] = idx번 위치를 마지막 원소로 하는 오름차순 LIS 길이 */
void make_dp_ascending() {
    for (int i = 1; i < N; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (nums[i] > nums[j])
                dp[i][0] = max(dp[i][0], dp[j][0] + 1);
        }
    }
}

/* dp[idx][1] = idx번 위치를 첫번째 원소로 하는 내림차순 LIS 길이 */
void make_dp_descending(){
    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            if (nums[i] > nums[j])
                dp[i][1] = max(dp[i][1], dp[j][1] + 1);
        }
    }
}

int main(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    fill(&dp[0][0], &dp[1000][2], 1);
    make_dp_ascending();
    make_dp_descending();
    int result = -1;
    for (int i = 0; i < N; i++) {
        result = max(result, dp[i][0] + dp[i][1] - 1);
    }
    cout << result << endl;
}
