/*
ID: dolabot1
PROG: milk3
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

// use backtracking

int A, B, C;
vector<int> capacities;

set<vector<int>> searched;
set<vector<int>> solutions;

bool is_explored(const vector<int> & partial) {
	return searched.find(partial) != searched.end();
}

bool is_complete(const vector<int> & partial) {
	return partial[0] == 0 || partial[1] == B;
}

set<vector<int>> next(const vector<int> & partial) {
	set<vector<int>> candidates;
	for (int from = 0; from <= 2; ++from) {
		for (int to = 0; to <= 2; ++to) {
			if (from != to && partial[from] > 0 && partial[to] < capacities[to]) {
				vector<int> candidate(partial);
				int amount = min(partial[from], capacities[to]-partial[to]);
				candidate[from] -= amount;
				candidate[to] += amount;
				candidates.insert(candidate);
			}
		}
	}
	return candidates;
}

void explore(const vector<int> & partial) {
	
	assert (partial[0] + partial[1] + partial[2] == C);
	//for(int i : partial) cout << i << " ";
	//cout << endl;
	
	if (is_explored(partial)) {
		return;
	}
	else  {
		searched.insert(partial);
		if (is_complete(partial)) {
			solutions.insert(partial);
		} 
		for (const vector<int> & candidate : next(partial)) {
			if (is_explored(candidate)) continue;
			//cout << "candidate: ";
			//for(int i : candidate) cout << i << " ";
			//cout << endl;
			explore(candidate);
		}
	}
} 


int main () {
	ifstream fin ("milk3.in");
	ofstream fout ("milk3.out");
	
	fin >> A >> B >> C;
	capacities = {A, B, C};
	
	vector<int> initial = {0, 0, C};
	explore(initial);
	/*
	for (const vector<int> & candidate : next(vector<int>({0, 9, 1}))) {
		cout << "candidate: ";
		for(int i : candidate) cout << i << " ";
		cout << endl;
	}
	
	for (const vector<int> & s : solutions) {
		cout << "solution: ";
		for(int i : s) cout << i << " ";
		cout << endl;
	}
	*/
	vector<int> answers;
	for (const vector<int> & s : solutions) {
		if (s[0] == 0) answers.push_back(s[2]);
	}
	sort(answers.begin(), answers.end());
	for (int i = 0; i < answers.size()-1; ++i) {
		fout << answers[i] << " ";
	} 
	fout << answers[answers.size() -1] << endl;

	return 0;
}