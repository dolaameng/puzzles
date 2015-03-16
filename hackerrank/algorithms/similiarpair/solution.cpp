#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

//depth first search - backtracking

typedef vector<vector<int> > Tree;
typedef vector<int> Solution;

Solution solution;
long total_pairs = 0;

void search(const Tree & tree, const int thr) {
	const int node = solution.back();
	
	// check current solution
	for (int i = 0; i < solution.size()-1; ++i) {
		if (abs(node - solution[i]) <= thr) total_pairs++;
	}

	const vector<int> & candidates = tree[node];
	for (int i = 0; i < candidates.size(); ++i) {
		solution.push_back(candidates[i]);
		search(tree, thr);
		solution.pop_back();
	}
}

int main() {
	int N, T;
	cin >> N >> T;
	Tree tree(N+1);
	vector<bool> possible_roots(N+1, true);
	for (int i = 0; i < N-1; ++i) {
		int a, b; cin >> a >> b;
		tree[a].push_back(b);
		possible_roots[b] = false;
	}
	int root = -1;
	for (int n = 1; n <= N; ++n) {
		if (possible_roots[n]) {
			root = n;
			break;
		}
	}
	
	solution.push_back(root);
	search(tree, T);
	cout << total_pairs << endl;
	return 0;
}