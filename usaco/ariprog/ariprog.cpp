/*
ID: dolabot1
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Pair {
public:
	int a;
	int b;
	Pair(int a_, int b_): a(a_), b(b_) {};
	static bool less_than(const Pair & lhs, const Pair & rhs) {
		return lhs.b < rhs.b || (lhs.b == rhs.b && lhs.a < rhs.a);
	}
};

int main () {
	ifstream fin ("ariprog.in");
	ofstream fout ("ariprog.out");
	int N, M;
	fin >> N >> M;
	// pre-compute bisquares
	unordered_set<int> bisqrs;
	for (int p = 0; p <= M; ++p) {
		for (int q = 0; q <= M; ++q) {
			bisqrs.insert(p*p + q*q);
		}
	}
	//for (int s : bisqrs) cout << s << " " ;
	//cout << endl;

	int largest = 2 * M * M;
	vector<Pair> abs;
	//for (int a = 0; a <= (largest-N+1); ++a) {
	for (int a : bisqrs) {
		//for (int b = 1; b <= (largest-a)/(N-1)+1; ++b) {
		for (int b : bisqrs) {
			b -= a;
			//cout << a << " " << b << endl;
			if (b < 1 || b > (largest-a)/(N-1)+1) continue;
			bool is_ariprog = true;
			for (int n = 2; n <= N-1; ++n) {
				if (bisqrs.find(a+n*b) == bisqrs.end()) {
					is_ariprog = false;
					cout << "testing " << a << "  " << b << " " << n << endl;
					break;
				}
			}
			if (is_ariprog) {
				//cout << a << " " << b << endl;
				abs.push_back(Pair(a, b));
			}
		}
	}
	sort(abs.begin(), abs.end(), Pair::less_than);
	if (abs.empty()) {
		fout << "NONE" << endl;
	} else {
		for (const Pair & p : abs) {
			fout << p.a << " " << p.b << endl;
		}
	}
	return 0;
}