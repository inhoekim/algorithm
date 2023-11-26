#include <iostream>
#include <vector>
#include <algorithm>
#define VAL second

using namespace std;
​
vector<pair<int, int>> lines;
​
int get_lis(int size) {
    int dp[size];
    fill(&dp[0], &dp[size], 1);
    for (int i = size - 1; i >= 0; i--) {
        for (int j = i + 1; j < size; j++) {
            if (lines[i].VAL < lines[j].VAL) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int lis = -1;
    for (int i = 0; i < size; i++)
        lis = max(lis, dp[i]);
    return lis;
}
​
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        lines.push_back({a, b});
    }
    sort(lines.begin(), lines.end());
    cout << n - get_lis(n) << endl;
    return 0;
}
