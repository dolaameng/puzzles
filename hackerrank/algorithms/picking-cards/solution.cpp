#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Input:
3  
3  
0 0 0  
3  
0 0 1  
3  
0 3 3
Output:
6  
4  
0
*/

const int MOD = 1000000007;




int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N; cin >> N;
		vector<int> cards(N);
		for (int i = 0; i < N; ++i) cin >> cards[i];
		
		sort(cards.begin(), cards.end());
		
		vector<int> accums(N+1, 0);
		for (int i = 0; i < N; ++i) {
			accums[cards[i]]++;
		}

		int a = accums[0];
		for (int i = 1; i < N+1; ++i) {
			a += accums[i];
			accums[i] = a - i;
		}

		/*
		for (int i = 0; i < N+1; ++i) {
			cout << i << ":" << accums[i] << endl;
		}
		*/
		unsigned long long total = 1;
		for (int i = 0; i < N; ++i) {
			total *= accums[i];
			total %= MOD;
			if (total == 0) break;
		}
		cout << total << endl;
	}
}