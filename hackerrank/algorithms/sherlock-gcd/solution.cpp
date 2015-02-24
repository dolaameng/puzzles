#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd (const int a, const int b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

bool has_coprime_set(vector<int> & xs) {
	sort(xs.begin(), xs.end());
	if (xs[0] == 1) return true;

	int lhs = xs[0];
	for (int i = 1; i < xs.size(); ++i) {
		lhs = gcd(lhs, xs[i]);
		if (lhs == 1) return true;
	}
	return false;
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N; cin >> N;
		vector<int> xs(N);
		for (int i = 0; i < N; ++i) cin >> xs[i];
		if (has_coprime_set(xs)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}