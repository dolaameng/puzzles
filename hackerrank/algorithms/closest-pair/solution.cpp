#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;   
    vector<int> xs(n);
    for (int i = 0; i < n; ++i) cin >> xs[i];
    sort(xs.begin(), xs.end());

	int min_dist = xs[n-1]-xs[0];
	vector<vector<int>> pairs;
	for (int i = 0; i < n-1; ++i) {
		int d = xs[i+1] - xs[i];
		if (d < min_dist) {
			min_dist = d;
			pairs.clear();
			pairs.push_back(vector<int>({xs[i], xs[i+1]}));
		} else if (d == min_dist) {
			pairs.push_back(vector<int>({xs[i], xs[i+1]}));
		}
	}

	for (int i = 0; i < pairs.size(); ++i) {
		cout << pairs[i][0] << " " << pairs[i][1] << " ";
	}
	cout << endl;
    return 0;
}
