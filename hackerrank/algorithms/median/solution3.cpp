#include <iostream>
#include <set>
using namespace std;

multiset<int> lower, upper;
typedef multiset<int >::iterator Pos;

double median() {
	int nlower = lower.size();
	int nupper = upper.size();
	if (nlower > nupper) {
		return *(lower.rbegin());
	} else {
		double x0 = *(lower.rbegin());
		double x1 = *(upper.begin());
		return (x0+x1)/2;
	}
}

bool remove(const int x) {
	Pos plower = lower.find(x);
	Pos pupper = upper.find(x);
	int nlower = lower.size();
	int nupper = upper.size();
	if (plower == lower.end() && pupper == upper.end()) {
		return false;
	} else if (plower != lower.end() && pupper != upper.end()) {
		if (nlower == nupper) upper.erase(pupper);
		else lower.erase(plower);
	} else if (plower != lower.end()) {
		lower.erase(plower);
		if (nlower == nupper) {
			int x = *(upper.begin());
			lower.insert(x);
			upper.erase(upper.begin());
		}
	} else if (pupper != upper.end()) {
		upper.erase(pupper);
		if (nlower > nupper) {
			Pos px = lower.end(); px--;
			int x = *(px);
			upper.insert(x);
			lower.erase(px);
		}
	}

	return true;
}

void add(const int x) {
	
	if (!lower.empty() && (x > *(lower.rbegin()))) {
		upper.insert(x);
	} else {
		lower.insert(x);
	}
	int nlower = lower.size();
	int nupper = upper.size();
	if (nlower > nupper + 1) {
		Pos px = lower.end(); px--;
		int x = *(px);
		upper.insert(x);
		lower.erase(px);
	}
	if (nupper > nlower) {
		int x = *(upper.begin());
		lower.insert(x);
		upper.erase(upper.begin());
	}
	/*
	cout << "LOWER:";
	for (Pos it = lower.begin(); it!=lower.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\nUPPER:";
	for (Pos it = upper.begin(); it!=upper.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	*/
}

int main() {
	cout.precision(32);
	int T; cin >> T;
	
	for(int t = 0; t < T; ++t) {
		char op; cin >> op;
		int x; cin >> x;

		if (op == 'r') {
			if (!remove(x)) {
				cout << "Wrong!" << endl;
				continue;
			}
		} else if (op == 'a'){
			add(x);
		}
		

		if (!lower.empty() || !upper.empty()) cout << median() << endl;
		else cout << "Wrong!" << endl;
	}
}