#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;


int main () {
	int N, M;
	cin >> N; cin >> M;
	const int MAXM = 501;

	vector<bitset<MAXM> > xs(N);
	for (int n = 0; n < N; ++n) {
		cin >> xs[n];
	}

	unsigned long long maxr = 0;
	int nteams = 0;
	for (int i = 0; i < xs.size() - 1; ++i) {
		for (int j = i+1; j < xs.size(); ++j) {
			int r = (xs[i] | xs[j]).count();
			if (r> maxr) {
				maxr = r;
				nteams = 1;
			}
			else if (r == maxr) {
				nteams++;
			}
		}
	}

	cout << maxr << endl << nteams << endl;
}