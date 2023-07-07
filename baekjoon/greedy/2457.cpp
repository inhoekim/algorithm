#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#define MONTH first
#define DAY second

using namespace std;

int ret;

class flower {
public:
	pair<int, int> start, end;
	flower(pair<int, int> start, pair<int, int> end) {
		this->start = start;
		this->end = end;
	}
	flower() {
		start = {-1, -1};
		end = {-1, -1};
	}
};

bool compare(flower a, flower b) {
	if (a.start.MONTH == b.start.MONTH) {
		return (a.start.DAY < b.start.DAY);
	}
	return (a.start.MONTH < b.start.MONTH);
}

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.MONTH == b.MONTH) {
		return (a.DAY <= b.DAY);
	}
	return (a.MONTH < b.MONTH);
}

bool is_same_day(pair<int, int> a, pair<int, int> b) {
	if (a.MONTH == b.MONTH && a.DAY == b.DAY)
		return (true);
	return (false);
}

void choice_flower(vector<flower> &f_lst) {
	flower princess({3, 1}, {11, 30});
	flower temp_choice;

	for (int i = 0; i < f_lst.size(); i++) {
		//조건에 필요한 모든 꽃을 전부다 choice한 경우
		if (compare(princess.end, princess.start) && !is_same_day(princess.end, princess.start))
			return;
		//만약 princess의 start 포인트보다 choice할 꽃의 end가 작다면 고를 이유가 없음
		if (compare(f_lst[i].end, princess.start))
			continue;
		//만약 princess의 start 포인트보다 choice할 꽃의 start가 크다면 조건을 충족하지 못함 (따라서 이전의 꽃들에서 하나를 선택해야한다)
		if (!compare(f_lst[i].start, princess.start)) {
			//선택된 이전의 꽃이 없다면 조건을 충족하지 못함
			if (temp_choice.end.MONTH == -1) {
				ret = 0;
				return ;
			}
			ret++;
			princess.start = temp_choice.end;
			//이후 임시 choice를 초기화 하고 현재 인덱스부터 다시 꽃을 choice 해봄
			temp_choice.end.MONTH = -1;
			i--;
			continue;
		}
		//조건을 충족한 꽃들 중 end가 가장 큰 꽃을 그리디하게 선택(해당 꽃의 end가 이후 pricess의 start가 됨)
		else {
			if (compare(temp_choice.end, f_lst[i].end))
				temp_choice = f_lst[i];
		}
	}
}

int main(void) {
	int n;
	cin >> n;
	vector<flower> f_lst;
	for (int i = 0; i < n; i++) {
		int s1, e1, s2, e2;
		cin >> s1 >> e1 >> s2 >> e2;
		f_lst.push_back(flower({s1, e1}, {s2, e2}));
	}
	//end포인트를 위해서 마지막에 맥스 flower를 추가
	f_lst.push_back(flower({999, 999}, {999, 999}));
	bool (*cmp) (flower a, flower b) = compare;
	sort(f_lst.begin(), f_lst.end(), cmp);
	choice_flower(f_lst);
	cout << ret << endl;
}
