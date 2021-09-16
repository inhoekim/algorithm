//https://programmers.co.kr/learn/courses/30/lessons/72412

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<string, int> um;
vector<int> num_case[4][3][3][3];

vector<int> solution(vector<string> info, vector<string> query) {
    um["-"] = 0;
    um["cpp"] = 1; um["java"] = 2; um["python"] = 3;
    um["backend"] = 1; um["frontend"] = 2;
    um["junior"] = 1; um["senior"] = 2;
    um["chicken"] = 1; um["pizza"] = 2;
    vector<int> answer;

    for(int i = 0; i < info.size(); i++) {
        stringstream ss;
        ss.str(info[i]);
        string lang_tem, group_tem, career_tem, food_tem;
        string *str_p[4] = {&lang_tem, &group_tem, &career_tem, &food_tem};
        int score;
        ss >> lang_tem >> group_tem >> career_tem >> food_tem >> score;

        for(int i = 0; i < (1<<4); i++) {
            vector<int> temp (4,0);
            for(int j = 0; j < 4; j++) {
                if(i & (1 << j)) temp[j] = um[*str_p[j]];
            }
            num_case[temp[0]][temp[1]][temp[2]][temp[3]].push_back(score);
        }
    }
    for(int a = 0; a < 4; a++) {
        for(int b = 0; b < 3; b++) {
            for(int c = 0; c < 3; c++) {
                for(int d = 0; d < 3; d++) {
                    sort(num_case[a][b][c][d].begin(), num_case[a][b][c][d].end());
                }
            }
        }
    }

    for(int i = 0; i < query.size(); i++) {
        stringstream ss;
        ss.str(query[i]);
        string lang_tem, group_tem, career_tem, food_tem, tem;
        int score;
        ss >> lang_tem >> tem >> group_tem >> tem >> career_tem >> tem >> food_tem >> score;

        auto iter = lower_bound(num_case[um[lang_tem]][um[group_tem]][um[career_tem]][um[food_tem]].begin(),
                                num_case[um[lang_tem]][um[group_tem]][um[career_tem]][um[food_tem]].end(),
                                score);
        int result = num_case[um[lang_tem]][um[group_tem]][um[career_tem]][um[food_tem]].end() - iter;
        answer.push_back(result);
    }

    return answer;
}

int main(){
    vector<string> info = {"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"};
    vector<string> query = {"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"};
    vector<int> answer = solution(info, query);

    for(int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }
    return 0;
}
