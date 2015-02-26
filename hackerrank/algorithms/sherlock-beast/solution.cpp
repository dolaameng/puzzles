#include <iostream>
#include <vector>
#include <string>
using namespace std;

string decent(const int N) {
	vector<int> five_three;
	if ( N >= 5 && (N-5) % 3 ==0 ) {
		five_three.push_back(N-5);
		five_three.push_back(5);
	} else if ( N >= 10 && (N-10) % 3 == 0 ) {
		five_three.push_back(N-10);
		five_three.push_back(10);
	} else if (N % 3 == 0) {
		five_three.push_back(N);
		five_three.push_back(0);
	} else {
		return "-1";
	}
	string r = "";
	for (int five = 0; five < five_three[0]; ++five) {
		r += "5";
	}
	for (int three = 0; three < five_three[1]; ++ three) {
		r += "3";
	}
	return r;
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N; cin >> N;
		cout << decent(N) << endl;
	}
}