#include <iostream>
#include <deque>
#include <vector>
#define Y first
#define X second
#define IDX first
#define DIR second

using namespace std;

enum e_color{
    RED = 1,
    BLUE = 2
};

const int DIRS[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
vector<vector<int>> color;
vector<vector<deque<pair<int, int>>>> map_k;
vector<pair<int, int>> location_k;
int N, K;

void change_map(pair<int, int> curr, pair<int, int> next, int loc_idx) {
    int cnt = 0;
    if (color[next.Y][next.X] == RED) {
        for (int i = map_k[curr.Y][curr.X].size() - 1; i >= loc_idx; i--) {
            pair<int, int> target = map_k[curr.Y][curr.X][i];
            map_k[next.Y][next.X].push_back(target);
            location_k[target.IDX] = next;
            cnt++;
        }
        for (int i = 0; i < cnt; i++)
            map_k[curr.Y][curr.X].pop_back();
    }
    else {
        for (int i = loc_idx; i < map_k[curr.Y][curr.X].size(); i++) {
            pair<int, int> target = map_k[curr.Y][curr.X][i];
            map_k[next.Y][next.X].push_back(target);
            location_k[target.IDX] = next;
            cnt++;
        }
        for (int i = 0; i < cnt; i++)
            map_k[curr.Y][curr.X].pop_back();
    }
}

void move_token(int idx) {
    deque<pair<int, int>> &tokens = map_k[location_k[idx].Y][location_k[idx].X];
    int loc_idx;
    for (loc_idx = 0; loc_idx < tokens.size(); loc_idx++)
        if (tokens[loc_idx].IDX == idx)
            break;
    int next_y = location_k[idx].Y + DIRS[tokens[loc_idx].DIR][0];
    int next_x = location_k[idx].X + DIRS[tokens[loc_idx].DIR][1];

    if (next_y < 0 || next_x < 0 || next_y >= N || next_x >= N || color[next_y][next_x] == BLUE) {
        if (tokens[loc_idx].DIR == 1 || tokens[loc_idx].DIR == 3)
            tokens[loc_idx].DIR--;
        else
            tokens[loc_idx].DIR++;
        next_y = location_k[idx].Y + DIRS[tokens[loc_idx].DIR][0];
        next_x = location_k[idx].X + DIRS[tokens[loc_idx].DIR][1];
        if (!((next_y < 0 || next_x < 0 || next_y >= N || next_x >= N) || color[next_y][next_x] == BLUE))
            change_map({location_k[idx].Y, location_k[idx].X}, {next_y, next_x}, loc_idx);
    }
    else
        change_map({location_k[idx].Y, location_k[idx].X}, {next_y, next_x}, loc_idx);
}

int game_start() {
    int turn = 1;
    while (turn <= 1000) {
        for (int i = 0; i < K; i++) {
            move_token(i);
            for (int i = 0; i < location_k.size(); i++)
                if (map_k[location_k[i].Y][location_k[i].X].size() >= 4)
                    return turn;
        }
        turn++;
    }
    return -1;
}

int main(void) {
    cin >> N >> K;
    color = vector<vector<int>>(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> color[i][j];
    map_k = vector<vector<deque<pair<int, int>>>>(N, vector<deque<pair<int, int>>>(N));
    for (int i = 0; i < K; i++) {
        int y, x, dir;
        cin >> y >> x >> dir;
        map_k[y-1][x-1].push_back({i, dir - 1});
        location_k.push_back({y-1, x-1});
    }
    cout << game_start() << endl;
}
