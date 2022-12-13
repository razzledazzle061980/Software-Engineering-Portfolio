#include <iostream>

using namespace std;

// Declare and initialize arrays
string password = "123";
int choice = 0;

// Struct that contains the fields associated with clients
struct clients
{
	int id;
	string name;
	int service;
};


// Clients dictionary that contains the clients, the num
// associated with the client and the service chosen for them
clients client[] = {
	{1, "Bob Jones", 2},
	{2,"Sarah Davis",1},
	{3, "Amy Friendly", 1},
	{4, "Johnny Smith", 2},
	{5, "Carol Spears", 1}
};

// Menu options shown to user after authentication
string menu_options = "What would you like to do?\n"\
"1.  DISPLAY the client list\n"\
"2.  CHANGE a client's service choice\n"\
"3.  EXIT the program..";


/*
 * ChangeCustomerChoice - Change a customer's selected service
 */
void ChangeCustomerChoice()
{
	// Variables
	int change_choice = 0;
	int new_service = 0;

	// Output prompt to enter client number and then read the input
	cout << "\nEnter the number of the client that you wish to change" << endl;

	// Display clients so user will have a reference when choosing
	// a client they wish to change the service for
	for (int i = 0; i <= 4; i++)
	{
		if (i == 0) {
            cout << "(";
        }
            if (i == 4) { cout << ")" << endl; 
        } else { 
            cout << i + 1 << " = " << client[i].name << ", "; 

            }
	}

	// Read input and save to change_choice
	cin >> change_choice;

	// Output prompt to enter new service and then read the input
	cout << "\nPlease enter the client's new service choice (1 = Brokerage, 2 = Retirement)" << endl;
	cin >> new_service;

	// Update the particular client record
	client[change_choice - 1].service = new_service;
}

// Authenticates user credentials (username is anything
void CheckUserPermissionAccess()
{
	// Variables
	string username;
	string pass;
	bool answer = false;

	// Loop while incorrect password is entered
	do {
		// Prompt user for username and then read input into username variable
		cout << "Enter your username: " << endl;
		cin >> username;

		// Prompt user for password and then read input into username variable
		// which is stored at the beginning of this script file
		cout << "Enter password for " << username << ":" << endl;
		cin >> pass;

		// If password equals user input then exit loop
		if (pass == 123) {
			answer = true;
		} else
		{
			// Output Invalid password
			cout << "Invalid Password. Please try again..\n" << endl;
		}

	} while (answer == false);

	return;
}

// Show client information
void DisplayInfo()
{
	// Display service options selected by client
	cout << "\tClient's Name" << "\tService Selected (1 = Brokerage, 2 = Retirement)" << endl;
	for (int i = 0; i <= 4; i++)
	{
		cout << client[i].id << ".  ";
		cout << client[i].name << " selected service option:  ";
		cout << client[i].service << endl;
	}

	// Insert an extra line
	cout << "\n" << endl;
}

int main()
{
	// Output welcome message
	cout << "Hello! Welcome to our Investment Company ";
	cout << "by Eric Wallace * CS-410: Reverse Engineering\n" << endl;

	// Run authentication function
	CheckUserPermissionAccess();

	// Loop while choice does not equal 3
	do
	{
		// Display menu options and read user
		// input assign to choice variable
		cout << menu_options << endl;
		cin >> choice;

		// Display what option user chose
		cout << "\nYou chose:  " << choice << "\n" << endl;

		// Switch used for selecting which option to display
		switch (choice)
		{
		case 1:
			DisplayInfo();
			break;
		case 2:
			ChangeCustomerChoice();
			break;
		default:
			break;
		}

	} while (choice != 3);

	return 0;

}