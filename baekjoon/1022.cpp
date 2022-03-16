#include <vector>
#include <iostream>

using namespace std;

int main() {
    int r1,c1,r2,c2;
    cin >> r1 >> c1 >> r2 >> c2;
    vector<vector<int>> resultMap(r2-r1+1, vector<int>(c2-c1+1));
    int totalCoorNum = (r2-r1+1) * (c2-c1+1);
    int currentNum = 0, currentRow= 0, currentCol = 0;
    int discovered = 0, pattern = 0;
    int level = 1;  // level == 현재 패턴의 이동횟수 레벨. 패턴 변동시 remainedMoveCnt가 level 값에 맞게 충전됨.
    int remainedMoveCnt = 1; // remainedMoveCnt == 해당 패턴으로 이동해야하는 횟수. 0이 될시 패턴(방향) 변경
    int space = 0;


    int direction [4][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}}; //우상좌하 순
    // 0,0 좌표부터 소용돌이를 그려가기 시작한다(무한루프로 돌림)
    // 루프를 돌면서 result로 반환해야하는 좌표를 지날때마다 resultMap에 좌표에 해당하는 값을 저장하고 discovered를 +1 증가시킨다. 발견해야하는 모든 좌표의 수에 discovered가 도달할 경우 루프를 종료시킨다.
    while(discovered != totalCoorNum) {
        currentNum++;
        if((r1 <= currentRow && currentRow <= r2) && (c1 <= currentCol && currentCol <= c2)) {
            discovered++;
            resultMap[currentRow-r1][currentCol-c1] = currentNum;
            int temp = currentNum / 10;
            int tempSpace = 0;
            while(temp != 0) {
                tempSpace++;
                temp /= 10;
            }
            if(tempSpace > space) space = tempSpace;
        }

        currentRow += direction[pattern][0];
        currentCol += direction[pattern][1];

        remainedMoveCnt--; //소용돌이 한칸 이동시키기
        if(remainedMoveCnt == 0) {
            pattern++;
            if(pattern == 4) {
                pattern = 0; //패턴 종료시 초기 패턴인 0으로 되돌리기
                level++;
            }
            if(pattern == 2) level++;
            remainedMoveCnt = level;
        }
    }

    for(int i = 0; i < r2 - r1 + 1; i++) {
        for(int j=0; j < c2 - c1 + 1; j++) {
            int temp = (*(resultMap.begin() + i))[j] / 10;
            int tempSpace = 0;
            while(temp != 0) {
                tempSpace++;
                temp /= 10;
            }

            for(int i = 0; i < space - tempSpace; i++) {
                cout << " ";
            }
            cout << (*(resultMap.begin() + i))[j];
            if(j != c2 - c1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
