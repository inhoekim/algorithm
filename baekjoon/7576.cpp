#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int main() {
    int M,N;
    cin >> M >> N;
    vector<vector<int>> box(N,vector<int>(M,0));
    queue<pair<int,int>> today, tommorw;
    int result = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> box[i][j];
            //만약 현재 입력받은 값이 익은 토마토(value = 1)인 경우 today Queue에 등록
            if(box[i][j] == 1) today.push(pair<int,int>(i,j));
        }
    }
    int direction[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; //상하좌우
    //BFS >> 더이상 방문해야할 노드가 없을 때까지 탐색을 수행
    while(!today.empty() || !tommorw.empty()) {
        //더이상 오늘 방문할 노드가 존재하지 않을 경우 다음날로 진행
        if(today.empty()) {
            today = tommorw;
            tommorw = queue<pair<int,int>>();
            result++;
            continue;
        }
        //해당 라인부터는 Today Queue의 노드들을 방문하는 로직
        pair<int,int> curr_tomato = today.front();
        today.pop();
        for(int i = 0; i < 4; i++) {
            int nextY= curr_tomato.first + direction[i][0];
            int nextX = curr_tomato.second + direction[i][1];
            if(nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) continue; //맵을 벗어나는 경우
            if(box[nextY][nextX] == -1) continue; //해당 위치에 토마토가 존재하지 않는 경우(벽이라고 생각)
            if(box[nextY][nextX] == 1) continue; //이미 익은 토마토인 경우
            //발견한 노드가 위 3가지 if 조건에 모두 해당하지 않는 경우는 익지 않은 토마토인 경우뿐이므로 tommrow Queue에 등록하고 map도 변경해준다
            box[nextY][nextX] = 1;
            tommorw.push(pair<int,int>(nextY,nextX));
        }
    }
    //모든 턴을 수행한 후에 맵에 익지않은 토마토가 존재하는 지 검사. 만약 존재한다면 -1를 return
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(box[i][j] == 0) {
                result = -1;
                break;
            }
        }
    }

    cout << result;
    return 0;
}
