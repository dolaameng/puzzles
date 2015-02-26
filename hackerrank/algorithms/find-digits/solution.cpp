#include <iostream>
#include <vector>
using namespace std;

int find_digits(const unsigned long n) {
	int ndigits = 0;
	unsigned long q = n;
	while (q > 0) {
		int r = q % 10;
		if (r > 0 && n % r == 0) ndigits++;
		q /= 10;
	}
	return ndigits;
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		unsigned long n; cin >> n;
		cout << find_digits(n) << endl;
	}
	return 0;
}