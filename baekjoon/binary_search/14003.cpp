#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> A;

int make_sequence(vector<int> &order) {
    vector<int> sequence = {1000000001};
    for (int i = 0; i < A.size(); i++) {
        vector<int>::iterator iter = lower_bound(sequence.begin(), sequence.end(), A[i]);
        if (iter == sequence.end()) {
            sequence.push_back(A[i]);
            order.push_back(sequence.size() - 1);
        }
        else {
            *iter = A[i];
            order.push_back(iter - sequence.begin());
        }
    }
    return sequence.size();
}

void print_order(vector<int> &order, int target_idx) {
    vector<int> result_order;
    for (int i = order.size() - 1; i >= 0; i--) {
        if (order[i] == target_idx) {
            result_order.push_back(A[i]);
            target_idx--;
        }
    }
    for (int i = result_order.size() - 1; i >= 0; i--) {
        if (i == 0)
            cout << result_order[i];
        else
            cout << result_order[i] << " ";
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        A.push_back(num);
    }
    vector<int> order;
    int result_len = make_sequence(order);
    cout << result_len << endl;
    print_order(order, result_len - 1);
    return 0;
}
