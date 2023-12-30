#include <iostream>
#include <map>
#include <queue>
#define CORD first
#define DIST second
#define A first
#define B second

using namespace std;

map<pair<int,int>, int> visited;

int a, b, c, d;

int bfs() {
    queue<pair<int, int>> que;
    que.push({0, 0});
    visited.insert({pair<int,int>(0,0), 0});
    while (!que.empty()) {
        pair<int,int> curr = que.front();
        que.pop();
        int dist = visited.find(curr)->DIST;
        if (curr.A == c && curr.B == d)
            return dist;
        /* Fill A */
        if (visited.find({a, curr.B}) == visited.end()) {
            visited.insert(make_pair(make_pair(a, curr.B), dist + 1));
            que.push({a, curr.B});
        }
        /* Fill B */
        if (visited.find({curr.A, b}) == visited.end()) {
            visited.insert(make_pair(make_pair(curr.A, b), dist + 1));
            que.push({curr.A, b});
        }
        /* Empty A */
        if (visited.find({0, curr.B}) == visited.end()) {
            visited.insert(make_pair(make_pair(0, curr.B), dist + 1));
            que.push({0, curr.B});
        }
        /* Empty B */
        if (visited.find({curr.A, 0}) == visited.end()) {
            visited.insert(make_pair(make_pair(curr.A, 0), dist + 1));
            que.push({curr.A, 0});
        }
        /* Move A */
        int next_b = curr.B + curr.A;
        int next_a = 0;
        if (next_b > b) {
            next_a += next_b - b;
            next_b = b;
        }
        if (visited.find({next_a, next_b}) == visited.end()) {
            visited.insert(make_pair(make_pair(next_a, next_b), dist + 1));
            que.push({next_a, next_b});
        }
        /* Move B */
        next_a = curr.A + curr.B;
        next_b = 0;
        if (next_a > a) {
            next_b += next_a - a;
            next_a = a;
        }
        if (visited.find({next_a, next_b}) == visited.end()) {
            visited.insert(make_pair(make_pair(next_a, next_b), dist + 1));
            que.push({next_a, next_b});
        }
    }
    return -1;
}

int main(void) {
    cin >> a >> b >> c >> d;
    cout << bfs() << endl;
}
