#include <vector>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string s;
    stack<string> stack;
    cin >> s;

    for(int i = 0; i < s.size(); i++) {
        if(s[i] == ')') {
            int innerStrCnt = 0;
            // ')'를 만나면 '('가 나올때까지 stack을 pop시키면서 괄호안의 문자열을 확인
            while(stack.top() != "(") {
                if(stack.top() == "r") {
                    stack.pop(); // "r" pop
                    innerStrCnt += stoi(stack.top());
                    stack.pop(); // realNum 문자열 pop
                }
                else {
                    stack.pop(); // 일반 문자열 pop
                    innerStrCnt++;
                }
            }
            stack.pop(); // '('도 pop 시켜줌
            int repeat = stoi(stack.top());
            stack.pop(); // 반복횟수 K pop 시킴
            stack.push(to_string(repeat * innerStrCnt));
            stack.push("r"); // r 앞에 있는 요소는 realNum으로 취급
        }

        else {
            string temp_s = "";
            temp_s += s[i];
            stack.push(temp_s);
        }
    }

    int result = 0;
    while(!stack.empty()) {
        if(stack.top() == "r") {
            stack.pop();
            result += stoi(stack.top());
        }else {
            result++;
        }
        stack.pop();
    }

    cout << result;
    return 0;
}
