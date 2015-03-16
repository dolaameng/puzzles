///////////////////////////////////// BUBBY VERSION //////////////////////
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <set>
using namespace std;

multiset<int> xs;
multiset<int>::iterator pmedian;

double median() {
	if (xs.size() % 2 == 1) {
		return *pmedian;
	} else {
		double x1 = *pmedian;
		multiset<int>::iterator pnext = pmedian; pnext++;
		double x2 = *pnext;
		//cout << "debug: " << x1 << " " << x2 << endl;
		return (x1+x2)/2;
	}
}

int main() {
	cout.precision(32);
	int T; cin >> T;
	
	for(int t = 0; t < T; ++t) {
		char op; cin >> op;
		int x; cin >> x;
		if (op == 'a') {
			xs.insert(x);
			if (xs.size() == 1) {
				pmedian = xs.begin();
			} else {
				if (x >= *pmedian && (xs.size() % 2 == 1)) {
					pmedian++;
				}
				if (x < *pmedian && (xs.size() % 2 == 0)) {
					pmedian--;
				}
			}
		} else {
			multiset<int>::iterator px = xs.find(x);
			if (px == xs.end()) {
				cout << "Wrong!" << endl;
				continue;
			} else {
				xs.erase(px);
			}
			if (x >= *pmedian && (xs.size() % 2 == 0)) {
				pmedian--;
			}
			if (x < *pmedian && (xs.size() % 2 == 1)) {
				pmedian++;
			}
		}
		if (!xs.empty()) cout << median() << endl;
		else cout << "Wrong!" << endl;
	}
}