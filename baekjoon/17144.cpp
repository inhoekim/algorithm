#include <vector>
#include <iostream>

using namespace std;

int main() {
    //초기화 작업
    int r,c,t;
    cin >> r >> c >> t;
    vector<vector<int>> direction = {{-1,0},{0,1}, {1,0}, {0,-1}}; //상,우,하,좌 순(시계방향)
    vector<vector<int>> direction_r = {{1,0},{0,1}, {-1,0}, {0,-1}}; //하,우,상,좌 순(반시계방향)
    vector<vector<int>> map(r,vector<int>(c,0));
    vector<vector<int>> tempMap(r,vector<int>(c,0));
    int machineTop = -1, machineBottom = -1;  //공기청정기 윗부분,아랫부분 row 좌표 저장
    for(int y = 0; y < r; y++) {
        for(int x = 0; x < c; x++) {
            int temp;
            cin >> temp;
            map[y][x] = temp;
            tempMap[y][x] = temp;
            if(temp == -1) {
                if(machineTop == -1) machineTop = y;
                else machineBottom = y;
            }
        }
    }
    //루프시작
    for(int i = 0; i < t; i++) {
        tempMap = map;
        //미세먼지 확산단계
        for(int y = 0; y < r; y++) {
            for(int x = 0; x < c; x++) {
                if(map[y][x] != 0 || map[y][x] != -1) {
                    int amount = map[y][x] / 5; // 확산되는 미세먼지 양
                    int cnt = 0; // 확산횟수
                    for(int i = 0; i < 4; i++) {
                        int nextY = y + direction[i][0];
                        int nextX = x + direction[i][1];
                        //맵밖으로 나가지는 경우 continue
                        if((nextX < 0 || nextX >= c) || (nextY < 0 || nextY >= r)) continue;
                        //공기청정기 좌표인 경우 continue
                        if(nextX == 0 && (nextY == machineTop || nextY == machineBottom)) continue;
                        tempMap[nextY][nextX] += amount;
                        cnt++;
                    }
                    tempMap[y][x] -= amount * cnt;
                }
            }
        }
        map = tempMap;
        //공기청정기 윗부분
        int currentY = machineTop - 1, currentX = 0;
        int level = 0;
        while(true) {
            int previousY = currentY + direction[level][0];
            int previousX = currentX + direction[level][1];
            //방향전환이 필요한 경우
            if((previousX < 0 || previousX >= c) || (previousY < 0 || previousY > machineTop)) {
                level++;
                previousY = currentY + direction[level][0];
                previousX = currentX + direction[level][1];
            }
            if(map[previousY][previousX] != -1) {
                map[currentY][currentX] = map[previousY][previousX];
                currentX = previousX;
                currentY = previousY;
            }
            //이전칸이 공기청정기인 경우, 모든 칸을 전부 다 옮겼으므로 break
            else {
                map[currentY][currentX] = 0;
                break;
            }
        }
        //공기청정기 아랫부분
        currentY = machineBottom + 1, currentX = 0;
        level = 0;
        while(true){
            int previousY = currentY + direction_r[level][0];
            int previousX = currentX + direction_r[level][1];
            //방향전환이 필요한 경우
            if((previousX < 0 || previousX >= c) || (previousY < machineBottom || previousY >= r)) {
                level++;
                previousY = currentY + direction_r[level][0];
                previousX = currentX + direction_r[level][1];
            }
            if(map[previousY][previousX] != -1) {
                map[currentY][currentX] = map[previousY][previousX];
                currentX = previousX;
                currentY = previousY;
            }
                //이전칸이 공기청정기인 경우, 모든 칸을 전부 다 옮겼으므로 break
            else {
                map[currentY][currentX] = 0;
                break;
            }
        }
    }
    //정답 출력
    int result = 0;
    for(int y = 0; y < r; y++) {
        for(int x = 0; x < c; x++) {
            result += map[y][x];
        }
    }
    cout << result + 2 << endl;
    return 0;

}
