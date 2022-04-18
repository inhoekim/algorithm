#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
vector<vector<char>> map;
vector<pair<int,int>> startPoint;
vector<vector<bool>> visited;
unordered_map<char,int> keys;
int h,w;
int direction[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; //상하좌우순

bool dfs(int currentY, int currentX, int &result) {
    //방문한 정점 체크표시
    visited[currentY][currentX] = true;
    //현재칸에 열쇠 혹은 문서가 있는지 확인
    if(map[currentY][currentX] == '$') {
        result++; //문서획득
        map[currentY][currentX] = '.';
    }
    else if(map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122) {
        char key = map[currentY][currentX];
        keys[key] = 1; //열쇠획득. 새로운 열쇠 획득시 처음 입구에서부터 다시 dfs를 돌려야한다
        map[currentY][currentX] = '.';
        return true;
    }
    //다음칸으로 이동
    for(int i = 0; i < 4; i++) {
        int nextY = currentY + direction[i][0];
        int nextX = currentX + direction[i][1];
        if(nextY < 0 || nextY >= h || nextX < 0 || nextX >= w) continue; //맵밖으로 나간 경우 Pass
        if(visited[nextY][nextX]) continue; //이미 방문한 노드인 경우 Pass
        if(map[nextY][nextX] != '.') {
            if(map[nextY][nextX] == '*') continue; //벽에 막힌 경우 처리
            if(map[nextY][nextX] >= 'A' && map[nextY][nextX] <= 'Z') { //해당 위치가 문인데 열쇠가 없는 경우 Pass
                char lowerCase = map[nextY][nextX] + 32;
                if(keys.find(lowerCase) == keys.end()) continue;
            }
        }

        if(dfs(nextY,nextX, result)) return true; //dfs 도중 새로운 열쇠를 획득한 적 있는 경우. 새롭게 dfs를 시작해야하므로 즉시 return해서 탐색을 종료.

    }
    return false;
}

int main(){
    int T;
    cin >> T;
    while(T-- != 0) {
        //맵등록
        cin >> h >> w;
        map = vector<vector<char>> (h, vector<char>(w,'*'));
        startPoint = vector<pair<int,int>>();
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                cin >> map[i][j] ;
            }
        }
        //key를 hashTable(keys)에 등록
        string keyString;
        cin >> keyString;
        if(keyString == "0") keyString = "";
        keys = unordered_map<char,int>();
        for(int i = 0; i < keyString.size(); i++) keys[keyString[i]] = 1;

        int result = 0;
        bool isNewKey = true;
        while(isNewKey) {
            visited = vector<vector<bool>>(h, vector<bool>(w, false));
            isNewKey = false;
            //스타트포인트를 찾기위해 전체 맵을 1번 순회
            for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                    //dfs를 돌릴 수 있는 시작점(startPoint)을 등록
                    if((i == 0 || i == h-1 || j == 0 || j == w-1) && map[i][j] != '*') {
                        if(map[i][j] >= 'A' && map[i][j] <= 'Z') {
                            char lowerCase = map[i][j] + 32;
                            if(keys.find(lowerCase) == keys.end()) continue;
                        }
                        startPoint.push_back(pair<int,int>(i,j));
                    }
                }
            }
            //dfs시작
            for(int i = 0; i < startPoint.size(); i++) {
                //아직 방문하지 않은 스타트포인트부터 방문하면서 DFS를 시작
                if(visited[startPoint[i].first][startPoint[i].second] == false ) {
                    isNewKey = dfs(startPoint[i].first, startPoint[i].second, result);
                }
                if(isNewKey) break;
            }
        }
        cout << result << endl;
    }
    return 0;
}


