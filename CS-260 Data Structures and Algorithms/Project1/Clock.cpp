//============================================================================
// Filename    : clocks.cpp
// Author      : Eric Wallace
// Description : Clock class which is comprised of variables and methods that
//					can be used anywhere in the application
//============================================================================

#include<iostream>
#include<ctime>
#include<iomanip>
#include<vector>

using namespace std;

/**
 * Class for clocks application, displays two clocks
 * and allows users to add hour, min and sec
 *
 * @parameter None
 * @return None
 */
class Time {
	// Private member variables
public:
	int hour;
	int minute;
	int seconds;
};


// Class for the 12 clock, includes methods for adding hour, minutes and seconds
class Clock :public Time {
public:
	string DoN;


	Clock() {
		// Get the current time for localtime
		time_t now;
		struct tm ltm;
		time(&now);
		localtime_s(&ltm, &now);
		hour = ltm.tm_hour;
		minute = ltm.tm_min;
		minute = minute < 10 ? printf("%02d", minute) : minute;
		seconds = ltm.tm_sec;
		if (hour >= 12) DoN = "PM";
		else DoN = "AM";
	}

	/**
	 * Method for adding one hour to our time
	 *
	 * @parameter unit
	 *
	 * @return None
	 */
	void AddHour(int unit = 12) {
		if (unit == 12) {
			if (hour == 11) {
				if (DoN == "AM") DoN = "PM";
				else DoN = "AM";
				hour = 12;
			}
			else {
				hour += 1;
				hour > 12 ? hour -= 12 : hour;
			}
		}
		else if (unit == 24) {
			if (hour == 23) hour = 00;
			else hour += 1;
		}
	};

	/**
	 * Method for adding one minute to our time
	 *
	 * @parameter None
	 *
	 * @return None
	 */
	void AddMinute() {
		if (minute == 59) {
			minute = 0;
			AddHour();
		}
		else {
			minute += 1;
		}
	};

	/**
	 * Method for adding an second to our time
	 *
	 * @parameter None
	 *
	 * @return None
	 */
	void AddSecond() {
		if (seconds == 59) {
			seconds = 0;
			AddMinute();
		}
		else {
			seconds += 1;
		}
	}
};


	void DisplayClock(Clock c1, Clock c2) {
		int hours = c1.hour > 12 ? c1.hour -= 12 : c1.hour;
		cout << "\t*******************************     *******************************" << endl;
		cout << "\t*" << right << setw(30) << "*" << right << setw(6) << "*" << right << setw(30) << "*" << endl;
		cout << "\t*" << setw(21) << "12-Hour Clock" << setw(9) << "*";
		cout << setw(6) << "*" << setw(9) << "2" << "4-Hour Clock" << setw(9) << "*" << endl;
		cout << "\t*" << right << setw(30) << "*" << right << setw(6) << "*" << right << setw(30) << "*" << endl;
		cout << "\t*" << setw(11) << hours << ":" << c1.minute << ":" << c1.seconds << " " << c1.DoN << setw(10) << " *";
		cout << setw(6) << "*" << setw(13) << c2.hour << ":" << c2.minute << ":" << c2.seconds << setw(11) << " *" << endl;
		cout << "\t*" << right << setw(30) << "*" << right << setw(6) << "*" << right << setw(30) << "*" << endl;
		cout << "\t*******************************     *******************************" << endl;
	}



int main() {
	Clock H12;
	Clock H24;

	DisplayClock(H12, H24);
	int option = 0;

	// Loop producing the options and handles adding of time
	while (option != 9) {
		cout << "\n\n" << endl;
		cout << "\t***************************" << endl;
		cout << "\t* 1 - Add One Hour        *" << endl;
		cout << "\t* 2 - Add One Minute      *" << endl;
		cout << "\t* 3 - Add One Second      *" << endl;
		cout << "\t* 9 - Exit Program        *" << endl;
		cout << "\t***************************" << endl;
		cout << "\n\n" << endl;
		cout << "Please choose and option" << endl;

		cin >> option;

		// Statement to run function to add appropriate unit
		switch (option) {
		case 1:
			H12.AddHour();
			H24.AddHour();
			break;
		case 2:
			H12.AddMinute();
			H24.AddMinute();
			break;
		case 3:
			H12.AddSecond();
			H24.AddSecond();
			break;
		case 9:
			exit(0);
			break;
		default:
			cout << "\tEnter Correct Choice!!\n";;
		}

		system("cls");
		DisplayClock(H12, H24);
	}
}