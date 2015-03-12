// This is one of the examples where breath-first search 
// could be better than depth-first, because we are 
// looking for minimum cost solution
// FOR both DF and BF search, early prunning is the KEY!!!

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
using namespace std;

int NR, NC, NSTEPS;
vector<string> GRID;
int TARGETR, TARGETC;
const string MOVES = "ULRD";


class Solution {
public:
	int row;
	int col;
	int nsteps;
	int nchanges;
	Solution(int r, int c, int n, int nc): row(r), col(c), nsteps(n), nchanges(nc) {};
	bool operator < (const Solution & rhs) const {
		bool r = (nchanges > rhs.nchanges) || (nchanges == rhs.nchanges && mat_dist() < rhs.mat_dist());
		return r;
	};
	int mat_dist () const {
		return abs(TARGETR - row) + abs(TARGETC - col);;
	}
};

class Record {
public:
	int nsteps;
	int nchanges;
	Record(int ns, int nc): nsteps(ns), nchanges(nc) {};
};

vector<vector<Record> > searched;



bool is_complete (const Solution & s) {
	return GRID[s.row][s.col] == '*';
}

bool is_valid (const Solution & s) {
	int md = s.mat_dist();
	return (s.nsteps >= md) && (s.row >= 0) && (s.row < NR) && (s.col >= 0) && (s.col < NC);
}

bool is_better(const Solution & s) {
	Record r = searched[s.row][s.col];
	//if (r.nsteps <= s.nsteps && r.nchanges >= s.nchanges) {
	if ( (s.nchanges < r.nchanges) || (s.nchanges==r.nchanges && s.nsteps > r.nsteps) ) {
		searched[s.row][s.col] = Record(s.nsteps, s.nchanges);
		return true;
	}
	return false;
}

Solution next_move(const Solution & s, const char move, const int change) {
	Solution nexts(s.row, s.col, s.nsteps-1, s.nchanges+change);
	nexts.row += (move == 'D') - (move == 'U');
	nexts.col += (move == 'R') - (move == 'L');
	//if (move == 'U') nexts.row--;
	//if (move == 'D') nexts.row++;
	//if (move == 'L') nexts.col--;
	//if (move == 'R') nexts.col++;
	return nexts;
}

// breath first search
Solution search () {
	priority_queue<Solution> que;
	que.push(Solution(0, 0, NSTEPS, 0));
	while (!que.empty()) {
		Solution s = que.top(); que.pop();
		//cout << "current: " << s.row << " " << s.col << " " << s.nsteps << " " << s.nchanges << endl;
		if (is_complete(s)) return s;
		else {
			for (int im = 0; im < MOVES.size(); ++im) {
				char move = MOVES[im];
				int change = (move != GRID[s.row][s.col]);
				Solution nexts = next_move(s, move, change);
				if (is_valid(nexts) && is_better(nexts)) {
					que.push(nexts);
				}
			}
		}
	}
	return Solution(-1, -1, -1, -1);
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
				TARGETR = r; TARGETC = c;
				break;
			}
		}
	}
	searched = vector<vector<Record> >(NR, vector<Record>(NC, Record(0, 1000)));
	
	Solution solution = search();
	//cout << solution.row << " " << solution.col << " " << solution.nsteps << " " << solution.nchanges << endl;
	cout << solution.nchanges << endl;
}