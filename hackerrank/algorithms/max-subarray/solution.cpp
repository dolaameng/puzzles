#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Window {
public:
	int start;
	int end;
	int sum;
	Window(int s, int e, int sum_): start(s), end(e), sum(sum_) {};
};

void read_array(vector<int> & xs) {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) { 
		int x;
		cin >> x;
		xs.push_back(x);
	} 
}

int max_block_sum(const vector<int> & xs) {
	Window best(0, 0, xs[0]);
	Window current(0, 0, 0);
	// two parts in Kadane algorithm - extend the current window
	// and search for the best window, in one loop of iterating
	for (int i = 0; i < xs.size(); ++i) {
		//cout << current.start << "," << current.end << "," << current.sum << endl;
		if (current.sum < 0) {
			current.start = i;
			current.end = i;
			current.sum = xs[i];
		} else {
			current.end = i;
			current.sum += xs[i];
		}
		if (current.sum > best.sum) {
			best = current;
		}
	}
	return best.sum;
}

int max_sum (const vector<int> & xs) {
	int sum = 0;
	int max = xs[0];
	for (int i = 0; i < xs.size(); ++i) {
		if (xs[i] > 0) sum += xs[i];
		if (xs[i] > max) max = xs[i];
	}
	if (max > 0) return sum;
	else return max;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
    	vector<int> xs;
    	read_array(xs);
    	cout << max_block_sum(xs) << " " << max_sum(xs) << endl;
    }
    return 0;
}