#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;
int const INF = 987654321;

class Solution {
public:
    int dp[1000][1000];
    string longestPalindrome(string s) {
        string result;
        fill(&dp[0][0],&dp[999][1000],-INF);

        for(int start = 0; start < s.size(); start++) {
            for(int end = s.size()-1 ; end >= 0; end--) {
                if(start > end) continue;
                if(dp[start][end] >= 0) continue;
                recul(start, end , s);
            }
        }
        int top_x = 0;
        int top_y = 0;
        int top = -INF;
        for(int x = 0; x < s.size(); x++) {
            for(int y = 0; y < s.size(); y++) {
                if(dp[x][y] > top)  {
                    top_x = x;
                    top_y = y;
                    top = dp[x][y];
                }
            }
        }
        result = s.substr(top_x, top_y - top_x + 1);
        return result;
    }

   int recul(int start, int end, string &s) {

       //memoization
       if(dp[start][end] > 0) return dp[start][end];
       if(dp[start][end] == 0) return -INF;
       //base case
       if (start == end ) {
           dp[start][end] = 1;
           return dp[start][end];
       }
       //no palindrome case
       if(s[start] != s[end]) {
           dp[start][end] = 0;
           return -INF;
       }
       //likely palindrome case
       if(end - start == 1) {
           dp[start][end] = 2;
           return dp[start][end];
       }
       int next = recul(start + 1, end - 1, s);
       if(next < 0) {
           dp[start][end] = 0;
           return -INF;
       }
       dp[start][end] = next + 2;
       return dp[start][end];
       }
};

int main(){
    Solution *s = new Solution();
    string result = s->longestPalindrome("abbba");
    cout << result << endl;
    return 0;
}
