/*
ID: dolabot1
PROG: gift1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main () {
	ifstream fin ("gift1.in");
	ofstream fout ("gift1.out");

	// people names
	vector<string> names;
	map<string, int> init_amounts;
	map<string, int> received_amounts; 
	map<string, vector<string>> friends;

	// parse inputs
	unsigned int n = 0;
	fin >> n; // n people
	// people names
	for (unsigned int i = 0; i <= n-1; ++i) {
		string name = "";
		fin >> name;
		names.push_back(name);
		received_amounts[name] = 0;
	}
	// initial amounts and friends
	for (int i = 0; i <= n-1; ++i) {
		string name;
		int amount, nfriends;
		fin >> name >> amount >> nfriends;
		init_amounts[name] = amount;
		vector<string> friend_names;
		for (int ifriend = 0; ifriend <= nfriends - 1; ++ifriend) {
			string friend_name;
			fin >> friend_name;
			friend_names.push_back(friend_name);
		}
		friends[name] = friend_names;
	}
	// distribute money
	for (const string s : names) {
		int given = 0;
		if (friends[s].size() > 0){
			given = init_amounts[s] / friends[s].size();
		}
		// receive from friends
		for (const string f : friends[s]) {
			received_amounts[f] += given;
		}
		// receive from self
		if (friends[s].size() > 0) {
			received_amounts[s] += init_amounts[s] % friends[s].size();
		}
	}

	for (const string s: names) {
		//cout << s << " " << init_amounts[s] << " " << received_amounts[s] << endl;
		fout << s << " " << received_amounts[s]-init_amounts[s] << endl;
	}

	return 0;
}