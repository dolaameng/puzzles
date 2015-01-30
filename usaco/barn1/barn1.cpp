/*
ID: dolabot1
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

int main () {
	//parse inputs
	ifstream fin ("barn1.in");
	ofstream fout("barn1.out");
	int M, S, C;
	fin >> M >> S >> C;
	vector<int> cow_stalls(S);
	for (int c = 0; c <= C-1; ++c) {
		int cow;
		fin >> cow;
		cow_stalls[cow] = 1;
	}

	for(int s = 0; s <= S-1; ++s) {
		cout << cow_stalls[s];
	}
	cout << endl;

	return 0;
}