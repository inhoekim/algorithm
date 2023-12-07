#include <string>
#include <algorithm>

using namespace std;

int get_num_length(int num) {
    if (num == 1)
        return 0;
    int ret = 1;
    while (num / 10) {
        ret++;
        num /= 10;   
    }
    return ret;
}

int get_compress_length(const string &s, int n) {
    int ret = 0;
    string curr_pattern(s.begin(), s.begin() + n);
    int curr_size = curr_pattern.size();
    int compression_cnt = 1;
    string remain_str(s.begin() + n, s.end());
    /* 문자열을 균등하게 자르지 못하는 n */
    if (remain_str.size() < n)
        return s.size();
    /* n 사이즈 만큼 문자열을 계속 잘라가면서 탐색 */
    while (true) {
        int pattern_flag = true;
        /* 현재 패턴으로 압축이 가능한지 check*/
        for(int i = 0; i < n; i++) {
            if (!(curr_pattern.at(i) == remain_str.at(i))) {
                pattern_flag = false;
                break;
            }
        }
        /* 압축 가능한 경우 - 압축횟수 cnt++ */
        if (pattern_flag)
            compression_cnt++;
        /* 압축 불가능한 경우 - 지금까지 압축했던 문자를 ret 길이에 더한 뒤 패턴변경 */
        else { 
            ret += get_num_length(compression_cnt) + n;
            curr_pattern = remain_str.substr(0, n);
            compression_cnt = 1;
        }
        remain_str = remain_str.substr(n);
        /* 문자열을 다 소모한 경우 */
        if (remain_str.size() == 0)
            return ret += get_num_length(compression_cnt) + n;
        /* 문자열을 n사이즈 만큼 더이상 자를 수 없는 경우 */
        else if (remain_str.size() < n)
            return ret += get_num_length(compression_cnt) + n + remain_str.size();
    }
}

int solution(string s) {
    int answer = s.size();
    int max_range = (answer / 2) + 1;
    for (int split_cnt = 1; split_cnt <= max_range; split_cnt++)
        answer = min(answer, get_compress_length(s, split_cnt));    
    return answer;
}
