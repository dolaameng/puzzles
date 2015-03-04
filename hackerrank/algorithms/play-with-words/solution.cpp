#include <iostream>
#include <string>
#include <vector>
using namespace std;

int max_palin(const string & str) {
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
	return table[0][N-1];
}

int max_palin_sep(const string & str) {
	int max_prod = 0;
	for (int i = 1; i <= str.size()-1; ++i) {
		string s1 = str.substr(0, i);
		string s2 = str.substr(i);
		int cur_prod = max_palin(s1) * max_palin(s2);
		if (cur_prod > max_prod) {
			max_prod = cur_prod;
		}
	}
	return max_prod;
}

int main() {
	string str;
	cin >> str;
	cout << max_palin_sep(str) << endl;
	return 0;
}