#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#define Y first
#define X second

using namespace std;

const int DIRS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int dist[101][101];
int map[101][101];

int bfs(pair<int, int> start, pair<int, int> end) {
    int ret = 0;
    dist[start.Y][start.X] = 0;
    queue<pair<int, int>> que;
    que.push({start.Y, start.X});
    while(!que.empty()) {
        pair<int, int> curr = que.front();
        que.pop();
        for(int i = 0; i < 4; i++) {
            int next_y = curr.Y + DIRS[i][0];
            int next_x = curr.X + DIRS[i][1];
            if (next_y < 0 || next_x < 0 || next_x > 100 || next_y > 100)
                continue;
            if (!map[next_y][next_x] || dist[next_y][next_x] != -1)
                continue;
            if (next_y == end.Y && next_x == end.X) {
                return dist[curr.Y][curr.X] + 1;
            }
            dist[next_y][next_x] = dist[curr.Y][curr.X] + 1;
            que.push({next_y, next_x});
        }
    }
    return -1;
}

void make_map(vector<vector<int>> &rectangle) {
    int temp_map[100][100];
    fill(&temp_map[0][0], &temp_map[100][101], 0);
    /* 상자들의 테두리를 그린다 */
    for (auto r : rectangle) {
        pair<int, int> left_bot = {r[1] * 2, r[0] * 2};
        pair<int, int> right_top = {r[3] * 2, r[2] * 2};
        for (int y = left_bot.Y; y <= right_top.Y; y++) {
                map[y][left_bot.X] = 1;
                map[y][right_top.X] = 1;
        }
        for(int x = left_bot.X; x <= right_top.X; x++) {
                map[left_bot.Y][x] = 1;
                map[right_top.Y][x] = 1;
        } 
    }
    /* 다시 상자들을 순회하면서 각 상자 내부에 존재하는 다른 상자의 테두리를 삭제한다 */
    for (auto r : rectangle) {
        pair<int, int> left_bot = {r[1] * 2, r[0] * 2};
        pair<int, int> right_top = {r[3] * 2, r[2] * 2};
        for (int y = left_bot.Y + 1; y < right_top.Y; y++) 
            for(int x = left_bot.X + 1; x < right_top.X; x++) 
                map[y][x] = 0;
    }
}

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    make_map(rectangle);
    fill(&dist[0][0], &dist[100][101], -1);
    int answer = bfs({characterY * 2, characterX * 2}, {itemY * 2, itemX * 2}) / 2;
    return answer;
}
