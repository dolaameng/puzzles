#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

string grid2str(const vector<string> & g) {
	string s = "";
	for (int r = 0; r < g.size(); ++r) s += g[r];
	return s;
}

vector<string> subgrid(const vector<string> & g,
				const int r0, const int r1, 
				const int c0, const int c1) {
	vector<string> sub;
	for (int r = r0; r < r1; ++r) sub.push_back(g[r].substr(c0, c1-c0));
	return sub;
}

// incremental hashing
bool search(const vector<string> & grid, const string & pat, 
	const int gridnr, const int gridnc, const int patnr, const int patnc) {
	//string s = grid2str(grid, 0, patnr, 0, patnc);
	
	for (int c = 0; c < gridnc - patnc + 1; ++c) {
		vector<string> sub = subgrid(grid, 0, patnr, c, c+patnc);
		string s = grid2str(sub);
		if (s == pat) return true;
		for (int r = 1; r < gridnr - patnr + 1; ++r) {	
			s = s.substr(patnc) + grid[r+patnr].substr(c, patnc);
			if (s == pat) return true;
		}
	}
	return false;
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int gridnr, gridnc, patnr, patnc;
		cin >> gridnr >> gridnc;
		vector<string> grid(gridnr);
		for (int r = 0; r < gridnr; ++r) cin >> grid[r];
		cin >> patnr >> patnc;
		vector<string> pattern(patnr);
		//cout << patnr << " " << patnc << endl;
		for (int r = 0; r < patnr; ++r) cin >> pattern[r];

		string pat = grid2str(pattern);
		//cout << pat;
		cout << search(grid, pat, gridnr, gridnc, patnr, patnc) << endl;
		
	}
	return 0;
}