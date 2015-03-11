#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int NR, NC, NSTEPS;
vector<string> GRID;
const string MOVES = "ULRD";
vector<int> possible_changes;
int global_best = 1000;

class Solution {
public:
	int r;
	int c;
	int nchanges;
	int allowed_steps;
	Solution(int r_, int c_, int n_, int s_):
		r(r_), c(c_), nchanges(n_), allowed_steps(s_) {}
};

bool is_complete(const Solution & partial) {
	return GRID[partial.r][partial.c] == '*';
}

Solution move(const Solution & partial, const char next_move) {
	char symbol = GRID[partial.r][partial.c];
	int change = (symbol != next_move);
	int nextr = partial.r;
	if (next_move == 'D') nextr++;
	if (next_move == 'U') nextr--;
	int nextc = partial.c;
	if (next_move == 'L') nextc--;
	if (next_move == 'R') nextc++;
	int nextchange = partial.nchanges + change;
	int nextallowed = partial.allowed_steps - 1;
	return Solution(nextr, nextc, nextchange, nextallowed);
}

bool is_valid (const Solution & partial) {
	//if (partial.c == 0)
		//cout << "Verifying Solution: " << partial.r << " " << partial.c << " " << partial.allowed_steps << endl;
	int r = partial.r;
	int c = partial.c;
	return (partial.allowed_steps >= 0) && (r >= 0) && (r < NR) && (c >= 0) && (c < NC);
}

bool is_searched (const Solution & partial) {
	if (partial.nchanges >= global_best) return true;
	return false;
}

void search (Solution partial) {
	if (is_complete(partial)) {
		possible_changes.push_back(partial.nchanges);
		if (partial.nchanges < global_best) {
			global_best = partial.nchanges;
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
				//cout << "Solution: " << partial.r << " " << partial.c << " " << partial.allowed_steps << "\t";
				//cout << "MOVE:" << next_move << "\t";
				//cout << "Candidate: " << candidate.r << " " << candidate.c << " " << candidate.allowed_steps << endl;
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
	for (int r = 0; r < NR; ++r) {
		for (int c = 0; c < NC; ++c) {
			if (GRID[r][c] == '*') {
				global_best = r+c;
				break;
			}
		}
	}
	search(Solution(0, 0, 0, NSTEPS));
	if (possible_changes.empty()) {
		cout << -1 << endl;
	} else {
		cout << *min_element(possible_changes.begin(), possible_changes.end()) << endl;
	}
}