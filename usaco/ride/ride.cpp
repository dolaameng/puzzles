/*
ID: dolabot1
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int str_product_mod(const string & str, const int mod = 47) {
	int product = 1;
	for (const char & c : str) {
		product = product * (c - 'A' + 1) % mod;
	}
	return product;
}

int main() {
	ifstream fin("ride.in");
	ofstream fout("ride.out");
	string comet, group;
	fin >> comet >> group;

	bool decision = (str_product_mod(comet) == str_product_mod(group));
	if (decision) {
		fout << "GO" << endl;
	} else {
		fout << "STAY" << endl;
	}

	return 0;
}