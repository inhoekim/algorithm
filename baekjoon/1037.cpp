#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int N, result;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++ ){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    if(N % 2 == 0) result = nums[0] * nums.back();
    else result = nums[(N/2)] * nums[(N/2)];

    cout << result << endl;
}
