#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	vector<int> rows;
	vector<int> cols;
	int nwands;
	Solution () nwands(0) {};
};

void search(const vector<string> & grid) {
	//TODO
}

int main() {
	int T, R, C, K;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> R >> C; 
		vector<string> grid(R);
		for (int r = 0; r < R; ++r) cin >> grid[r];
		cin >> K;
		search(grid);
	}
	return 0;
}