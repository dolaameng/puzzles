#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <set>
#include <utility>
using namespace std;

int search(const int D, const int P) {
	set<pair<int, int> > r;
	if (D < 0) return 0;
	if (P == 0) return (D == 0) ? 1: 4;
	//int total = 0;
	for (int a = 1; a*a <= abs(P); ++a) {
		if (P % a != 0) continue;
		//cout << "explore:" << a << " " << P/a << endl;
		int b = P / a;
		if (abs(a-b) == D) {
			//cout << "confirm: " << a << " " << b << endl;
			//total += (a!=b) ? 4 : 2;
			r.insert(make_pair(a, b));
			r.insert(make_pair(b, a));
			r.insert(make_pair(-a, -b));
			r.insert(make_pair(-b, -a));
		}
	}
	return r.size();
}

int main() {
	int T, D, P;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> D >> P;
		cout << search(D, P) << endl;
	}
	return 0;
}