#include <iostream>
#include <string>
#include <bitset>
using namespace std;

bool has_common(const string & s1, const string & s2) {
	bitset<26> b1;
	bitset<26> b2;
	for (int i = 0; i < s1.size(); ++i) b1.set(s1[i]-'a');
	for (int i = 0; i < s2.size(); ++i) b2.set(s2[i]-'a');
	return (b1&b2).count() > 0;
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		string s1, s2;
		cin >> s1 >> s2;
		if (has_common(s1, s2)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}