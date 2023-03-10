#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int K;

bool compare(vector<int> &a, vector<int> &b) {
    if(a[0] > b[0]) return true;
    else if(a[0] == b[0]){
        if(a[1] > b[1]) return true;
        else if(a[1] == b[1]) {
            if(a[2] > b[2]) return true;
            else if(a[2] == b[2]) {
                if(a[3] == K) return true;
            }
        }
    }
    return false;
}

int main(){
    int N;
    cin >> N >> K;
    K--;
    vector<vector<int>> list(N);
    for(int i = 0; i < N; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        list[a] = {b, c, d, a};
    }
    sort(list.begin(), list.end(), compare);
    int ranking = 1;
    for(vector<int> l : list) {
        if (l[3] == K) break;
        ranking++ ;
    }
    cout << ranking << endl;
}
