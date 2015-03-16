#include <iostream>
#include <vector>
using namespace std;

// the systermatic way of representing subarray is
// to specify their start and end.
long count_list(const vector<int> & xs, const int K, 
				const int start) {
	int pivot = -1;
	for (int i = start; i < xs.size(); ++i) {
		if (xs[i] > K) {
			pivot = i;
			break;
		}
	}
	if (pivot == -1) {
		return 0;
	}
	long total = (pivot-start+1)*(xs.size()-pivot) + count_list(xs, K, pivot + 1);
	return total;
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, K; 
		cin >> N >> K;
		vector<int> xs(N);
		for (int n = 0; n < N; ++n) cin >> xs[n];
		cout << count_list(xs, K, 0) << endl;
	}
	return 0;
}