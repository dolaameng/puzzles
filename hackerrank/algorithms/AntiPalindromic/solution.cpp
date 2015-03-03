#include <iostream>
using namespace std;

unsigned long long apalin(const unsigned long long N, const unsigned long long M) {
	unsigned long long total = 1;
	for (int i = 1; i <= N; ++i) {
		if (i == 1) total *= M;
		else if (i == 2) total *= (M-1);
		else total *= (M-2);
		if (total == 0) break;
		total %= (1000000000+7);
	}
	return total;
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		unsigned long long N, M; 
		cin >> N >> M;
		cout << apalin(N, M) << endl;
	}
}