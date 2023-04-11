// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Define the maximum number of characters
#define NUM_OF_CHARS	20

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	//  The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
	//  even though it is a constant and the compiler buffer overflow checks are on.
	//  You need to modify this method to prevent buffer overflow without changing the account_order
	//  varaible, and its position in the declaration. It must always be directly before the variable used for input.

	const std::string account_number = "CharlieBrown42";
	char user_input[NUM_OF_CHARS];
		
	std::cout << "Enter a value: ";

	// Get user input by using the getline only write the first
	// 20 characters to user_input
	cin.getline(user_input, NUM_OF_CHARS);

	// Detect if more than 20 characters was passed to user input
	// if so, display message about a potential buffer overflow
	if (cin.fail())
		cout << "Possible buffer overflow detected!  Input has been limited to 20 characters." << endl;

	std::cout << "You entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
