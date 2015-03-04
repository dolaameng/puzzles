#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 2000;

int knapsack(vector<int> & xs, const int total) {
	sort(xs.begin(), xs.end());
	vector<int>::iterator it = unique(xs.begin(), xs.end());
	vector<int> candidates(xs.begin(), it);
	vector<bool> s(MAX+1, false);
	for (int i = 0; i < candidates.size(); ++i) {
		s[candidates[i]] = true;
	}
	deque<int> q(candidates.begin(), candidates.end());
	while (!q.empty()) {
		int x = q.front();
		if (x == total) return total;
		q.pop_front();
		for (int ic = 0; ic < candidates.size(); ++ic) {
			int newx = candidates[ic] + x;
			//cout << "newx:" << newx << endl;
			if (newx <= total && !s[newx]) {
				s[newx] = true;
				q.push_back(newx);
			}
			
		}
	}
	for (int t = total; t >= 1; --t) {
		if (s[t]) return t;
	}
	return 0;
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, K;
		cin >> N >> K;
		vector<int> xs(N);
		for (int i = 0; i < N; ++i) cin >> xs[i];
		cout << knapsack(xs, K) << endl;
	}
	return 0;
}