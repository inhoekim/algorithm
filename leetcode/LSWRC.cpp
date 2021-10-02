#include <map>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int p = 0;
        queue<char> q;
        map<char,int> m;
        char ch;
        while(p < s.size()) {
            if(m.find(s[p]) != m.end() && m[s[p]] != 0) {
                do{
                    ch = q.front();
                    q.pop();
                    m[ch]--;
                }while(ch != s[p]);
            }
            m[s[p]] = 1;
            q.push(s[p]);
            int temp = q.size();
            result = max(result, temp);
            p++;
        }
        return result;
    }
};
