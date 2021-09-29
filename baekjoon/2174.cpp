#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

int A,B,N,M;
unordered_map<char,int> um;
int map[100][100];
bool flag = false;

struct Robot{
    int x, y, rotate, index;
};

struct Order{
    int order,robotIndex, iter;
};

void p_x(int &x, int &y){x++;}
void p_y(int &x, int &y){y++;}
void m_x(int &x, int &y){x--;}
void m_y(int &x, int &y){y--;}
void(*func[4])(int&,int&) = {m_x, p_y, p_x, m_y };

void orderL(Robot* list, int robotIndex, int iter) {
    while(iter >= 4) iter %= 4;
    while(iter) {
        list[robotIndex].rotate--;
        if(list[robotIndex].rotate < 0) list[robotIndex].rotate = 3;
        iter--;
    }
}

void orderR(Robot* list, int robotIndex, int iter) {
    while(iter >= 4) iter %= 4;
    while(iter) {
        list[robotIndex].rotate++;
        if(list[robotIndex].rotate > 3) list[robotIndex].rotate = 0;
        iter--;
    }
}

void orderF(Robot* list, int robotIndex, int iter) {
    int rotate = list[robotIndex].rotate;
    int x = list[robotIndex].x, y = list[robotIndex].y;

    while(iter) {
        map[x][y] = 0;
        func[rotate](x,y);
        if (x < 0 || x >= A || y < 0 || y >= B) {
            printf("Robot %d crashes into the wall\n", robotIndex + 1);
            flag = true;
            break;
        }
        if(map[x][y] == 1) {
            int target;
            for(int i = 0; i < N; i++) {
                if(list[i].x == x && list[i].y == y) {
                    target = list[i].index;
                    break;
                }
            }
            printf("Robot %d crashes into robot %d\n", robotIndex + 1, target);
            flag = true;
            break;
        }
        map[x][y] = 1;
        iter--;
    }

    list[robotIndex].x = x;
    list[robotIndex].y = y;
}
void(*func2[3])(Robot*,int,int) = {orderL, orderR, orderF};

int main(){
    // 인풋처리
    um['W'] = 0; um['N'] = 1; um['E'] = 2; um['S'] = 3; um['L'] = 0; um['R'] = 1; um['F'] = 2;
    cin >> A >> B >> N >> M;
    Robot robot_list[N];
    Order order_list[M];
    fill_n(map[0], 100 * 100, 0);
    for(int i = 0; i < N; i++) {
        int x, y;
        char rotate;
        cin >> x >> y >> rotate;
        robot_list[i] = {x - 1,y - 1, um[rotate], i + 1};
        map[x-1][y-1] = 1;
    }
    for(int i = 0; i < M; i++) {
        int robotIndex, iter;
        char order;
        cin >> robotIndex >> order >> iter;
        order_list[i] = {um[order], robotIndex - 1, iter};
    }
    // 작업
    for(int i = 0; i < M; i++) {
        if(flag) break;
        func2[order_list[i].order](robot_list, order_list[i].robotIndex, order_list[i].iter);
    }
    if(!flag) cout << "OK" << endl;
}
