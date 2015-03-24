#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<string> substrs(const string & s) {
	//cout << "debug:" << s << endl;
	if (s.size() == 1) {
		return vector<string>(1, s);
	} else {
		vector<string> r = substrs(s.substr(1));
		vector<string> results;
		results.push_back(s.substr(0, 1));
		for (int i = 0; i < r.size(); ++i) {
			results.push_back(s.substr(0, 1) + r[i]);
		}
		for (int i = 0; i < r.size(); ++i) {
			results.push_back(r[i]);
		}
		return results;
	}
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N; cin >> N;
		string s; cin >> s;
		sort(s.begin(), s.end());
		vector<string> results = substrs(s);
		for (int i = 0; i < results.size(); ++i) {
			cout << results[i] << endl;
		}
	}
}