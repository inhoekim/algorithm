#include <algorithm>
#include <vector>
#include <iostream>
​
using namespace std;
​
int N,M;
vector<int> lectures;
​
int get_result(int min_len, int max_len) {
    while (min_len != max_len) {
        int temp_result = (min_len + max_len) / 2;
        int time_sum = 0;
        int used_bluray = 1;
        for (int i = 0; i < lectures.size(); i++) {
            if (lectures[i] > temp_result) {
                used_bluray = -1;
                break;
            }
            if (time_sum + lectures[i] <= temp_result)
                time_sum += lectures[i];
            else {
                used_bluray++;
                time_sum = lectures[i];
            }
        }
        if (used_bluray == -1 || used_bluray > M)
            min_len = temp_result + 1;
        else
            max_len = temp_result;
    }
    return min_len;
}
​
int main() {
    cin >> N >> M;
​
    int max_len = 0;
    for (int i = 0; i < N; i++) {
        int lecture_time;
        cin >> lecture_time;
        lectures.push_back(lecture_time);
        max_len += lecture_time;
    }
    cout << get_result(lectures[0], max_len) << endl;
    return 0;
}
