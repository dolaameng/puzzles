#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	const int NMAX = 103;
	int n, m;
	cin >> n;
	vector<int> xs(n);
	for (int i = 0; i < n; ++i) cin >> xs[i];
	cin >> m;
	vector<int> ys(m);
	for (int i = 0; i < m; ++i) cin >> ys[i];
	int min_value = *min_element(ys.begin(), ys.end());
	
	vector<int> setx(NMAX, 0);
	for (int i = 0; i < xs.size(); ++i) {
		setx[xs[i]-min_value]++;
	}
	vector<int> sety(NMAX, 0);
	for (int i = 0; i < ys.size(); ++i) {
		sety[ys[i]-min_value]++;
	}
	vector<int> missing;
	for (int i = 0; i < NMAX; ++i) {
		if (sety[i] > setx[i]) {
			missing.push_back(i+min_value);
		}
	}
	for (int i = 0; i < missing.size() - 1; ++i) cout << missing[i] << " ";
	cout << missing[missing.size()-1] << endl;
}