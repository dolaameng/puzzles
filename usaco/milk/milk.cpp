/*
ID: dolabot1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Farm {
public:
	int price;
	int unit;
	Farm(): price(0), unit(0) {};
	Farm(int p, int u) : price(p), unit(u) {};
public:
	static bool priceLT(const Farm & lhs, const Farm & rhs) {
		return lhs.price < rhs.price;
	}
};

int main () {
	//parse input
	ifstream fin ("milk.in");
	ofstream fout ("milk.out");
	int total, n = 0;
	vector<Farm> farms;
	fin >> total >> n;
	for (int i = 0; i <= n-1; ++i) {
		int price, unit;
		fin >> price >> unit;
		farms.push_back(Farm(price, unit));
	}
	//sort farms by prices
	sort(farms.begin(), farms.end(), Farm::priceLT);

	int payment = 0;
	for (int i = 0; i <= n-1; ++i) {
		int units = min(farms[i].unit, total);
		total -= units;
		payment += units * farms[i].price;
		if (total == 0) break;
	}

	fout << payment << endl;

	return 0;
}