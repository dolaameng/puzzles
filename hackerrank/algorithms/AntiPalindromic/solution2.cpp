#include <iostream>
using namespace std;

const unsigned long long int MOD = 1000000000+7;

unsigned long long int ipow( unsigned long long int base,  unsigned long long int exp) {
	unsigned long long int result = 1;
	while (exp) {
		if (exp & 1) result = (result * base) % MOD;
		exp >>= 1;
		base = (base * base) % MOD;
		//cout << base << " " << exp << endl;
	}
	return result;
}

unsigned long long int apalin(const unsigned long long int N, const unsigned long long int M) {
	if (N == 1) return M % MOD;
	else if (N == 2) return M*(M-1) % MOD;
	else return (M*(M-1) % MOD) *ipow(M-2, N-2) % MOD;
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		unsigned long long int N, M; 
		cin >> N >> M;
		cout << apalin(N, M) << endl;
	}
}