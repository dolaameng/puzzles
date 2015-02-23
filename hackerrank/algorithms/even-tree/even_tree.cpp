#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<bool> searched;
int ncuts = 0;

int dfs(int root, const vector<vector<int> > & graph) {
	searched[root] = true;
	int nnodes = 0;
	for (int i = 0; i < graph[root].size(); ++i) {
		int node = graph[root][i];
		if (!searched[node]) {
			int subnodes = dfs(node, graph);
			if (subnodes % 2 == 0) ncuts += 1;
			else nnodes += subnodes;
		}
	}
	return nnodes + 1;
}


int main() {
	int N, M;
	cin >> N >> M;
	// bias starting from 1
	vector<vector<int> > graph(N+1, vector<int>()); 
	searched = vector<bool>(N+1, false);
	for (int m = 0; m < M; ++m) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	/*
	for (int i = 0; i < graph.size(); ++i) {
		cout << i << ":";
		for (int j = 0; j < graph[i].size(); ++j) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	*/
	dfs(1, graph);
	cout << ncuts << endl;
	return 0;
}