/*
ID: dolabot1
PROG: combo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

// brute force: N^3 (combinations) x 6 (checks) with N <= 100 is easy to break

bool is_openable(const vector<int> & pass, const vector<int> & farmer, const vector<int> & master, const int n) {
	bool to_farmer = true;
	bool to_master = true;
	for (size_t i = 0; i < pass.size(); ++i) {
		//to_farmer = to_farmer && (abs(pass[i]-farmer[i])<= 2 || abs(n+pass[i]-farmer[i])%n<= 2 || abs(pass[i]-farmer[i]-n)%n<= 2) ;
		//to_master = to_master && (abs(pass[i]-master[i])<= 2 || abs(n+pass[i]-master[i])%n<= 2 || abs(pass[i]-master[i]-n)%n<= 2) ;
		// cleaner test after reading Brian Dean's code
		to_farmer = to_farmer && (abs(pass[i]-farmer[i])<= 2 || abs(pass[i]-farmer[i])>=n-2) ;
		to_master = to_master && (abs(pass[i]-master[i])<= 2 || abs(pass[i]-master[i])>=n-2) ;
		if (!to_farmer && !to_master) return false;
	}
	return true;
}

int main () {
	//parse int
	ifstream fin ("combo.in");
	ofstream fout ("combo.out");
	int n = 0;
	fin >> n;
	vector<int> farmer;
	for (int i = 0; i < 3; ++i) {
		int d;
		fin >> d;
		farmer.push_back(d);
	}
	vector<int> master;
	for (int i = 0; i < 3; ++i) {
		int d;
		fin >> d;
		master.push_back(d);
	}

	// brute force
	int total = 0;
	for (int d1 = 1; d1 <= n; ++d1)
		for (int d2 = 1; d2 <= n; ++d2) 
			for (int d3 = 1; d3 <= n; ++d3) {
				if (is_openable({d1, d2, d3}, farmer, master, n)) {
					//cout << d1 << "," << d2 << "," << d3 << "\t";
					total += 1;
				}
			}

	fout << total << endl;

	//debug
	/*
	cout << n << endl;
	for (int d : farmer) cout << d << " ";
	cout << endl;
	for (int d : master) cout << d << " ";
	cout << endl;
	*/


	return 0;
}