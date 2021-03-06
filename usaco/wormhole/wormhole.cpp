/*
ID: dolabot1
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// JUST AFTER FINISHING the draft of version1, I realized it could be easier to model it as a directed graph.
// brute force: 
// (1) N objects (<= 12) to form N/2 pairs, there are N! / (2!^(N/2)) / (N/2)! <= 10e5 of possible pairing - use DFS to generate all
// for each possible pairing - check loop 

void print_vector(const vector<int> & v) {
	cout << endl;
	for (int i : v) cout << i << " ";
	cout << endl;
}

void print_matrix(const vector<vector<int>> & m) {
	cout << endl;
	for (const vector<int> & r : m) {
		for (int i : r) cout << i << " ";
		cout << endl;
	}
}

class WormHole {
public:
	int x;
	int y;
	WormHole(int x_, int y_): x(x_), y(y_) {}; 
	static bool lessthan(const WormHole & lhs, const WormHole & rhs) {
		if (lhs.y == rhs.y) return lhs.x < rhs.x;
		else return lhs.y < rhs.y;
	}
};


void all_pairs(const vector<int> & partial, const vector<int> resource, const int N, vector<vector<int>> & pairs) {
	assert (partial.size() % 2 == 0);
	if (partial.size() == N) { // complete solution
		pairs.push_back(partial);
	} else {
		for (int i = 0; i < resource.size(); ++i) {
			for (int j = i+1; j < resource.size(); ++j) {
				vector<int> candidate(partial);
				candidate.push_back(resource[i]);
				candidate.push_back(resource[j]);
				vector<int> new_resource;
				for(int r = 0; r < resource.size(); ++r) {
					if ( r>i && r!=j) new_resource.push_back(resource[r]);
				}
				all_pairs(candidate, new_resource, N, pairs);
			}
		}
	}
}

bool bt_has_cycle(const vector<int> & partial, const vector<vector<int>> & pairs, 
					const vector<vector<int>> & graph) {
	const int n = partial.size();
	bool repeat = false;
	for (int j = n-3; j >= 0; j-=2) {
		if (partial[j] == partial[n-1]){
			repeat = true;
			break;
		}
	}
	if (n > 1 && repeat) {
		print_vector(partial);
		return true;
	} else {
		const vector<vector<int>> * resource = &pairs;
		if (n % 2 == 1) resource = &graph;
		for (int next = 0; next < pairs.size(); ++next) {
			if ((*resource)[partial[n-1]][next] == 0) continue;
			vector<int> candidate(partial);
			candidate.push_back(next);
			if (bt_has_cycle(candidate, pairs, graph)) return true;
		}
		return false;
	}
}

// realizing modeling by a graph is not a general idea, as 
// you need to distinguish between wormhole jump and normal move
bool is_loop(const vector<int> & pair_path, const vector<vector<int>> & graph) {
	// build the adjancent matrix for pair path
	const size_t n = graph.size();
	vector<vector<int>> pairs(n, vector<int>(n, 0));
	for (int i = 0; i < pair_path.size(); i+=2) {
		pairs[pair_path[i]][pair_path[i+1]] = 1;
		pairs[pair_path[i+1]][pair_path[i]] = 1;
	}
	for (int start = 0; start < n; ++start) {
		vector<int> partial;
		partial.push_back(start);
		if ( bt_has_cycle(partial, pairs, graph) )
			return true;
	}
	return false;
}



int main () {
	// input and output
	ifstream fin ("wormhole.in");
	ofstream fout ("wormhole.out");
	int n;
	vector<WormHole> holes;
	fin >> n;
	assert (n % 2 == 0 && n <= 12);
	for (int i = 0; i < n; ++i) {
		int x, y;
		fin >> x >> y;
		holes.push_back(WormHole(x, y));
	}

	// build the connection graph based on x, y coords 
	// if i.x < j.x and i.y == j.y
	sort(holes.begin(), holes.end(), WormHole::lessthan);
	//for (const WormHole & wh : holes) {
	//	cout << wh.x << "," << wh.y << endl;
	//}
	vector<vector<int>> graph(n, vector<int>(n, 0));
	for (int i = 0; i < n-1; ++i)  {
		const WormHole & hi = holes[i];
		const WormHole & hj = holes[i+1];
		if (hi.x < hj.x && hi.y == hj.y) graph[i][i+1] = 1;
		
	}
	//print_matrix(graph);

	// generate all pairing
	vector<vector<int>> pairs;
	vector<int> resource;
	for (int r = 0; r < n; ++r) resource.push_back(r);
	all_pairs(vector<int>(), resource, n, pairs);

	// solutions by brute force explore

	vector<int> solutions;
	for (int p = 0; p < pairs.size(); ++p) {
		if (is_loop(pairs[p], graph)) {
			solutions.push_back(p);
			//print_vector(pairs[p]);
		}
	}
	fout << solutions.size() << endl;


	return 0;
}