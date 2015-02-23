#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <cassert>
using namespace std;

//topological sorting

vector<int> topological_sort(set<int> & nodes, vector<int> & incoming, vector<set<int> *> & outgoing) {
	vector<int> sorted;
	while (! nodes.empty()) {
		//find current root
		int root = -1;
		for (set<int>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
			if (incoming[*i]==0) {
				root = *i;
				break;
			}
		}
		

		//assert(root != -1);
		/*
		cout << "root:" << root << endl;
		for (set<int>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
			cout << *i << ":" << incoming[*i] << " ";
		}
		cout << endl;
		*/

		sorted.push_back(root);
		// update the graph structure
		nodes.erase(root);
		set<int> & followers = *outgoing[root];
		for (set<int>::const_iterator i = followers.begin(); i != followers.end(); ++i) {
			incoming[*i]--;
		}
	}
	return sorted;
}

int main() {
	int N = 1000000;
	vector<int> incoming_degrees(N+1, -1); // incoming degrees
	vector<set<int> *> incoming(N+1, NULL); // incoming edges
	vector<set<int> *> outgoing(N+1, NULL); // outgoing edges
	set<int> nodes;

	int ns; cin >> ns;
	for (int s = 0; s < ns; ++s) {
		int n; cin >> n;
		int pre, x;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			nodes.insert(x);
			if (incoming[x] == NULL) incoming[x] = new set<int>();
			if (outgoing[x] == NULL) outgoing[x] = new set<int>();
			if (i > 0) {
				incoming[x]->insert(pre);
				outgoing[pre]->insert(x);
			}
			pre = x;
		}
	}

	//cout << "total: " << nodes.size() << endl;
	for (set<int>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
		incoming_degrees[*i] = incoming[*i]->size();
	}
	
	vector<int> sorted = topological_sort(nodes, incoming_degrees, outgoing);
	for (int i = 0; i < sorted.size() - 1; ++i) {
		cout << sorted[i] << " ";
	}
	cout << sorted[sorted.size()-1] << endl;
	
	// debug
	/*
	for (set<int>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	for (set<int>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
		cout << *i << ":";
		set<int> siblings = *outgoing[*i];
		for (set<int>::const_iterator j = siblings.begin(); j != siblings.end(); ++j) {
			cout << *j << " ";
		}
		cout << endl;
	}
	cout << endl;
	*/
	
	
	return 0;
}