/*
ID: dolabot1
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Block {
public:
	int start;
	int end;
	Block(int s, int e): start(s), end(e) {};
};



vector<Block> repair(const vector<Block> & blocks, const int n) {
	if (blocks.size() <= n) {
		return blocks;
	} else {
		int min_dist_i = 0;
		int min_dist = 1000000;
		for (int i = 0; i <= blocks.size() - 2; ++i) {
			int dist = blocks[i+1].start - blocks[i].end;
			if (dist < min_dist) {
				min_dist = dist;
				min_dist_i = i;
			}
		}
		vector<Block> new_blocks;
		for (int i = 0; i <= blocks.size() - 1; ++i) {
			if (i == min_dist_i) {
				Block b(blocks[i].start, blocks[i+1].end);
				i += 1;
				new_blocks.push_back(b);
			} else {
				new_blocks.push_back(blocks[i]);
			}
		}
		return repair(new_blocks, n);
	}
}

int main () {
	// parse inputs
	ifstream fin ("barn1.in");
	ofstream fout("barn1.out");
	int M, S, C;
	fin >> M >> S >> C;
	vector<int> cow_stalls(C);
	for (int c = 0; c <= C-1; ++c) {
		int cow;
		fin >> cow;
		cow_stalls[c] = cow;
	}
	sort(cow_stalls.begin(), cow_stalls.end());
	// find stall continous blocks
	vector<Block> blocks;
	int start = 0;
	int end = 0;
	for (int i = 1; i <= cow_stalls.size() - 1; ++i) {
		if (cow_stalls[i] == cow_stalls[i-1]+1) {
			end = i;
		} else {
			blocks.push_back(Block(cow_stalls[start], cow_stalls[end]));
			start = i;
			end = i;
		}
	}
	blocks.push_back(Block(cow_stalls[start], cow_stalls[end]));

	vector<Block> barn = repair(blocks, M);
	int n_blocks = 0;
	for (const Block & block : barn) {
		n_blocks += block.end - block.start + 1;
	}
	fout << n_blocks << endl;

	return 0;
}