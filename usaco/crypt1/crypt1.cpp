/*
ID: dolabot1
PROG: crypt1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

/*
Solve 
	* * *   (n1)
x     * *   (n2)
----------
    * * *   (p1)
  * * *     (p2)
---------- 
  * * * *   (r)
*/

// brute force - N^5 * 12 * N (3 check loops) with N <= 10 (solvable within 1 second)

using namespace std;

vector<int> factor(int n) {
	int base = 10;
	vector<int> factors;
	while ( n >= base ) {
		factors.push_back(n % base);
		n /= base;
	}
	factors.push_back(n);
	reverse(factors.begin(), factors.end());
	return factors;
}

bool is_feasible (const int n1d1, const int n1d2, const int n1d3, const int n2d1, const int n2d2, const vector<int> & digits) {
	int n1 = n1d1 * 100 + n1d2 * 10 + n1d3;
	vector<int> p1f = factor(n2d2 * n1);
	vector<int> p2f = factor(n2d1 * n1);
	vector<int> pf = factor(n2d1 * n1 * 10 + n2d2 * n1);
	if (!(p1f.size() == 3 && p2f.size() == 3 && pf.size() == 4)) return false;
	for (int i : p1f) {
		if (find(digits.begin(), digits.end(), i) == digits.end()) {
			return false;
		}
	}
	for (int i : p2f) {
		if (find(digits.begin(), digits.end(), i) == digits.end()) {
			return false;
		}
	}
	for (int i : pf) {
		if (find(digits.begin(), digits.end(), i) == digits.end()) {
			return false;
		}
	}
	return true;
}

int main () {
	// parse input
	ifstream fin ("crypt1.in");
	ofstream fout ("crypt1.out");
	int n = 0;
	fin >> n;
	vector<int> digits;
	for (int i = 0; i <= n-1; ++i) {
		int x;
		fin >> x;
		digits.push_back(x);
	}


	//brute force
	int total = 0;
	for (int n1d1 : digits)
		for (int n1d2 : digits) 
			for (int n1d3 : digits)
				for (int n2d1 : digits)
					for (int n2d2 : digits) {
						if (is_feasible(n1d1, n1d2, n1d3, n2d1, n2d2, digits)) {
							cout << n1d1 << " " << n1d2 << " " << n1d3 << endl << n2d1 << " " << n2d2 << endl;
							total += 1;
						}
					}

	fout << total << endl;
	return 0;
}