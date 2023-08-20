#include <iostream>
#include <algorithm>
#include <queue>
#define Y first
#define X second
#define MAX 987654321

using namespace std;

int w, h;
char map[30][30];
int ret;
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int dists[20][30][30];
pair<int, int> point_coord[20];

void bfs(pair<int, int> start, int (*dist)[30]) {
    queue<pair<int, int>> q;
    dist[start.Y][start.X] = 0;
    q.push(start);
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        for(int i = 0; i < 4; i++) {
            int next_y = curr.Y + dirs[i][0];
            int next_x = curr.X + dirs[i][1];
            if (next_y < 0 || next_x < 0 || next_y == h || next_x == w)
                continue;
            if (dist[next_y][next_x] != -1 || map[next_y][next_x] == 'x')
                continue;
            dist[next_y][next_x] = dist[curr.Y][curr.X] + 1;
            q.push({next_y, next_x});
        }
    }
}

void cal_move_cnt(vector<int> &picked) {
    int total = 0;
    for(int i = 0; i < picked.size() - 1; i++) {
        pair<int, int> next = point_coord[picked[i + 1]];
        int move_cnt = dists[picked[i]][next.Y][next.X];
        if (move_cnt < 0)
            return ;
        total += move_cnt;
    }
    ret = min(ret, total);
}

void get_permutation(int dirty_cnt, vector<int> &order, bool *is_picked, int cnt) {
    if (cnt == dirty_cnt) {
        cal_move_cnt(order);
        return ;
    }

    for (int i = 1; i <= dirty_cnt; i++) {
        if (is_picked[i])
            continue;
        order.push_back(i);
        is_picked[i] = true;
        get_permutation(dirty_cnt, order, is_picked, cnt + 1);
        order.pop_back();
        is_picked[i] = false;
    }
}

int main(void) {
    while (true) {
        cin >> w >> h;
        int dirty_cnt = 0;
        ret = MAX;
        //종료 조건
        if (w == 0 || h == 0)
            return (0);
        //입출력 파트
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> map[i][j];
                if (map[i][j] == 'o') {
                    point_coord[0].Y = i;
                    point_coord[0].X = j;
                    map[i][j] = '*';
                }
                else if (map[i][j] == '*') {
                    dirty_cnt++;
                    point_coord[dirty_cnt].Y = i;
                    point_coord[dirty_cnt].X = j;
                }
            }
        }
        fill(&dists[0][0][0], &dists[19][29][30], -1);
        //맵에 존재하는 포인트 지점들을 모두 시작점으로 하여 bfs를 돌리고 각 포인트별 dist배열을 구해놓는다
        for (int i = 0; i <= dirty_cnt; i++)
            bfs(point_coord[i], dists[i]);
        //존재하는 먼지들의 도착순서 순열을 구해서 가장 작은 방문 경로를 찾는다
        vector<int> order; order.push_back(0);
        bool is_picked[20];
        fill(&is_picked[0], &is_picked[20], false);
        is_picked[0] = true;
        get_permutation(dirty_cnt, order, is_picked, 0);
        //결과값 리턴
        if (ret == MAX)
            ret = -1;
        cout << ret << endl;
    }
}
