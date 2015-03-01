#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N; cin >> N;
	vector<int> sticks(N);
	for (int i = 0; i < N; ++i) cin >> sticks[i];

	sort(sticks.begin(), sticks.end());

	int pivot = sticks[0];
	int total = N;
	cout << total << endl;
	for (int i = 0; i < N; ++i) {
		if (sticks[i] != pivot) {
			pivot = sticks[i];
			cout << total << endl;
		}
		total--;
	}
	return 0;
}