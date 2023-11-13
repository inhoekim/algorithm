#include <algorithm>
#include <vector>
#include <iostream>
#define FORWARD 0
#define REVERSE 1

using namespace std;

int N,M,T;
vector<vector<int>> disk;
int visited[51][51];
int direction[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
int zero_count;
int total_zero_cnt;

int cal_result() {
    int result = 0;
    for (int n = 0; n < N; n++)
        for (int m = 0; m < M; m++)
            result += disk[n][m];
    return result;
}

void organize_element(int n, int m, int element){
    visited[n][m] = 1;
    for (int i = 0; i < 4; i++) {
        int next_n = n + direction[i][0];
        int next_m = m + direction[i][1];
        if (next_n < 0 || next_n == N)
            continue;
        if (next_m < 0)
            next_m = M - 1;
        else if (next_m == M)
            next_m = 0;
        if (visited[next_n][next_m])
            continue;
        if (disk[next_n][next_m] == element) {
            zero_count++;
            if (disk[n][m] == element)
                zero_count++;
            disk[n][m] = 0;
            disk[next_n][next_m] = 0;
            organize_element(next_n, next_m, element);
        }
    }
}

void ordering_disk() {
    double avg = (double)cal_result() / (N * M - total_zero_cnt);
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            if (disk[n][m] == 0)
                continue;
            if (disk[n][m] < avg)
                disk[n][m]++;
            else if (disk[n][m] > avg)
                disk[n][m]--;
        }
    }
}

void rotate_track(int x, int d, int k) {
    for (int idx = 1; idx <= N; idx++) {
        if (idx % x != 0)
            continue;
        if (d == FORWARD)
            rotate(disk[idx - 1].begin(), disk[idx - 1].end() - k, disk[idx - 1].end());
        else if (d == REVERSE)
            rotate(disk[idx - 1].begin(), disk[idx - 1].begin() + k, disk[idx - 1].end());
    }
    zero_count = 0;
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            if (!visited[n][m] && disk[n][m] != 0)
                organize_element(n, m, disk[n][m]);
        }
    }
    if (zero_count == 0)
        ordering_disk();
    total_zero_cnt += zero_count;
}

int main() {
    cin >> N >> M >> T;
    disk = vector(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> disk[i][j];
    for (int i = 0; i < T; i++) {
        int x, d, k;
        cin >> x >> d >> k;
        fill(&visited[0][0], &visited[N - 1][M], 0);
        rotate_track(x, d, k);
    }
    cout << cal_result() << endl;
    return 0;
}
