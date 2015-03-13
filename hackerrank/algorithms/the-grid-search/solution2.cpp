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

bool search(const string & pat, const char first, const char last,
	const vector<string> & grid, 
	const int gridnr, const int gridnc,
	const int patnr, const int patnc) {
	set<string> hash_table;
	for (int r = 0; r < gridnr - patnr + 1; ++r) {
		for (int c = 0; c < gridnc - patnc + 1; ++c) {
			if (grid[r][c] == first && grid[r+patnr-1][c+patnc-1]==last){
				string h = hash_fn(grid, r, r+patnr, c, c+patnc);
				if (h == pat) return true;
			}
		}
	}
	return false;
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
		//cout << patnr << " " << patnc << endl;
		for (int r = 0; r < patnr; ++r) cin >> pattern[r];
		// hashing grid
		string pat_hash = hash_fn(pattern, 0, patnr, 0, patnc);
		//cout << pat_hash << endl;
		bool found = search(pat_hash,
			pattern[0][0], pattern[patnr-1][patnc-1],
			grid, gridnr, gridnc, patnr, patnc);
		if (found) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}