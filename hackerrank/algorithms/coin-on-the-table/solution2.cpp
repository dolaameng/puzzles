#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int NR, NC, NSTEPS;
vector<string> GRID;
const string MOVES = "ULRD";
vector<int> possible_changes;
vector<vector<int> > searched;
int global_best = 1000;

class Solution {
public:
	vector<int> rs;
	vector<int> cs;
	vector<int> nchanges;
	int allowed_steps;
	Solution(const vector<int> & rs_, const vector<int> & cs_, const vector<int> & n_, int s_):
		rs(rs_), cs(cs_), nchanges(n_), allowed_steps(s_) {};
};

bool is_complete(const Solution & partial) {
	//cout << "Complete: " << partial.rs.back() << " " << partial.cs.back() << " " << partial.allowed_steps << "\t";
	return GRID[partial.rs.back()][partial.cs.back()] == '*';
}

Solution move(const Solution & partial, const char next_move) {
	char symbol = GRID[partial.rs.back()][partial.cs.back()];
	int change = (symbol != next_move);
	vector<int> nextr(partial.rs);
	if (next_move == 'D') nextr.push_back(nextr.back()+1);
	else if (next_move == 'U') nextr.push_back(nextr.back()-1);
	else nextr.push_back(nextr.back());
	vector<int> nextc(partial.cs);
	if (next_move == 'L') nextc.push_back(nextc.back()-1);
	else if (next_move == 'R') nextc.push_back(nextc.back()+1);
	else nextc.push_back(nextc.back());
	vector<int> nextchange(partial.nchanges);
	nextchange.push_back(nextchange.back()+ change);
	int nextallowed = partial.allowed_steps - 1;
	return Solution(nextr, nextc, nextchange, nextallowed);
}

bool is_valid (const Solution & partial) {
	//if (partial.c == 0)
		//cout << "Verifying Solution: " << partial.r << " " << partial.c << " " << partial.allowed_steps << endl;
	int r = partial.rs.back();
	int c = partial.cs.back();
	return (partial.allowed_steps >= 0) && (r >= 0) && (r < NR) && (c >= 0) && (c < NC);
}

bool is_searched (const Solution & partial) {
	if (partial.nchanges.back() >= global_best) return true;
	int r = partial.rs.back();
	int c = partial.cs.back();
	if (searched[r][c] <= partial.nchanges.back()) return true;

	return false;
}

void search (Solution partial) {
	if (is_complete(partial)) {
		possible_changes.push_back(partial.nchanges.back());
		if (partial.nchanges.back() < global_best) {
			global_best = partial.nchanges.back();
			
		}
		for (int i = 0; i < partial.rs.size(); ++i) {
			int r = partial.rs[i];
			int c = partial.cs[i];
			if (true)
				searched[r][c] = partial.nchanges[i];
			}
		
	} else {
		for (int im = 0; im < MOVES.size(); ++im) {
			char next_move = MOVES[im];
			Solution candidate = move(partial, next_move);
			/*
			if (next_move=='D') { 
				cout << "Solution: " << partial.r << " " << partial.c << "\t";
				cout << "MOVE:" << next_move << "\t";
				cout << "Candidate: " << candidate.r << " " << candidate.c << endl;
			}
			*/
			if (is_valid(candidate) && !is_searched(candidate)) {
				//cout << "Solution: " << partial.rs.back() << " " << partial.cs.back() << " " << partial.allowed_steps << "\t";
				//cout << "MOVE:" << next_move << "\t";
				//cout << "Candidate: " << candidate.rs.back() << " " << candidate.cs.back() << " " << candidate.allowed_steps << endl;
				search(candidate);
			}
		}
	}
}

int main () {
	cin >> NR >> NC >> NSTEPS;
	for (int r = 0; r < NR; ++r) {
		string line; cin >> line;
		GRID.push_back(line);
	}
	searched = vector<vector<int> >(NR, vector<int>(NC, 1000));
	for (int r = 0; r < NR; ++r) {
		for (int c = 0; c < NC; ++c) {
			if (GRID[r][c] == '*') {
				global_best = r+c;
				break;
			}
		}
	}
	search(Solution(vector<int>(1, 0), vector<int>(1, 0), vector<int>(1, 0), NSTEPS));
	if (possible_changes.empty()) {
		cout << -1 << endl;
	} else {
		cout << *min_element(possible_changes.begin(), possible_changes.end()) << endl;
	}
}