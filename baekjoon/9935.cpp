#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string input1, input2;
    cin >> input1 >> input2;
    stack<char> st;
    int pointer = 0;
    string temp;
    for(int i = 0; i < input1.length(); i++) {
        if (input1[i] == input2[pointer]) {
            //문자열 폭발발생
            if(pointer + 1 == input2.length()) {
                //폭발 이후에는 스택에서 가장 최근 단어들을 꺼내와 새롭게 다시 검사하는 과정을 거쳐야한다
                //문자열 폭발이 실패했을때 뒤에 몇개까지 일치했는지 숫자를 적어놓고 그 숫자를 pointer가 가져오는 식으로 해결하면 될 것같음..
                int n = 0;
                while(!st.empty() && st.top() == '!') {
                    n++;
                    st.pop();
                }
                temp = "";
                for(int j = 0; j < n; j++) {
                    temp += st.top();
                    st.pop();
                }
                reverse(temp.begin(), temp.end());
                pointer = n;
                if(pointer == 0) {
                    temp = "";
                }
                continue;
            }
            //문자열 폭발이 아직 미발생된 상태이지만 가능성이 존재하는 Case
            temp += input1[i];
            pointer++;
        }
        //문자열 폭발이 발생하지 않는게 확정된 Case
        else {
            for(int j = 0; j < temp.length(); j++) {
                st.push(temp[j]);
            }
            //현재 바라보고있는 글자를 대상으로 처음부터 다시 검사 시작
            if(input1[i] == input2[0]) {
                for(int j = 0; j < temp.length(); j++) {
                    st.push('!');
                }
                pointer = 1;
                temp = input1[i];
            }
            else{
                st.push(input1[i]);
                temp = "";
                pointer = 0;
            }
        }
    }
    int num = st.size();
    if (num == 0) {
        cout << "FRULA" << endl;
        return 0;
    }
    string result;
    for(int i = 0; i < num; i++) {
        result += st.top();
        st.pop();
    }
    reverse(result.begin(), result.end());
    result.erase(remove(result.begin(),result.end(),'!'), result.end());
    cout << result + temp << endl;
    return 0;

}
