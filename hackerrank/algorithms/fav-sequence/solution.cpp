#include <vector>
#include <iostream>
#include <map>
#include <set>
using namespace std;

//topological sorting

typedef map<int, set<int> > Graph;

int find_root(Graph & graph) {
	int root = -1;
	for (Graph::iterator i = graph.begin(); i != graph.end(); ++i) {
		if (i->second.empty()) {
			root = i->first;
			break;
		}
	}
	graph.erase(root);
	for (Graph::iterator i = graph.begin(); i != graph.end(); ++i) {
		i->second.erase(root);
	}
	return root;
}

vector<int> topological_sort(Graph & graph) {
	vector<int> nodes;
	int N = graph.size();
	while (nodes.size() < N) {
		int root = find_root(graph);
		nodes.push_back(root);
	}
	return nodes;
}

int main() {
	int N = 1000000;
	Graph graph; // incoming nodes

	int ns; cin >> ns;
	for (int s = 0; s < ns; ++s) {
		int n; cin >> n;
		vector<int> xs;
		for (int i = 0; i < n; ++i) {
			int x; cin >> x;
			if (graph.find(x) == graph.end()) graph[x] = set<int>();
			for (int ix = 0; ix < xs.size(); ++ix) {
				graph[x].insert(xs[ix]);
			} 
			xs.push_back(x);
		}
		//for(int j = 0; j < xs.size(); ++j) cout << xs[j] << " ";
		//cout << endl;
	}

	cout << "reading data done " << endl;

	
	vector<int> nodes = topological_sort(graph);
	for (int i = 0; i < nodes.size() - 1; ++i) {
		cout << nodes[i] << " ";
	}
	cout << nodes[nodes.size()-1] << endl;
	

	//debug 
	
	for (map<int,set<int> >::iterator it = graph.begin(); it != graph.end(); ++it) {
		int key = it->first;
		const set<int> & nodes = it->second;
		cout << key << ":";
		for (set<int>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
			cout << *i << " ";
		}
		cout << endl;
	}
	
	return 0;
}