#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>

using namespace std;

int subtree(const int root, const vector<int> & wts,
	const int cut, 
	const vector<vector<int> > & node_edges) {
	int N = wts.size();
	deque<int> q; 
	int total_wts = wts[root];
	vector<bool> searched(N);
	searched[root] = true;
	for (int n = 0; n < node_edges[root].size(); ++n) {
		int neighbor = node_edges[root][n];
		if (neighbor != cut) {
			q.push_back(neighbor);
			searched[neighbor] = true;
		}
	}

	while (!q.empty()) {
		int node = q.front(); q.pop_front();
		//cout << "search " << node << endl;
		total_wts += wts[node];
		for (int n = 0; n < node_edges[node].size(); ++n) {
			int neighbor = node_edges[node][n];
			if (!searched[neighbor]) {
				q.push_back(neighbor);
				searched[neighbor] = true;
			}
		}
	}
	//cout << endl;
	return total_wts;
}

int main() {
	int N; cin >> N;
	vector<int> wts(N+1);
	int total_wts = 0;
	for (int i = 1; i <= N; ++i) {
		cin >> wts[i];
		total_wts += wts[i];
	}
	vector<vector<int> > node_edges(N+1);
	vector<pair<int, int> > edges;
	for (int i = 0; i < N-1; ++i) {
		int a, b; cin >> a >> b;
		edges.push_back(make_pair(a, b));
		node_edges[a].push_back(b);
		node_edges[b].push_back(a);
	}

	int min_diff = total_wts;
	for (int e = 0; e < edges.size(); ++e) {
		int a = edges[e].first;
		int b = edges[e].second;
		//cout << "for " << a << " cut " << b << endl;
		int sub_wt = subtree(a, wts, b, node_edges);
		//cout << "for " << b << " cut " << a << endl;
		//int sub_wtb = subtree(b, wts, a, node_edges);
		//cout << sub_wt << " " << sub_wtb << " " << total_wts << endl;
		int diff = abs(2*sub_wt - total_wts);
		if (diff < min_diff) min_diff = diff;
	}
	cout << min_diff << endl;
	return 0;
}