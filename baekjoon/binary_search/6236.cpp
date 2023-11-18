#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int N,M;
vector<int> plan;

int get_result(int min_len, int max_len) {

    while (min_len != max_len) {
        int temp_result = (min_len + max_len) / 2;
        int cnt = 1;
        int remain_money = temp_result;
        for (int i = 0; i < plan.size(); i++) {
            if (remain_money - plan[i] < 0) {
                cnt++;
                remain_money = temp_result - plan[i];
            }
            else {
                remain_money -= plan[i];
            }
        }
        if (cnt <= M)
            max_len = temp_result;
        else
            min_len = temp_result + 1;
    }
    return min_len;
}

int main() {
    cin >> N >> M;
    int max_element = -1;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        plan.push_back(tmp);
        max_element = max(max_element, tmp);
        sum += tmp;
    }
    cout << get_result(max_element, sum) << endl;
    return 0;
}
