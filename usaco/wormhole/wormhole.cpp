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


int trace(const vector<vector<int>> & A) {
	const size_t n = A.size();
	int tr = 0;
	for (int d = 0; d < n; ++d) {
		tr += A[d][d];
	}
	return tr;
}

vector<vector<int>> multiply(const vector<vector<int>> & A, const vector<vector<int>> & B) {
	const size_t n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			int value = 0;
			for (int k = 0; k < n; ++k) {
				value += A[r][k] * B[k][c];
			}
			C[r][c] = value;
		}
	}
	return C;
}

int row_sum(const vector<vector<int>> M, int r) {
	int total = 0;
	for (int c = 0; c < M.size(); ++c) {
		total += M[r][c];
	}
	return total;
}

int col_sum(const vector<vector<int>> M, int c) {
	int total = 0;
	for (int r = 0; r < M.size(); ++r) {
		total += M[r][c];
	}
	return total;
}

bool is_loop(const vector<int> & pair, const vector<vector<int>> & graph) {
	
	vector<vector<int>> A;
	for (int r = 0; r < graph.size(); ++r) A.push_back(graph[r]);
	for (int i = 0; i < pair.size(); i+=2) {
		if (col_sum(graph, pair[i]) != 0 ) {
			A[pair[i]][pair[i+1]] = 1;
		}
		
		if (col_sum(graph, pair[i+1]) != 0) {
			A[pair[i+1]][pair[i]] = 1;
		}
	}
	print_vector(pair);
	print_matrix(graph);
	print_matrix(A);
	vector<vector<int>> AA = A;
	for (int it = 0; it < pair.size(); ++it) {
		if (trace(AA) > 0) {
			cout << "solution: " << endl;
			print_matrix(AA);
			return true;
		}
		AA = multiply(AA, A);
	}
	cout << "false" << endl;
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
	vector<vector<int>> graph(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			const WormHole & hi = holes[i];
			const WormHole & hj = holes[j];
			if (hi.x < hj.x && hi.y == hj.y) graph[i][j] = 1;
		}
	}

	vector<vector<int>> pairs;
	vector<int> resource;
	for (int r = 0; r < n; ++r) resource.push_back(r);
	all_pairs(vector<int>(), resource, n, pairs);

	vector<int> solutions;
	for (int p = 0; p < pairs.size(); ++p) {
		if (is_loop(pairs[p], graph)) {
			solutions.push_back(p);
		}
	}
	fout << solutions.size() << endl;


	// debug 
	/*
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	
	n = 12;
	cout << n << endl;
	
	cout << pairs.size() << endl;
	*/

	vector<vector<int>> M = {{0, 0, 0, 1}, 
							{0, 0, 1, 0}, 
							{0, 1, 0, 0}, 
							{1, 0, 0, 0}};
	//print_matrix(multiply(multiply(M, M), M));
	return 0;
}