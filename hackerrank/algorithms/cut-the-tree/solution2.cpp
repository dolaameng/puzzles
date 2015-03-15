#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <map>

using namespace std;

map<pair<int,int>, int> cache;

int total_visits = 0;
int cached_visits = 0;

int subtree(const int exclude,
			const int root, 
			const vector<int> & wts,
			const vector<vector<int> > & tree) {
	
	total_visits++;
	if (cache[make_pair(exclude, root)] != -1) {
		cached_visits++;
		return cache[make_pair(exclude, root)];
	}

	int total_wts = wts[root];
	for (int i = 0; i < tree[root].size(); ++i) {
		int neighbor = tree[root][i];
		if (neighbor != exclude) {
			total_wts += subtree(root, neighbor, wts, tree);
		} 
	}
	cache[make_pair(exclude, root)] = total_wts;
	cache[make_pair(root, exclude)] = total_wts;
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
	vector<vector<int> > tree(N+1);
	vector<pair<int, int> > edges;
	for (int i = 0; i < N-1; ++i) {
		int a, b; cin >> a >> b;
		edges.push_back(make_pair(a, b));
		tree[a].push_back(b);
		tree[b].push_back(a);
		cache[make_pair(a, b)] = -1;
		cache[make_pair(b, a)] = -1;
	}

	int min_diff = total_wts;
	for (int e = 0; e < edges.size(); ++e) {
		int a = edges[e].first;
		int b = edges[e].second;
		int sub_wt = subtree(a, b, wts, tree);
		int diff = abs(2*sub_wt - total_wts);
		if (diff < min_diff) min_diff = diff;
	}
	cout << min_diff << endl;
	//cout << total_visits << " " << cached_visits << endl;
	return 0;
}