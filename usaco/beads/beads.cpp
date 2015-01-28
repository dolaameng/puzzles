/*
ID: dolabot1
PROG: beads
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
	ifstream fin ("beads.in");
	ofstream fout ("beads.out");

	unsigned int n;
	string beads;
	fin >> n >> beads;

	// bias used to rotate the string 
	// and then take the break as always at the beginning
	int maxbeads = -1;
	for(int b = 0; b <= n-1; ++b) {
		// end 1 counting
		int nbeads = 1;
		char color = beads[b%n]; // i = 0	
		int i = 1;
		for(i = 1; i <= n-1; ++i) {
			char new_color = beads[(i+b)%n];
			if (color == new_color) {
				nbeads += 1;
			} else if (color == 'w') {
				nbeads += 1;
				color = new_color;
			} else if (new_color == 'w') {
				nbeads += 1;
			} else {
				break;
			}
		}
		// end 2 counting
		if (i < n-1) {
			nbeads += 1;
			color = beads[(n-1+b)%n];
			for (int j = n-2; j > i-1; --j) {
				char new_color = beads[(j+b)%n];
				if (color == new_color) {
					nbeads += 1;
				} else if (color == 'w') {
					nbeads += 1;
					color = new_color;
				} else if (new_color == 'w') {
					nbeads += 1;
				} else {
					break;
				}
			}
		}
		if (nbeads > maxbeads) {
			maxbeads = nbeads;
		}
		/*
		for (int t = 0; t <= n-1; ++t) {
			cout << beads[(t+b) %n];
		}
		cout << endl << i << " : " << nbeads << endl;
		*/
	}
	fout << maxbeads << endl;
	return 0;
}