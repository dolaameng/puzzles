/*
ID: dolabot1
PROG: milk2
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Task {
public:
	int start;
	int end;
	Task(): start(0), end(0) {};
	Task(int s, int e): start(s), end(e) {};
public:
	static bool startTimeLessThan (const Task & lhs, const Task & rhs) {
		return lhs.start < rhs.start;
	};
	static bool durationLessThan (const Task & lhs, const Task & rhs) {
		return (lhs.end - lhs.start) < (rhs.end - rhs.start);
	}
};

int main () {
	// parsing
	ifstream fin ("milk2.in");
	ofstream fout ("milk2.out");
	int n = 0;
	fin >> n;
	vector<Task> tasks;
	for (int i = 0; i <= n-1; ++i) {
		int start, end;
		fin >> start >> end;
		tasks.push_back(Task(start, end));
	}
	// sorting by stat time
	sort(tasks.begin(), tasks.end(), Task::startTimeLessThan);
	// continous blocks
	vector<Task> blocks;
	vector<Task> idles;
	int start = tasks[0].start;
	int end = tasks[0].end;
	for (int i = 1; i <= tasks.size() - 1; ++i) {
		if (tasks[i].start <= end && tasks[i].end > end) {
			end = tasks[i].end;
		} else if (tasks[i].start > end) {
			blocks.push_back(Task(start, end));
			idles.push_back(Task(end, tasks[i].start));
			start = tasks[i].start;
			end = tasks[i].end;
		}
	}
	blocks.push_back(Task(start, end));
	
	int longest_block_duration = 0;
	if (!blocks.empty()) {
		const Task &  longest_block = *max_element(blocks.begin(), blocks.end(), Task::durationLessThan);
		longest_block_duration = longest_block.end - longest_block.start;
	}
	//cout << longest_block_duration << endl;
	int longest_idle_duration = 0;
	if (!idles.empty()){
		const Task &  longest_idle = *max_element(idles.begin(), idles.end(), Task::durationLessThan);
		longest_idle_duration = longest_idle.end - longest_idle.start;
	}
	//cout << longest_idle_duration << endl;

	//debug
	fout << longest_block_duration << " " << longest_idle_duration << endl;

	return 0;
}