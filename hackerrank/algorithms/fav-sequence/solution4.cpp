#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main () {
	const int MAXN = 1000001;
	const int MAXM = 1001;

	vector<int> xs(MAXM);
	vector<bool> nodes(MAXN, false);
	vector<vector<int> > nexts(MAXN, vector<int>());
	vector<int> in_degrees(MAXN);

	int nseqs; cin >> nseqs;
	for (int s = 0; s < nseqs; ++s) {
		int n; cin >> n;
		int prex, x;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			nodes[x] = true;
			if (i > 0) {
				nexts[prex].push_back(x);
				in_degrees[x]++;
			}
			prex = x;
		}
	}
	priority_queue<int, vector<int>, greater<int> > q;
	vector<int> sorted;
	for (int i = 0; i < MAXN; ++i) {
		if (nodes[i] && in_degrees[i] == 0)
			q.push(i);
	}
	while(! q.empty()) {
		int cur = q.top();
		sorted.push_back(cur); q.pop();
		for (int i = 0; i < nexts[cur].size(); ++i) {
			int d = --in_degrees[nexts[cur][i]];
			if (d == 0) {
				q.push(nexts[cur][i]);
			}
		}
	}

	for (int i = 0; i < sorted.size() - 1; ++i) {
		cout << sorted[i] << " ";
	}
	cout << sorted[sorted.size() - 1] << endl;

	return 0;
}