#include <algorithm>
#include <iostream>
#define PIE_1E3 (360*1e3)
using namespace std;

void proc_one_sec(long long time, int &answer, long long end_sec) {
    long long h_angle = (long long)((time / 120.0) * 1e3) % (long long)PIE_1E3;
    long long m_angle = (long long)((time / 10.0) * 1e3) % (long long)PIE_1E3;
    long long s_angle = (long long)(time * 6 * 1e3) % (long long)PIE_1E3;
    time++;
    long long nh_angle = (long long)((time / 120.0) * 1e3) % (long long)PIE_1E3;
    long long nm_angle = (long long)((time / 10.0) * 1e3) % (long long)PIE_1E3;
    long long ns_angle = (long long)(time * 6 * 1e3) % (long long)PIE_1E3;

    nh_angle = (nh_angle == 0) ? (long long)PIE_1E3 : nh_angle;
    nm_angle = (nm_angle == 0) ? (long long)PIE_1E3 : nm_angle;
    ns_angle = (ns_angle == 0) ? (long long)PIE_1E3 : ns_angle;

    if ((s_angle <= h_angle && nh_angle < ns_angle))
        answer++;
    if (s_angle <= m_angle && nm_angle < ns_angle)
        answer++;
    if (time - 1 == 12 * 3600LL || time - 1 == 0)
        answer--;
    if (time == end_sec) {
        if (ns_angle == nh_angle)
            answer++;
        if (ns_angle == nm_angle)
            answer++;
        if (time == 12 * 3600LL || time == 0)
            answer--;
    }
}

int solution(int h1, int m1, int s1, int h2, int m2, int s2) {
    long long start_sec = (h1 * 60LL * 60LL) + (m1 * 60LL) + s1;
    long long end_sec = (h2 * 60LL * 60LL) + (m2 * 60LL) + s2;
    int answer = 0;
    while(start_sec < end_sec)
        proc_one_sec(start_sec++, answer, end_sec);
    return answer;
}

int main(void) {
    solution(	11, 59, 30, 12, 0, 0);
}
