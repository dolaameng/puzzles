#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

deque<int> track (int n, int a, int b) {
	deque<int> solutions;
	solutions.push_back(0);
	for (int i = 0; i < n-1; ++i) {
		int nsolutions = solutions.size();
		for (int s = 0; s < nsolutions; ++s) {
			solutions.push_back(solutions.front() + a);
			solutions.push_back(solutions.front() + b);
			solutions.pop_front();
			//cout << "solutions size:" << solutions.size() << endl;
		}
		sort(solutions.begin(), solutions.end());
		deque<int>::iterator it = unique(solutions.begin(), solutions.end());
		solutions.resize(distance(solutions.begin(), it));
	}
	return solutions;
}

int main () {
	int T; cin >> T;
	int n, a, b;
	for (int t = 0; t < T; ++t) {
		cin >> n >> a >> b;
		deque<int> results = track(n, a, b);
		for (int i = 0; i < results.size() - 1; ++i) {
			cout << results[i] << " ";
		}
		cout << results[results.size() - 1] << endl;
	}
	return 0;
}