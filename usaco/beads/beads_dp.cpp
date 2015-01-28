/*
ID: dolabot1
PROG: beads
LANG: C++11
*/

// Dynamic Programming Solution by Daniel Bundala


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class RedBlue {
public:
	int blue;
	int red;
	RedBlue(): blue(0), red(0) {};
};

int main () {
	ifstream fin ("beads.in");
	ofstream fout ("beads.out");
	int n;
	string tmp;
	fin >> n >> tmp;
	const string s = tmp + tmp;

	vector<RedBlue> left(n*2 + 1);
	left[0].red = left[0].blue = 0;
	for (int i = 1; i <= 2 * n ; ++i) {
		if (s[i-1] == 'r') {
			left[i].red = left[i-1].red + 1;
			left[i].blue = 0;
		} else if (s[i-1] == 'b') {
			left[i].blue = left[i-1].blue + 1;
			left[i].red = 0;
		} else {
			left[i].red = left[i-1].red + 1;
			left[i].blue = left[i-1].blue + 1;
		}
	}

	vector<RedBlue> right(n*2 + 1);
	right[2*n].red = right[2*n].blue = 0;
	for (int i = 2*n - 1; i >= 0; i--) {
		if (s[i] == 'r') {
			right[i].red = right[i+1].red + 1;
			right[i].blue = 0;
		} else if (s[i] == 'b') {
			right[i].blue = right[i+1].blue + 1;
			right[i].red = 0;
		} else {
			right[i].red = right[i+1].red + 1;
			right[i].blue = right[i+1].blue + 1;
		}
	}

	int maxbeads = 0;
	for (int i = 0; i < 2 * n ; i++) {
		maxbeads = max(maxbeads, 
						max(left[i].red, left[i].blue) 
						+ max(right[i].red, right[i].blue));
	}
	maxbeads = min(maxbeads, n); // check same color necklace
	//cout << maxbeads;
	fout << maxbeads << endl;

	return 0;
}