#include <iostream>
#include <map>
using namespace std;

double median(const map<int,int> & xs, const int n) {
	if (xs.size() == 1) {
		return xs.begin()->first;
	}

	int pivot = n / 2; // 5->2 6->(2,3)
	bool isodd = (n%2==1);
	//cout << "debug n:" << n << " " << isodd << " " << pivot << endl;

	int visited = 0;
	int prex = 0;
	for (map<int,int>::const_iterator it = xs.begin(); it != xs.end(); ++it) {
		//cout << "debug:" << it->first << "(" << it->second << ")" << " " <<visited << " " << pivot << endl;
		int x = it->first;

		
		if (visited  == pivot) {
			if (isodd) return x;
			else  {		
				//cout << "debug:" << x << " " << prex << ":" << ((long double)x+(long double)prex)/2. << endl;
				return  (double) ((long double)x+prex)/2.;
			}
		} else if (visited > pivot) {
			return prex;
		}

		visited += it->second;
		prex = x;
	}
	return -1;
}

int main() {
	cout.precision(32);
	int T; cin >> T;
	map<int, int> xs;
	int n = 0;
	for(int t = 0; t < T; ++t) {
		char op; cin >> op;
		int x; cin >> x;
		if (op == 'r') {
			if (xs.empty()) {
				cout << "Wrong!" << endl;
				continue;
			} else if (xs.find(x) == xs.end()){
				cout << "Wrong!" << endl;
				continue;
			} else {
				xs[x]--;
				--n;
				if (xs[x] == 0) xs.erase(x);
			}
		} else if (op == 'a') {
			++n;
			if (xs.find(x) == xs.end()){
				xs[x] = 1;
			} else {
				xs[x]++;
			}
		}
		if (!xs.empty()) cout << median(xs, n) << endl;
		else cout << "Wrong!" << endl;
	}
}