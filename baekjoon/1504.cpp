#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<vector<pair<int,int>>> map;
//문제 조건에 의하면 가중치 최대치는 1000인데 간선의 총갯수는 200,000개 이므로 정답은 2억이상의 값이 나올 수 없다. 따라서 INF값은 대충 987654321로 설정.
int INF = 987654321;
int N,E;

vector<int> dij(int start){
    vector<int> dist(N,INF);
    priority_queue<pair<int,int>> pq;
    pq.push(pair<int,int>(0,start));
    dist[start] = 0;
    while(!pq.empty()) {
        int cost = -pq.top().first;
        int currNode = pq.top().second;
        pq.pop();
        for(int i = 0; i < map[currNode].size(); i++) {
            int nextCost = -map[currNode][i].first;
            int nextNode = map[currNode][i].second;
            if(dist[nextNode] > cost + nextCost) {
                dist[nextNode] = cost + nextCost;
                pq.push(pair<int,int>(-dist[nextNode], nextNode));
            }
        }
    }
    return dist;
}

int main(){
    cin >> N >> E;
    map = vector<vector<pair<int,int>>>(N);

    for(int i = 0 ; i < E; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        map[a-1].push_back(pair<int,int>(-c,b-1)); // pair first == 가중치 , pair second == 인접노드번호
        map[b-1].push_back(pair<int,int>(-c, a-1)); //양방향 그래프이므로 양쪽으로 간선을 넣어준다
    }
    int u,v;
    cin >> u >> v;
    u -= 1, v -= 1;
    int goal = N-1;
    int result1 = 0, result2 = 0;
    //0번노드, U번노드, V번노드를 각각 시작점으로 하여 다익스트라 알고리즘을 돌린다
    //0->U->V->Goal의 순서를 갖는 경로와 0->V->U->Goal의 순서를 갖는 경로, 두 경로의 최단거리 중 더 짧은 녀석이 정답이 된다
    vector<int> distStart = dij(0);
    vector<int> distU = dij(u);
    vector<int> distV = dij(v);

    if(distStart[u] == INF || distU[v] == INF || distV[goal] == INF) result1 = INF;
    else result1 += distStart[u] + distU[v] + distV[goal]; //0->U->V->Goal 순서의 경로

    if(distStart[v] == INF || distV[u] == INF || distU[goal] == INF) result2 = INF;
    else result2 += distStart[v] + distV[u] + distU[goal]; //0->V->U->Goal 순서의 경로

    if(result1 == INF && result2 == INF) cout << -1 << endl;
    else if(result1 >= result2) cout << result2 << endl;
    else if(result2 > result1) cout << result1 << endl;
    return 0;
}


