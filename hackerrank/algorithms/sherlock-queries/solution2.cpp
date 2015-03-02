#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N, M;
	const unsigned long long X = 1000000000 + 7;
	cin >> N >> M;
	vector<unsigned long long> A(N+1);
	vector<int> B(M+1);
	vector<int> C(M+1);
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = 1; i <= M; ++i) cin >> B[i];
	for (int i = 1; i <= M; ++i) cin >> C[i];

	vector<unsigned long long> unique_B (N+1, 1);
	for (int i = 1; i <= M; ++i) {
		unique_B[B[i]] = (unique_B[B[i]] * C[i]) % X;
	}

	for (int ib = 1; ib < unique_B.size(); ++ib) {
		int b = unique_B[ib];
		if (b == 1) continue;
		for (int t = 1; t <= N / ib; ++t) {
			A[t*ib] *= b;
			A[t*ib] %= X;
		}
	}
	for (int ia = 1; ia <= N-1; ++ia) cout << A[ia] << " ";
	cout << A[N] << endl;
	return 0;
}