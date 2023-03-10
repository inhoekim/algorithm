#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef priority_queue<pair<int, vector<int>>> PQ;
int ranking = 0;
PQ pq;
PQ recur_pq;
int N, K;


void get_ranking(int recur) {
    if(recur == 3) return;
    int this_medal = pq.top().first;
    vector<int> this_nation = pq.top().second;
    bool nation_flag = false;
    if (this_nation.back() == K) nation_flag = true;
    if(nation_flag && pq.size() == 1) return;

    recur_pq.push(pair<int,vector<int>>(this_nation[recur], this_nation));
    pq.pop();

    while(!pq.empty()){
        int next_medal = pq.top().first;
        vector<int> next_nation = pq.top().second;
        // 등수가 확실하게 갈리는 지점을 발견
        if(this_medal != next_medal) {
            // 내가 원하는 나라를 발견하지 못한 상태라면 랭킹 계산 후 계속 찾기
            if(!nation_flag) {
                //랭킹 계산 후 pq2 clear
                ranking += recur_pq.size();
                recur_pq = PQ();
            }
            // 원하는 나라를 발견한 상태라면 다시 세부 등수확인을 위해 루프 탈출
            else {
                pq = recur_pq;
                recur_pq = PQ();
                get_ranking(++recur);
                return;
            }
        }
        // 등수가 구분이 안되는 경우 현재 발견한 나라를 저장
        if (next_nation.back() == K) nation_flag = true;
        recur_pq.push(pair<int,vector<int>>(next_nation[recur], next_nation));
        this_nation = next_nation;
        this_medal = next_medal;
        pq.pop();
    }

    if(!recur_pq.empty()) {
        pq = recur_pq;
        recur_pq = PQ();
        get_ranking(++recur);
    }
}

int main(){
    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        pq.push(pair<int,vector<int>>(b,{c,d,a}));
    }
    get_ranking(0);
    cout << ranking + 1 << "\n";
    return 0 ;
}
