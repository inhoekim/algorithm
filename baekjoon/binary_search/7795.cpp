#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int A, B;
vector<int> As, Bs;

int binary_search(int min_idx, int max_idx, int a_idx) {
    while (min_idx + 1 != max_idx) {
        int temp_idx = (min_idx + max_idx) / 2;
        if (Bs[temp_idx] >= As[a_idx])
            max_idx = temp_idx;
        else
            min_idx = temp_idx;
    }
    return min_idx;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
       cin >> A >> B;
       As.clear();
       Bs.clear();
       for (int i = 0; i < A; i++) {
           int temp;
           cin >> temp;
           As.push_back(temp);
       }
       for (int i = 0; i < B; i++) {
           int temp;
           cin >> temp;
           Bs.push_back(temp);
       }
       sort(As.begin(), As.end());
       sort(Bs.begin(), Bs.end());
       int cnt = 0;
       for (int i = 0; i < A; i++)
           cnt += binary_search(-1, B, i) + 1;
        cout << cnt << endl;
    }
    return 0;
}
