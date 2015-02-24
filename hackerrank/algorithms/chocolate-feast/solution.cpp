#include <iostream>
#include <vector>
using namespace std;

int trade (int wrappers, int M) {
	if (wrappers < M) return 0;
	else {
		int candy = wrappers / M;
		return candy + trade(candy + wrappers % M, M);
	}
}

int main () {
	int T; cin >> T;
	int N, C, M;
	for (int t = 0; t < T; ++t) {
		cin >> N >> C >> M;
		int ncandies = N / C + trade(N/C, M);
		cout << ncandies << endl;
	}
}