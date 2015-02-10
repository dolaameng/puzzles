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
#include <algorithm>
#include <set>

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
	vector<bool> bisqrs(M*M*2+1, false);
	set<int> nnums;
	for (int p = 0; p <= M; ++p) {
		for (int q = 0; q <= M; ++q) {
			int n = p*p + q*q;
			bisqrs[n] = true;
			nnums.insert(n);
		}
	}
	vector<int> nums(nnums.begin(), nnums.end());
	//for (int s : nums) cout << s << " " ;
	//cout << endl;

	int largest = 2 * M * M;
	vector<Pair> abs;
	for (int i = 0; i <= nums.size() - 1; ++i) {
		int a = nums[i];
		for (int j = i+1; j <= nums.size() - 1; ++j) {
			int b = nums[j]-a;
			//cout << a << " " << b << endl;
			if (b > (largest-a)/(N-1)+1) continue;
			bool is_ariprog = true;
			for (int n = 2; n <= N-1; ++n) {
				if (!bisqrs[a+n*b]) {
					is_ariprog = false;
					//cout << "testing " << a << "  " << b << " " << n << endl;
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