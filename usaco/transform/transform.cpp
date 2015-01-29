/*
ID: dolabot1
PROG: transform
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<vector<char>> rot90 (const vector<vector<char>> & src) {
	const int n = src.size();
	vector<vector<char>> dst(n, vector<char>(n));
	for (int src_r = 0; src_r <= n-1; ++src_r) {
		int dst_c = n - 1 - src_r;
		for (int i = 0; i <= n - 1; ++i) {
			dst[i][dst_c] = src[src_r][i];
		} 
	}
	return dst;
}

vector<vector<char>> rot180 (const vector<vector<char>> & src) {
	return rot90(rot90(src));
}

vector<vector<char>> rot270 (const vector<vector<char>> & src) {
	return rot90(rot180(src));
}

vector<vector<char>> mirror(const vector<vector<char>> & src) {
	// mirror horizontally along the middle vertical line
	const int n = src.size();
	vector<vector<char>> dst(n, vector<char>(n));
	for (int r = 0; r <= n-1; ++r) {
		for (int c = 0; c <= n-1; ++c) {
			dst[r][c] = src[r][n-1 - c];
		}
	}
	return dst;
}

map<string, vector<vector<char>>> transformed_squares;
const vector<vector<char>> & get_transform(string type, const vector<vector<char>> & square) {
	if (transformed_squares.find(type) == transformed_squares.end()) {
		vector<vector<char>> transformed;
		if (type == "1") {
			transformed = rot90(square);
		} else if (type == "2") {
			transformed = rot180(square);
		} else if (type == "3") {
			transformed = rot270(square);
		} else if (type == "4") {
			transformed = mirror(square);
		} else if (type == "5.1") {
			transformed = rot90(mirror(square));
		} else if (type == "5.2") {
			transformed = rot180(mirror(square));
		} else if (type == "5.3") {
			transformed = rot270(mirror(square));
		}
		transformed_squares[type] = transformed;
	} 
	return transformed_squares[type];
}


int main () {
	ifstream fin ("transform.in");
	ofstream fout ("transform.out");
	int n = 0;
	fin >> n;
	vector<vector<char>> src;
	vector<vector<char>> dst;
	for (int i = 0; i <= n - 1; ++i) {
		string line;
		fin >> line;
		src.push_back(vector<char>(line.begin(), line.end()));
	}
	for (int i = 0; i <= n - 1; ++i) {
		string line;
		fin >> line;
		dst.push_back(vector<char>(line.begin(), line.end()));
	}

	int transform_type = 7;
	if (get_transform("1", src) == dst) {
		transform_type = 1;
	} else if (get_transform("2", src) == dst) {
		transform_type = 2;
	} else if (get_transform("3", src) == dst) {
		transform_type = 3;
	} else if (get_transform("4", src) == dst) {
		transform_type = 4;
	} else if (get_transform("5.1", src) == dst) {
		transform_type = 5;
	} else if (get_transform("5.2", src) == dst) {
		transform_type = 5;
	} else if (get_transform("5.3", src) == dst) {
		transform_type = 5;
	} else if (src == dst) {
		transform_type = 6;
	}

	fout << transform_type << endl;



	return 0;
}