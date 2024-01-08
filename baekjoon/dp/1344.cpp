#include <iostream>
#include <cmath>

using namespace std;

const int PRIMES[7] = {2, 3, 5, 7, 11, 13, 17};
double comb[10];

void make_comb() {
    comb[0] = 1;
    comb[1] = 18;
    for (int i = 2; i < 10; i++)
        comb[i] = (comb[i - 1] / i) * (19 - i);
}

double get_prime_rate(double win_rate) {
    double ret = 0;
    for(int i = 0; i < 7; i++) {
        int win_cnt = PRIMES[i];
        if (win_cnt > 9)
            win_cnt = 9 - (PRIMES[i] % 9);
        ret += comb[win_cnt] * pow(win_rate, PRIMES[i]) * pow(1 - win_rate, 18 - PRIMES[i]);
    }
    return ret;
}

int main(void) {
    double a, b;
    cin >> a >> b;
    make_comb();
    double prime_goal_rate_a = get_prime_rate(a / 100.0);
    double prime_goal_rate_b = get_prime_rate(b / 100.0);
    cout << fixed;
    cout.precision(15);
    cout << (1 - ((1 - prime_goal_rate_a) * (1 - prime_goal_rate_b))) << endl;
    return 0;
}
