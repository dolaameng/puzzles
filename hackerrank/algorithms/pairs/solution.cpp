#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	int N, K;
	cin >> N >> K;
	set<int> xs;
	for (int i = 0; i < N; ++i) {
		int x; cin >> x;
		xs.insert(x);
	}
	int total = 0;
	for (set<int>::iterator it = xs.begin(); it != xs.end(); ++it) {
		int x = *it;
		if (xs.find(x+K) != xs.end()) {
			total++;
		}
	}
	cout << total << endl;
	return 0;
}