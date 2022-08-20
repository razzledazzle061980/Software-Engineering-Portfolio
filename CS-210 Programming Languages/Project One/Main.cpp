#include "Clock.h"

using namespace std;

int main() {
	Clock H12;
	Clock H24;

	DisplayClock(H12, H24);
	int option = 0;

	// Loop producing the options and handles adding of time
	while (option != 9) {
		cout << "\n\n" << endl;
		cout << "***************************" << endl;
		cout << "* 1 - Add One Hour        *" << endl;
		cout << "* 2 - Add One Minute      *" << endl;
		cout << "* 3 - Add One Second      *" << endl;
		cout << "* 9 - Exit Program        *" << endl;
		cout << "\n*************************" << endl;

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
			cout << "Enter Correct Choice!!\n";
		}

		system("cls");
		DisplayClock(H12, H24);
	}
}