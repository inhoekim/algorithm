#include <algorithm>
#include <vector>
#include <iostream>
​
using namespace std;
​
int N,M;
vector<int> gems;
​
int get_result(int min_len, int max_len) {
    while (min_len != max_len) {
        int temp_result = (min_len + max_len) / 2;
        int received_human = 0;
        for (int i = 0; i < gems.size(); i++) {
            received_human += gems[i] / temp_result;
            if (gems[i] % temp_result)
                received_human++;
        }
        if (received_human <= N)
            max_len = temp_result;
        else
            min_len = temp_result + 1;
    }
    return min_len;
}
​
int main() {
    cin >> N >> M;
    int max_len = 0;
​
    for (int i = 0; i < M; i++) {
        int cnt;
        cin >> cnt;
        gems.push_back(cnt);
        max_len = max(max_len, cnt);
    }
    cout << get_result(1, max_len) << endl;
    return 0;
}
