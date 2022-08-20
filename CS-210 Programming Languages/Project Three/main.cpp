//============================================================================
// Name        : Starter.cpp
// Author      : Eric Wallace
// Assignment  : Project 3	
// Date		   : April 15, 2022
// Description : Project 3 using Python 3 and C++
//============================================================================

#include <Python.h>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include "Colors.h"

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("starter");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"starter");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue); 
		//Clean Up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"starter");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass an integer in milliseconds the amount
	of time execution should pause
Example:
	sleep(2000);
Output:
	None
Return:
	None
*/
void delay(int delay_time) {
	delay_time *= 1000;
	std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
}

/*
* Description:
*   To call this function, pass a errorTitle and errormessge
* Example:
*   displayError(errorTitle, errorMessage);
* Output:
*   Outputs an error message in red text
* Return:
*   none
*/
void displayError(string errorTitle, string errorMessage) {
	cin.clear();
	cin.ignore();
	// Display error message

	print_no_reset("\t\t\b" + errorTitle + "\b\n", color_red);
	println("\t-------------------------------------");
	print("\t   " + errorMessage + "\n");
	print_color_reset();
	delay(2);
	system("CLS");
	cin.clear();

}

/*
Description:
	Call the function by simply calling the function
	and supplying a string 
Example:
	hasNumber(string);
Output:
	none
Return:
	boolean
*/
bool hasNumber(const string& s) {
	for (char const& ch : s) {
		if (isdigit(ch) == 0) return false;
	}
	return true;
}

/*
Description:
	Call the function by simply calling the function with no arguments
Example:
	mainMenu();
Output:
	Outputs the default menu systems
Return:
	None
*/
void mainMenu() {
	cout << "\n\t***************************************" << endl;
	cout << "\t           ITEM-TRACKING                 " << endl;
	cout << "\t 1. List the number of times products were purchased" << endl;
	cout << "\t 2. Display the frequency of a searched item" << endl;
	cout << "\t 3. Display histogram with the frequency of each item." << endl;
	cout << "\t 4. Exit" << endl;
	cout << "\t Please enter a choice:  ";
}

// Searches the purchased items for match
bool findInFile(string searchItem) {
	ifstream file;
	string filename = "purchased_items.txt";
	string item;

	file.open(filename);

	// Throw error and return to main menu if error reading file
	if (!file.is_open()) {
		displayError("ERROR READING FILE", "There was an error reading file");
		mainMenu();
	}
	
	while (getline(file, item)) {
		std::transform(searchItem.begin(), searchItem.end(), searchItem.begin(),
			[](unsigned char c) -> unsigned char { return std::tolower (c); });

		std::transform(item.begin(), item.end(), item.begin(),
			[](unsigned char c) -> unsigned char { return std::tolower(c); });
		
		if (item.find(searchItem) != std::string::npos)
			return true;
	}
	return false;
	file.close();
}

/*
Description:
	Call the function by simply calling the function with no arguments
Example:
	subMenu();
Output:
	Outputs option 2 sub menu
Return:
	None
*/
string subMenu() {
	string subSelection;
	system("CLS");
	print_color(color_orange);
	print("\n\t***************************************\n");
	print("\t           ITEM-SELECTION                 \n");
	print("\t Please enter an item or keyword you would like to search.\n");
	print("\t To exit and return to main menu, type back\n");
	print("\t ");
	print_color_reset();

	cin >> subSelection;

	// User types in back
	if (subSelection == "back") { return "back"; }

	// Search purchased products for search keyword                                                                                                                                                                                                           
	else if (findInFile(subSelection) == false) {
		displayError("KEYWORD NOT FOUND", "Keyword or item not found in list. \n\tPlease try again.");                                                                    
		subMenu();
	}
	else {
		return subSelection;
	}
}

/*
Description:
	Call the function, pass the filename as an argument
Example:
	ReadFrequencyFile(filename);
Output:
	Outputs histogram of data provided by the file
Return:
	None
*/
void ReadFrequencyFile(string filename) {
	// Variables associated with function
	ifstream readFile;
	string line;

	// Output message showing the file is being opened
	print("\tOpening file " + filename + " and preparing to process data...\n", color_yellow);

	// Open file
	readFile.open(filename);

	// Error message stating an error occurred while
	// opening the file
	if (!readFile.is_open()) {
		displayError("ERROR OPENING FILE", "Encountered an error while attempting to open file " + filename);
		mainMenu();
	}

	// Iterate through each line until the end of file
	// is reach at which time the loop exits
	while (!readFile.eof()) {
		string itemName;
		int numOfItems;

		readFile >> itemName;
		readFile >> numOfItems;

		int clr{};
		// Set color of squares
		if (numOfItems >= 0) clr = (color_red); 
		if (numOfItems > 1) clr = (color_light_blue); 
		if (numOfItems >= 5) clr = (color_green); 
		if (numOfItems >= 10) clr = (color_yellow); 

		// Print out the name of the item
		print("\t" + itemName + " ", clr);

		// Loop through each of the number of items
		for (int i = 0; i < numOfItems; i++) {
			print("*", clr);
			cout << " ";
		}
		
		cout << endl;
	}

	readFile.close();

	cout << "\tProcessing of Purchased Product list complete." << endl;
}


int main()
{
	// Section contains variables used throughout the app
	int numOfPurchases	= 0;
	string searchItem;
	string statement;
	int maxChoice		= 4;
	int minChoice		= 1;
	int choice			= 0;

	while (choice != 4) {
		mainMenu();

		cin >> choice;
		cout << endl;
		if (choice < minChoice || choice > maxChoice) {
			system("CLS");
			displayError("ERROR - MENU SELECTION", "You selected an invalid option");
		}
		// Switch statement to determine which function to execute
		switch (choice) {
			// Case1: List all items purchased and the number of times they were purchased
			case 1:
				system("CLS");
				CallProcedure("PurchasedItems");
				cout << endl;
				break;
			// Case 2: Calculates the number of purchases the specified item had
			case 2:
				system("CLS");
				// Calling subMenu which returns user searchItem
				searchItem = subMenu();

				// Return to main menu'
				if (searchItem == "back") {
					system("CLS");
					break;
				}

				system("CLS");
				// Call to Python script to count the frequency of their searchItem
				print("\n\n\tCalculating the frequency your item was purchased...\n", color_blue);
				numOfPurchases = callIntFunc("CountPurchasedItems", searchItem);

				// Display number of purchases
				if (numOfPurchases == 0) {
					print("\tNo purchases were found.\n", color_blue);
				}
				else {
					statement = "\tSearch results show " + std::to_string(numOfPurchases) + " purchases were made on " + searchItem + "\n";
					print_color(color_blue);
					cout << statement << endl;
					cout << "\t" << searchItem << " : " + std::to_string(numOfPurchases) << endl;
					print_color_reset();
				}
				system("CLS");
				break;
			// Print histogram to show all items purchased
			case 3:
				system("CLS");

				// Call the function to collect data for histogram
				CallProcedure("OutputPurchasedList");

				// Run function to read previously outputted file
				// and display histogram
				ReadFrequencyFile("frequency.dat");
				break;
		}
	}
	cout << "Thank you, Goodbye!!" << endl;
	return 0;
}