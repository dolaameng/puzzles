#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
using namespace std;

/*
input:
3 3 2
0 1
0 2
0 3
100 1
200 2 
300 3

output:
40000
*/

int manhatten(const pair<int,int> & xy1, const pair<int,int> & xy2) {
	return abs(xy1.first-xy2.first) + abs(xy1.second-xy2.second);
}

int main() {
	int N, M, K; 
	vector<pair<int,int> > riders;
	vector<pair<int,int> > bikes;
	cin >> N >> M >> K;
	for (int i = 0; i < N + M; ++i) {
		int x, y; cin >> x >> y;
		if (i < N) riders.push_back(make_pair(x, y));
		else bikes.push_back(make_pair(x, y));
	}

	vector<vector<int> > r2b(N, vector<int>(M));
	for (int r = 0; r < riders.size(); ++r) {
		for (int b = 0; b < bikes.size(); ++b) {
			r2b[r][b] = manhatten(riders[r], bikes[b]);
		}
	}
}