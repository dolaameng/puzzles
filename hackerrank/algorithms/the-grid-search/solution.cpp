#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

string hash_fn(const vector<string> & grid, 
	const int rstart, const int rend,
	const int cstart, const int cend) {
	string h = "";
	for (int r = rstart; r < rend; ++r) {
		h += grid[r].substr(cstart, cend-cstart);
	}
	return h;
}

set<string> build_hash(const vector<string> & grid, 
	const int gridnr, const int gridnc,
	const int patnr, const int patnc) {
	set<string> hash_table;
	for (int r = 0; r < gridnr - patnr + 1; ++r) {
		for (int c = 0; c < gridnc - patnc + 1; ++c) {
			string h = hash_fn(grid, r, r+patnr, c, c+patnc);
			//cout << h << endl;
			hash_table.insert(h);
		}
	}
	return hash_table;
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		// input 
		int gridnr, gridnc, patnr, patnc;
		cin >> gridnr >> gridnc;
		vector<string> grid(gridnr);
		for (int r = 0; r < gridnr; ++r) cin >> grid[r];
		cin >> patnr >> patnc;
		vector<string> pattern(patnr);
		for (int r = 0; r < patnr; ++r) cin >> pattern[r];
		// hashing grid
		set<string> grid_hash = build_hash(grid, gridnr, gridnc, patnr, patnc);
		string pat_hash = hash_fn(pattern, 0, patnr, 0, patnc);
		if (grid_hash.find(pat_hash) != grid_hash.end()) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}