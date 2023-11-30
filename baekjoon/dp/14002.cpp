#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int N;
vector<int> nums;
vector<int> sequence = {10000};
vector<int> idx_sequence;

void make_sequence(void) {
    for (int i = 0; i < N; i++) {
        if (nums[i] > sequence.back()) {
            sequence.push_back(nums[i]);
            idx_sequence.push_back(sequence.size() - 1);
        }
        else {
            vector<int>::iterator iter = lower_bound(sequence.begin(), sequence.end(), nums[i]);
            *iter = nums[i];
            idx_sequence.push_back(iter - sequence.begin());
        }
    }
}

void print_sequence(void) {
    deque<int> dq;
    int curr_target = sequence.size() - 1;
    for (int i = N-1; i >= 0; i--) {
        if (idx_sequence[i] == curr_target) {
            dq.push_front(nums[i]);
            curr_target--;
        }
    }
    cout << dq.front();
    dq.pop_front();
    while (!dq.empty()) {
        cout << " " << dq.front();
        dq.pop_front();
    }
    cout << endl;
}

int main(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    make_sequence();
    cout << sequence.size() << endl;
    print_sequence();
}
