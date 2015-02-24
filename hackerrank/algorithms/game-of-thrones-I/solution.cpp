#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool ana_palin(const string & s) {
	vector<int> char_cnts(26, 0);
	for (int i = 0; i < s.size(); ++i) {
		const char c = s[i];
		char_cnts[c-'a']++;
	}
	int n_odds = 0;
	for (int i = 0; i < char_cnts.size() ; ++i) {
		n_odds += (char_cnts[i] % 2 == 1);
	}
	return n_odds <= 1;
}

int main () {
	string s; cin >> s;
	if (ana_palin(s)) cout << "YES" << endl;
	else cout << "NO" << endl;
}