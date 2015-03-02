#include <iostream>
#include <vector>
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

	for (int ib = 1; ib <= M; ++ib) {
		int b = B[ib];
		for (int t = 1; t <= N / b; ++t) {
			A[t*b] *= C[ib];
			A[t*b] %= X;
			//cout << ib << " " << b << " " << t*b << endl;
		}
	}
	for (int ia = 1; ia <= N-1; ++ia) cout << A[ia] << " ";
	cout << A[N] << endl;
	return 0;
}