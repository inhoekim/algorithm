#include <string>
#include <stack>
#include <sstream>

using namespace std;

int split_str(string &p) {
    stack<char> st;
    int iter = 0;
    st.push(p[iter++]);
    while (!st.empty()) {
        if (st.top() == p[iter])
            st.push(p[iter++]);
        else {
            st.pop();
            iter++;   
        }
    }
    return iter;
}

void reverse_bracket(string &str) {
    int size = str.size();
    for (int i = 0; i < size; i++) {
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == ')')
            str[i] = '(';
    }
}

string make_answer(string answer) {
    if (answer == "")
        return "";
    
    stringstream ss;
    int split_point = split_str(answer);

    if (answer[0] == '(') {
        ss << answer.substr(0, split_point);
        ss << make_answer(answer.substr(split_point));
    }
    else {
        ss << '(';
        ss << make_answer(answer.substr(split_point));
        ss << ')';
        string rule4_str = answer.substr(1, split_point - 2);
        reverse_bracket(rule4_str);
        ss << rule4_str;
    }
    return ss.str();
}

string solution(string p) {
    string answer = make_answer(p);
    return answer;
}
