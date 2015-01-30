/*
ID: dolabot1
PROG: palsquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>



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
	// parse base b
	ifstream fin ("palsquare.in");
	ofstream fout ("palsquare.out");
	int b;
	fin >> b;
	const int n = 300;

	for (int i = 1; i <= n; ++i) {
		int nsqr = i * i;
		string bsqr_str = to_base(nsqr, b);
		if (is_palindrome(bsqr_str)) {
			//cout << to_base(i, b) << " " << bsqr_str << endl;
			fout << to_base(i, b) << " " << bsqr_str << endl;
		}
	}

	return 0;
}