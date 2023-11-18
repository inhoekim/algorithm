#include <algorithm>
#include <iostream>
#include <vector>
#define X first
#define Y second

using namespace std;
vector<pair<int,int>> lines;

long long cal_result(vector<pair<int,int>> lines) {
	long long ret = 0;
	for(int i = 0; i < lines.size(); i++)
		ret += (long long)lines[i].Y - lines[i].X;
	return ret;
}

vector<pair<int,int>> conbine_line() {
	vector<pair<int,int>> new_lines = {{lines[0].X, lines[0].Y}};
	for(int i = 1; i < lines.size(); i++) {
		if (lines[i].X <= new_lines.back().Y){
			if (lines[i].Y > new_lines.back().Y)
				new_lines.back().Y = lines[i].Y;
		}
		else
			new_lines.push_back({lines[i].X, lines[i].Y});
	}
	return new_lines;
}

int main(void) { 
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		lines.push_back(pair<int, int>(a, b));
	}
	sort(lines.begin(), lines.end());
	vector<pair<int,int>> new_line = conbine_line();
	cout << cal_result(new_line) << endl;
	return (0);
}
