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
#include <set>
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
	set<int> bisqrs;
	for (int p = 0; p <= M; ++p) {
		for (int q = 0; q <= M; ++q) {
			bisqrs.insert(p*p + q*q);
		}
	}
	vector<int> nums(bisqrs.begin(), bisqrs.end());
	//for (int s : nums) cout << s << " " ;
	//cout << endl;
	for (int i = 0; i <= nums.size() - 1; ++i) {
		for (int j = i+1; j <= nums.size() - 1; ++j) {
			int a = nums[i];
			int b = nums[j] - a;
		}
	}
	
	
	return 0;
}