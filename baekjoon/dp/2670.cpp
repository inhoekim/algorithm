#include <vector>
#include <iostream>

using namespace std;

double dp[10001];
int N;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        double num;
        cin >> num;
        dp[i] = num;
    }
    for (int i = N-2; i >= 0; i--)
        dp[i] = max(dp[i], dp[i + 1] * dp[i]);
    double result = -1;
    for (int i = 0; i < N; i++)
        result = max(result, dp[i]);
    cout << fixed;
    cout.precision(3);
    cout << result << endl;
    return 0;
}
