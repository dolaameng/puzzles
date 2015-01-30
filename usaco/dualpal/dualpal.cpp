/*
ID: dolabot1
PROG: dualpal
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

const string BASE_LETTERS = "0123456789ABCDEFGHIJKLMN";

bool is_palindrome(const string & s) {
	int n = s.size();
	for (int i = 0, j = n-1; i < j; ++i, --j) {
		if (s[i] != s[j]) {
			return false;
		}
	}
	return true;
}

string reverse_str(const string & s) {
	string rs(s);
	int n = rs.size();
	for(int i = 0, j = n-1; i < j; ++i, --j) {
		const char c = rs[i];
		rs[i] = rs[j];
		rs[j] = c;
	}
	return rs;
}

string to_base(int n, int b) {
	string s; 
	while (n >= b) {
		int r = n % b;
		n = n / b;
		s.push_back(BASE_LETTERS[r]);
	}
	if (n > 0) {
		s.push_back(BASE_LETTERS[n]);
	}
	return reverse_str(s);
}


int main () {

	ifstream fin ("dualpal.in");
	ofstream fout ("dualpal.out");
	int n, s;
	fin >> n >> s;

	vector<int> found;
	while (found.size() < n) {
		s += 1;
		int pal_times = 0;
		for (int b = 2; b <= 10; ++ b) {
			if (is_palindrome(to_base(s, b))) {
				pal_times++;
			}
			if (pal_times >= 2) {
				break;
			}
		}
		if (pal_times >= 2) {
			found.push_back(s);
		}
	}
	
	for (size_t i = 0; i <= found.size() - 1; ++i) {
		fout << found[i] << endl;
	}
	return 0;
}