#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<char> > profile (const vector<vector<char> > & grid, const int N) {
	vector<vector<char> > cavity(grid);
	for (int r = 1; r < N-1; ++r) {
		for (int c = 1; c < N-1; ++c) {
			if (grid[r-1][c] < grid[r][c] && grid[r+1][c] < grid[r][c]
				&& grid[r][c-1] < grid[r][c] && grid[r][c+1] < grid[r][c]) {
				cavity[r][c] = 'X';
			}
		}
	}
	return cavity;
}

int main () {
	int N; cin >> N;
	vector<vector<char> > grid(N, vector<char>(N, 0));
	for (int r = 0; r < N; ++r) {
		string row; cin >> row;
		for (int c = 0; c < N; ++c) {
			grid[r][c] = row[c];
		}
	}

	vector<vector<char> > cavity_map = profile(grid, N);
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			cout << cavity_map[r][c];
		}
		cout << endl;
	}
}