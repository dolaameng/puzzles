/*
ID: dolabot1
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;


map<char, int> ttr_vocab = {{'A', 2}, {'B', 2}, {'C', 2},
							{'D', 3}, {'E', 3}, {'F', 3}, 
							{'G', 4}, {'H', 4}, {'I', 4}, 
							{'J', 5}, {'K', 5}, {'L', 5}, 
							{'M', 6}, {'N', 6}, {'O', 6},
							{'P', 7}, {'R', 7}, {'S', 7}, 
							{'T', 8}, {'U', 8}, {'V', 8}, 
							{'W', 9}, {'X', 9}, {'Y', 9}};
long long ttr_hash(const string & word) {
	long long h = 0;
	for (char c : word) {
		h = h*10 + ttr_vocab[c];
	}
	return h;
}

int main () {
	// build dict hashing - already sorted
	ifstream dict ("dict.txt");
	string word;
	unordered_map<long long, vector<string>> word_hash;
	while (dict >> word) {
		long long h = ttr_hash(word);
		if (word_hash.find(h) != word_hash.end()) {
			word_hash[h].push_back(word);
		} else {
			word_hash[h] = vector<string>(1, word);
		}
	}

	// parse input and output
	ifstream fin ("namenum.in");
	ofstream fout ("namenum.out");
	long long q = 0;
	fin >> q;
	cout << q << endl;
	const vector<string> & found_words = word_hash[q];
	if (found_words.empty()) {
		fout << "NONE" << endl;
		cout << "NONE" << endl;
	} else {
		for (int i = 0; i <= found_words.size() - 1; ++i) {
			fout << found_words[i] << endl;
			cout << found_words[i] << endl;
		}
	}

	return 0;
}