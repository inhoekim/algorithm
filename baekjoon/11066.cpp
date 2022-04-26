#include <vector>
#include <iostream>

using namespace std;

long long dp [500][500];
int files [500];
long long sum[500] = {0};

long long mergeFile(int front, int end) {
    if(end == front) return 0;
    if(end - front == 1) return dp[front][end] = files[front] + files[end];
    if(dp[front][end] != 0) return dp[front][end];
    // first temp is INF
    long long temp = 9876543219876543;
    for(int i = 0; i < end - front; i++) {
        if (front == 0) {
            temp = min(temp,mergeFile(front, front + i) + mergeFile(front + i + 1, end) + sum[end]);
        } else if (front != 0){
            temp = min(temp,mergeFile(front, front + i) + mergeFile(front + i + 1, end) + sum[end] - sum[front - 1]);
        }
        dp[front][end] = temp;
    }
    return dp[front][end];

}

int main(){
    int T;
    cin >> T;
    while(T-- != 0) {
        int K;
        cin >> K;
        for(int i = 0; i < K; i++) {
            cin >> files[i];
            if(i == 0) sum[0] = files[0];
            else sum[i] = sum[i-1] + files[i];
        }
        fill(&dp[0][0], &dp[499][500], 0);
        mergeFile(0,K - 1);
        cout << dp[0][K-1] << endl;
    }
    return 0;
}


