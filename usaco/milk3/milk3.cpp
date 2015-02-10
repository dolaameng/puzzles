/*
ID: dolabot1
PROG: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <set>

using namespace std;

// use backtracking

int A, B, C;

class Solution {
public:
	int a;
	int b;
	int c;
	Solution(int a_, int b_, int c_): a(a_), b(b_), c(c_) {};
	bool operator < (const Solution & rhs) const {
		return a*20*20+b*20+c < rhs.a*20*20+rhs.b*20+rhs.c;
	}
	bool is_complete() const {
		// exclude initial position
		return (a+b > 0) && (a == 0 || b == B);
	}
	int operator[](const size_t i) {
		if (i == 0) return a;
		else if (i == 1) return b;
		else return c;
	}
};

set<Solution> complete_solutions;

void explore(const Solution & partial) {
	if (partial.is_complete()) {
		complete_solutions.insert(partial);
	} else if (complete_solutions.find(partial) != complete_solutions.end()) {
		return;
	} else {
		for (int from = 0; from <= 2; ++from) {
			for (int to = 0; to <= 2; ++to) {
				//TODO
			}
		}
	}
}

int main () {
	ifstream fin ("milk3.in");
	ofstream fout ("milk3.out");
	fin >> A >> B >> C;
	
	complete_solutions.insert(Solution(0, 0, C));
	explore(Solution(0, 0, C));

	return 0;
}