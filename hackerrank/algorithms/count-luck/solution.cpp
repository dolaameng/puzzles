#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
	vector<int> rows;
	vector<int> cols;
	int nwands;
	Solution (): nwands(0) {};
	Solution move(int newr, int newc, int nwands) {
		Solution s(*this);
		s.rows.push_back(newr);
		s.cols.push_back(newc);
		s.nwands += nwands;
		return s;
	};
};



bool is_complete(const Solution & s, const int endr, const int endc) {
	int n = s.rows.size();
	int r = s.rows[n-1];
	int c = s.cols[n-1];
	//cout << "checking " << r << "  " << c << endl;

	return (r == endr) && (c == endc);
}

bool is_searched(const int r, const int c, const vector<vector<bool> > & cache) {
	return cache[r][c];
}

Solution search(const vector<string> & grid, 
	const int startr, const int startc,
	const int endr, const int endc) {
	const int R = grid.size();
	const int C = grid[0].size();
	stack<Solution> que;
	Solution init; 
	init.rows.push_back(startr);
	init.cols.push_back(startc);
	que.push(init);

	vector<vector<bool> > searched(R, vector<bool>(C, false));
	searched[startr][startc] = true;

	while (!que.empty()) {
		Solution s = que.top();
		que.pop();
		if (is_complete(s, endr, endc)) {
			return s;
		}
		int n = s.rows.size();
		int sr = s.rows[n-1];
		int sc = s.cols[n-1];
		const string moves = "UDLR";
		vector<int> newrs;
		vector<int> newcs;
		
		for (int m = 0; m < moves.size(); ++m) {
			int newr = s.rows[s.rows.size() - 1];
			int newc = s.cols[s.cols.size() - 1];
			newr += ((moves[m] == 'D') - (moves[m] == 'U'));
			newc += ((moves[m] == 'R') - (moves[m] == 'L'));
			if (newr >= 0 && newr < R && newc >= 0 && newc < C &&
				!is_searched(newr, newc, searched)  && 
				(grid[newr][newc] == '.' || grid[newr][newc] == '*')) {

				newrs.push_back(newr);
				newcs.push_back(newc);
				searched[newr][newc] = true;
			}
		}
		int nwands = (newrs.size() > 1);
		for (int i = 0; i < newrs.size(); ++i) {
			que.push(s.move(newrs[i], newcs[i], nwands));
		}
	}
	return Solution(); // no solution
}

int main() {
	int T, R, C, K;
	int startr, startc, endr, endc;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> R >> C; 
		vector<string> grid(R);
		for (int r = 0; r < R; ++r) {
			cin >> grid[r];
			for (int c = 0; c < grid[r].size(); ++c) {
				if (grid[r][c] == 'M') {
					startr = r;
					startc = c;
				}
				if (grid[r][c] == '*') {
					endr = r;
					endc = c;
				}
			}
		}
		cin >> K;
		Solution s = search(grid, startr, startc, endr, endc);
		if (s.nwands == K) cout << "Impressed" << endl;
		else cout << "Oops!" << endl;
	}
	return 0;
}