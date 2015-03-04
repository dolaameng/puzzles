#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int> > max_palin(const string & str) {
	const int N = str.size();
	vector<vector<int> > table(N, vector<int>(N, 1));
	for (int l = 1; l <= N-1; ++l) {
		for (int i = 0; i < N-l; ++i) {
			int a = i; int b = i + l;
			if (l == 1) {
				if (str[a] == str[b]) table[a][b] = 2;
				else table[a][b] = 1;
			} else {
				if (str[a] == str[b]) table[a][b] = table[a+1][b-1] + 2;
				else table[a][b] = max(table[a+1][b], table[a][b-1]);
			}
		}
	}
	return table;
}

int max_palin_sep(const string & str) {
	vector<vector<int> > table = max_palin(str);
	const int N = str.size();
	int max_len = 0;
	for (int s = 0; s < N-1; ++s) {
		int len = table[0][s] * table[s+1][N-1];
		if (len > max_len) max_len = len;
	}
	return max_len;
}

int main() {
	string str;
	cin >> str;
	cout << max_palin_sep(str) << endl;
	return 0;
}