#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

char map[12][6] = {};
//상하좌우
int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int dfs(int y, int x, char c, vector<pair<int,int>> &list, bool (*visited) [6]) {
    int num = 0;
    visited[y][x] = true;
    if(map[y][x] == c) num++;
    else return num;
    list.push_back(pair(y,x));
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 || nx > 5 || ny < 0 || ny > 11) continue;
        if(!visited[ny][nx]) num += dfs(ny,nx,c,list, visited);
    }
    return num;
}

void change_map() {
    for(int x = 0; x < 6; x++)  {
        int fallCnt = 0;
        for(int y = 11; y > -1; y--) {
            if(map[y][x] == '.') fallCnt++;
            else {
                int fall_y = y + fallCnt;
                map[fall_y][x] = map[y][x];
                if(fall_y != y) {
                    map[y][x] = '.';
                }
            }
        }
    }
}

int check_chain() {
    int result = -1;
    bool chain = true;
    while(chain) {
        change_map();
        result++;
        chain = false;
        for(int y = 0; y < 12; y++) {
            for(int x = 0; x < 6; x++) {
                if (map[y][x] == '.') continue;
                vector<pair<int,int>> list;
                bool visited[12][6] = {false};
                int num = dfs(y,x,map[y][x], list, visited);
                if(num >= 4) {
                    for(pair<int,int> p : list) {
                        map[p.first][p.second] = '.';
                    }
                    chain = true;
                }
            }
        }
    }
    return result;
}

int main(){
    for(int y = 0; y < 12; y++) {
        for(int x = 0; x < 6; x++) {
            cin >> map[y][x] ;
        }
    }
    int result = check_chain();
    cout << result << endl;
    return 0;
}
