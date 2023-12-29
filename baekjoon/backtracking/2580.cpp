#include <iostream>
#include <vector>
#define Y first
#define X second

using namespace std;

int map[9][9];
int col_check[9], row_check[9], box_check[9];
vector<pair<int,int>> zero_lst;

void print_map() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 8)
                cout << map[i][j];
            else
                cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

int get_box_idx(int y, int x) {
    return ((y / 3) * 3) + (x / 3);
}

void back_tracking(int depth) {
    if (depth == zero_lst.size()) {
        print_map();
        exit(0);
    }
    for (int num = 1; num <= 9; num++) {
        int sh_num = 1 << (num - 1);
        int box_idx = get_box_idx(zero_lst[depth].Y, zero_lst[depth].X);
        if (row_check[zero_lst[depth].Y] & sh_num || col_check[zero_lst[depth].X] & sh_num || box_check[box_idx] & sh_num)
            continue;
        row_check[zero_lst[depth].Y] |= sh_num;
        col_check[zero_lst[depth].X] |= sh_num;
        box_check[box_idx] |= sh_num;
        map[zero_lst[depth].Y][zero_lst[depth].X] = num;
        back_tracking(depth + 1);
        row_check[zero_lst[depth].Y] ^= sh_num;
        col_check[zero_lst[depth].X] ^= sh_num;
        box_check[box_idx] ^= sh_num;
        map[zero_lst[depth].Y][zero_lst[depth].X] = 0;
    }
}


int main(void) {
    //입력부
    for (int i = 0 ; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num;
            cin >> num;
            if (num == 0)
                zero_lst.push_back({i, j});
            else {
                map[i][j] = num;
                row_check[i] = row_check[i] | (1 << (num - 1));
                col_check[j] = col_check[j] | (1 << (num - 1));
                int box_idx = get_box_idx(i, j);
                box_check[box_idx] = box_check[box_idx] | (1 << (num - 1));
            }
        }
    }
    //백트래킹
    back_tracking(0);
}
