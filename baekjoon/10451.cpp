#include <vector>
#include <iostream>

using namespace std;

void dfs(vector<bool> &visited, vector<bool> &isInStack, vector<int> &p, int curr,int &result) {
    visited[curr] = true;
    isInStack[curr] = true;
    int nextNode = p[curr];
    if (visited[nextNode] == false) dfs(visited,isInStack,p,nextNode, result);
    else if(isInStack[nextNode] == true) result++;
    isInStack[curr] = false;
}
int main() {
    int T;
    cin >> T;
    while(T-- != 0) {
        int result = 0;
        int N;
        cin >> N;
        vector<int> p(N, 0);
        //그래프 만들기
        for(int i = 0; i < N; i++) {
            int temp;
            cin >> temp;
            p[i] = temp - 1;
        }
        vector<bool> visited(N,0);
        vector<bool> isInStack(N,0);
        for(int i = 0; i < visited.size(); i++) {
            if(visited[i] == 0) dfs(visited,isInStack,p,i,result);
        }
        cout << result << endl;
    }
}


