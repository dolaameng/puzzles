#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int dist_to_palin(const string & s) {
	int i = 0, j = s.size()-1;
	int dist = 0;
	while (i < j) {
		dist += abs(s[i] - s[j]);
		++i;
		--j;
	}
	return dist;
}

int main() {
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		cout << dist_to_palin(s) << endl;
	}
	return 0;
}
