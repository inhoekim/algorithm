#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef unsigned long long ll;
typedef struct {
	int type, atk, hp;
} t_room;

int N, atk;
vector<t_room> rooms;

ll enter_the_dungeon(ll min_len, ll max_len) {
	while (min_len != max_len) {
		ll temp_result = (min_len / 2) + (max_len / 2);
		ll curr_hp = temp_result;
		ll temp_atk = (ll)atk;
		for (auto room : rooms) {
			if (room.type == 1) {
				int last_attack = 1;
				if (room.hp % temp_atk)
					last_attack = 0;
				if (curr_hp <= (room.hp / temp_atk - last_attack) * room.atk)
				{
					min_len = temp_result + 1;
					break;
				}
				curr_hp -= (room.hp / temp_atk - last_attack) * room.atk;
			}
			else if (room.type == 2) {
				temp_atk += room.atk;
				curr_hp += room.hp;
				if (curr_hp > temp_result)
					curr_hp = temp_result;
			}
		}
		if (min_len == temp_result + 1)
			continue;
		max_len = temp_result;
	}
	return min_len;
}

int main(void) {
	cin >> N >> atk;
	for (int i = 0; i < N; i++) {
		t_room room;
		cin >> room.type >> room.atk >> room.hp;
		rooms.push_back(room);
	}
	cout << enter_the_dungeon(1, -1) << endl;
	return 0;
}
