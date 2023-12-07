#include <iostream>
#include <vector>

using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int right_idx = 1;
    for (int i = 0; i < stations.size(); i++) {
        int left_range = stations[i] - w;
        int right_range = stations[i] + w;
        
        if (right_idx < left_range) {
            answer += (left_range - right_idx ) / (2 * w + 1);
            if ((left_range - right_idx) % (2 * w + 1) != 0)
                answer++;
            right_idx = right_range + 1;
        }
        right_idx = right_range + 1;
    }
    if (right_idx <= n) {
        answer += ((n - right_idx) + 1) / (2 * w + 1) ;
        if (((n - right_idx) + 1)% (2 * w + 1) != 0)
            answer++;
    }
    return answer;
}
