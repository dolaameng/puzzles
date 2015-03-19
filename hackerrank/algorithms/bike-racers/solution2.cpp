#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <stack>
#include <algorithm>
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

int N, M, K; 
vector<pair<int,int> > riders;
vector<pair<int,int> > bikes;
vector<vector<int> > r2b;


int max_matches = 0;
vector<bool> taken_bikes;
pair<int, int> solution;

void dfs(const vector<vector<int> > & graph) {
	int matches = solution.first; int node = solution.second;
	cout << "matches:" << matches << " node:" << node << " max:" << max_matches << endl;
	if (max_matches >= K) return;
	
	if (matches >= K) {
		max_matches = K;
		return;
	}
	if (node == N) {
		if (matches > max_matches) max_matches = matches;
		return;
	}
	if ( (matches + N - node) < max_matches) return;
	
	bool explored = false;
	for (int i = 0; i < graph[node].size(); ++i) {
		int m = graph[node][i];
		if (!taken_bikes[m] && max_matches < K) {
			explored = true;
			solution = make_pair(matches+1, node+1); taken_bikes[m] = true;
			dfs(graph);
			solution = make_pair(matches-1, node-1); taken_bikes[m] = false;
		}
	}
	if (!explored) {
		solution = make_pair(matches, node+1);
		dfs(graph);
		solution = make_pair(matches, node-1); 
	}
}

int match (const vector<vector<int> > & graph) {
	taken_bikes = vector<bool>(M, false);
	max_matches = 0;
	solution = make_pair(0, 0);
	dfs(graph);
	return max_matches;
}

int euclidean(const pair<int,int> & xy1, const pair<int,int> & xy2) {
	return (xy1.first-xy2.first)*(xy1.first-xy2.first) + (xy1.second-xy2.second)*(xy1.second-xy2.second);
}

bool check(const unsigned long long time, 
			const vector<vector<int> > & r2b) {
	vector<vector<int> > graph (N, vector<int>());
	for (int r = 0; r < N; ++r) {
		for (int b = 0; b < M; ++b) {
			if (r2b[r][b] <= time) graph[r].push_back(b);
		}
	}
	/*
	for (int r = 0; r < N; ++r) {
		cout << r << ":";
		for (int i = 0; i < graph[r].size(); ++i) {
			cout << graph[r][i] << " ";
		}
		cout << endl;
	}
	*/
	return match(graph) >= K;
}

int main() {
	
	
	cin >> N >> M >> K;
	for (int i = 0; i < N + M; ++i) {
		int x, y; cin >> x >> y;
		if (i < N) riders.push_back(make_pair(x, y));
		else bikes.push_back(make_pair(x, y));
	}

	r2b = vector<vector<int> >(N, vector<int>(M));
	for (int r = 0; r < riders.size(); ++r) {
		for (int b = 0; b < bikes.size(); ++b) {
			r2b[r][b] = euclidean(riders[r], bikes[b]);
		}
	}

	
	 long long low = 0;
	 long long high = 10000000000000000; // 10**16
	while (low < high) {
		 long long mid = (low + high) / 2;
		if (check(mid, r2b)) high = mid;
		else low = mid+1;
		//cout << mid << endl;
	}

	cout << low << endl;
	
	//cout << check(0,r2b) << endl;
	return 0;

}