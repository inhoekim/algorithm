#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

const int DIRECTION[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void resize_map(vector<vector<int>> &map, int resizing_size) {
    int map_size = map[0].size();
    vector<vector<int>> temp(resizing_size, vector<int>(resizing_size, 0));
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            temp[map_size + i][map_size + j] = map[i][j];
        }
    }
    map = temp;
}

string hashing_map(vector<vector<int>> &map, bool is_target) {
    int size = map.size();
    stringstream ss;
    if (is_target) {
        size /= 3;
        for (int i = size; i < 2 * size; i++)
            for (int j = size; j < 2 * size; j++)
                if (map[i][j])
                    ss << "[" << i << "," << j << "]";
    }
    else {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (map[i][j])
                    ss << "[" << i << "," << j << "]";
    }
    return ss.str();
}

bool move_map(vector<vector<int>> &map, int dir_idx, int is_reverse) {
    int map_size = map.size();
    vector<vector<int>> temp(map_size, vector<int>(map_size, 0));
    for (int y = 0; y < map_size; y++) {
        for (int x = 0; x < map_size; x++) {
            if (map[y][x]) {
                int next_y = y + DIRECTION[dir_idx][0] * is_reverse;
                int next_x = x + DIRECTION[dir_idx][1] * is_reverse;
                if (next_y < 0 || next_x < 0 || next_y >= map_size || next_x >= map_size)
                    return false;
                temp[next_y][next_x] = 1;
            }
        }
    }
    map = temp;
    return true;
}

void rotate_map(vector<vector<int>> &map) {
    int map_size = map.size();
    vector<vector<int>> temp = map;
    for (int i = 0; i < map_size; i++)
        for (int j = 0; j < map_size; j++)
            temp[i][j] = map[map_size - 1 - j][i];
    map = temp;
}

void dfs(vector<vector<int>> &map, unordered_set<string> &visited,
         string target, bool &answer)
{
    if (answer || hashing_map(map, true).compare(target) == 0) {
        answer = true;
        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        if (!move_map(map, dir, 1))
            continue;
        string hash_val = hashing_map(map, false);
        if (!answer && visited.find(hash_val) == visited.end()) {
            visited.insert(hash_val);
            dfs(map, visited, target, answer);
        }
        move_map(map, dir, -1);
    }

    for (int rotate_idx = 0; rotate_idx < 3; rotate_idx++) {
        rotate_map(map);
        string hash_val = hashing_map(map, false);
        if (!answer && visited.find(hash_val) == visited.end()) {
            visited.insert(hash_val);
            dfs(map, visited, target, answer);
        }
    }
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int map_size = lock[0].size();
    /* 주어진 key와 lock 맵을 3배 크기로 resize*/
    resize_map(key, 3 * map_size);
    resize_map(lock, 3 * map_size);
    /* 찾고자 하는 lock모양의 hash값을 구함 */
    vector<vector<int>> answer_lock_template = lock;
    for (int i = 0; i < map_size * 3; i++) {
        for (int j = 0; j < map_size * 3; j++) {
            if (lock[i][j] == 0) {
                answer_lock_template[i][j] = 1;
            }
            else {
                answer_lock_template[i][j] = 0;
            }
        }
    }
    string target = hashing_map(answer_lock_template, true);
    /* dfs 검사 */
    unordered_set<string> visited;
    visited.insert(hashing_map(key, false));
    bool answer = false;
    dfs(key, visited, target, answer);
    return answer;
}
