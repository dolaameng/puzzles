/*
ID: dolabot1
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum WeekDay {SAT, SUN, MON, TUE, WEN, THU, FRI};
const vector<string> WeekDayNames = {"SAT", "SUN", "MON", "TUE", "WEN", "THU", "FRI"};

bool leap_year(const unsigned int year) {
	if (year % 100 == 0) {
		return year % 400 == 0;
	} else {
		return year % 4 == 0;
	}
}

unsigned int year_month_days(const unsigned int year, const unsigned int month) {
	if (month == 9 || month == 4 || month == 6 || month == 11) {
		return 30;
	} else if (month == 2) {
		if (leap_year(year)) {
			return 29;
		}
		else {
			return 28;
		}
	} else {
		return 31;
	}
}

int main () {
	ifstream fin ("friday.in");
	ofstream fout ("friday.out");
	unsigned int n;
	fin >> n; 

	// Saturday to Friday
	vector<unsigned int> thirteenth(7);

	int which_day = (MON + 12) % 7; //saturday
	for (unsigned int year = 1900; year < 1900 + n; ++year) {
		for (unsigned int month = 1; month <= 12; ++month) {
			//cout << year << " " << month << " " << WeekDayNames[which_day] << endl;
			thirteenth[which_day] += 1;
			which_day += year_month_days(year, month);
			which_day %= 7;
		}
	}

	for (int i = 0; i <= thirteenth.size() - 1; ++i) {
		//cout << WeekDayNames[i] << ":" << thirteenth[i] << endl;
		fout << thirteenth[i];
		if ( i < thirteenth.size() -1) {
			fout << " ";
		}
	}
	fout << endl;

	return 0;
}