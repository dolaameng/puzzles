#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

vector<int> buy(const vector<int> & flavors, const int sum) {
	vector<int> r(2);
	for(int i = 1; i < flavors.size(); ++i) {
		for (int j = i+1; j < flavors.size(); ++j) {
			if ( flavors[i] + flavors[j] == sum) {
				r[0] = i;
				r[1] = j;
				return r;
			}
		}
	}
	return r;
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int M, N;
		cin >> M >> N;
		vector<int> flavors(N+1);
		for (int n = 1; n <= N; ++n) cin >> flavors[n];
		assert(flavors.size() >= 2);
		vector<int> choices = buy(flavors, M);
		cout << choices[0] << " " << choices[1] << endl;
	}
	return 0;
}