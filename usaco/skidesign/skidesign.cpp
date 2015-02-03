/*
ID: dolabot1
PROG: skidesign
LANG: C++11
*/

// I misunderstood the problem as it must be using mass removed from one hill to put on another. It is not a constraint.

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>


using namespace std;



int main () {
	// input output
	ifstream fin ("skidesign.in");
	ofstream fout ("skidesign.out");
	const int LMT = 17;
	int n; fin >> n;
	vector<int> hts;
	for (int i = 0; i < n; ++i){
		int h; fin >> h; hts.push_back(h);
	}

	// brute force all intervals

	int minh = *min_element(hts.begin(), hts.end());
	int maxh = *max_element(hts.begin(), hts.end());

	vector<int> costs;
	for(int low = minh, high = minh + 17; high <= maxh; ++low, ++high) {
		int cost = 0;
		for (int h : hts) {
			if (h < low) cost += (h-low)*(h-low);
			else if (h > high) cost += (high-h)*(high-h);
		}
		costs.push_back(cost);
	}
	//for (int c : costs) cout << c << endl;
	fout << *min_element(costs.begin(), costs.end()) << endl;
	return 0;
}