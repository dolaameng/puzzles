#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <set>
#include <iterator>

using namespace std;

//depth first search - backtracking

const int NMAX = 100000+1;

// binary index tree for quick partial sum
class BIT {
private:
	vector<int> xs;
	const int n;
public:
	BIT(const int n_): xs(n_+1), n(n_) {
	};
	void update(const int i, const int x) {
		int index = i + 1;
		while (index <= n+1) {
			xs[index] += x;
			index += index & (-index);
		}
	}
	long sumto(const int i) {
		int index = i + 1;
		long sum = 0;
		while (index > 0) {
			sum += xs[index];
			index -= index & (-index);
		}
		return sum;
	}
	//both are inclusive
	long rangesum(const int start, const int end) {
		return sumto(end) - sumto(start-1);
	}
};

typedef vector<vector<int> > Tree;
typedef vector<int> Solution;

Solution solution;
BIT bit(NMAX);
long total_pairs = 0;

void search(const Tree & tree, const int thr) {
	const int node = solution.back();
	
	// check current solution
	//TODO
	int start = (node-thr >= 1) ? (node-thr) : 1;
	int end = (node+thr <= NMAX) ? (node+thr) : NMAX;
	total_pairs += bit.rangesum(start, end) -1;
	

	const vector<int> & candidates = tree[node];
	for (int i = 0; i < candidates.size(); ++i) {
		solution.push_back(candidates[i]); 
		//TODO
		bit.update(candidates[i], 1);
		search(tree, thr);
		solution.pop_back(); 
		//TODO
		bit.update(candidates[i], -1);
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
	//TODO:
	bit.update(root, 1);
	search(tree, T);
	cout << total_pairs << endl;
	return 0;
}