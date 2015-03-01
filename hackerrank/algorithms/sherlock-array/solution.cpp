#include <iostream>
#include <vector>

using namespace std;

int sum(const vector<int> & xs) {
	int total = 0;
	for (int i = 0; i < xs.size(); ++i) total += xs[i];
	return total;
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N; cin >> N;
		vector<int> xs(N);
		for (int i = 0; i < N; ++i) cin >> xs[i];
		int total = sum(xs);
		int left = 0;
		bool answer = false;
		for (int i = 0; i < N; ++i) {
			if (left == total - left - xs[i]) {
				answer = true;
				break;
			}
			left += xs[i];
		}
		if (answer) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}