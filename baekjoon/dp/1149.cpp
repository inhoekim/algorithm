#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;

typedef enum rgb {
    RED,
    GREEN,
    BLUE
}   e_rgb;

vector<vector<int>> rgbs;
int dp[1001][3];

void make_dp() {
    dp[0][RED] = rgbs[0][RED];
    dp[0][GREEN] = rgbs[0][GREEN];
    dp[0][BLUE] = rgbs[0][BLUE];
    for (int i = 1; i < N; i++) {
        for (int color = 0; color < 3; color++) {
            int other_color_1 = (color + 1) % 3;
            int other_color_2 = (color + 2) % 3;
            dp[i][color] = min(dp[i-1][other_color_1] + rgbs[i][color], dp[i-1][other_color_2] + rgbs[i][color]);
        }
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int red, green, blue;
        cin >> red >> green >> blue;
        rgbs.push_back({red, green, blue});
    }
    make_dp();
    int result = min(dp[N-1][RED], dp[N-1][GREEN]);
    result = min(result, dp[N-1][BLUE]);
    cout << result << endl;
    return 0;
}
