#include <vector>
#include <iostream>
#include <cmath>
#define ll unsigned long long

using namespace std;

int N, M;
vector<int> times;

 ll binary_search(ll min_time, ll max_time) {
    if (N <= M)
        return 0;
    while (min_time != max_time) {
        ll target_order = M;
        ll temp_result = (ll)ceil(min_time / 2.0 + max_time / 2.0);
        for(int i = 0; i < M; i++)
           target_order += temp_result / times[i];
        if (target_order >= N)
            max_time = temp_result - 1;
        else if (target_order < N)
            min_time = temp_result;
    }
    return min_time;
}

int get_order(ll target_time) {
     int order = M;
     vector<int> recently_used_idx;
     for (int i = 0; i < M; i++) {
         order += target_time / times[i];
         if ((target_time + 1) % times[i] == 0)
             recently_used_idx.push_back(i + 1);
     }
     int last_idx = N - order;
     return recently_used_idx[last_idx - 1];
 }

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int time;
        cin >> time;
        times.push_back(time);
    }
    ll target_time = binary_search(1, -1);
    if (target_time == 0)
        cout << N << endl;
    else
        cout << get_order(target_time) << endl;
    return 0;
}
