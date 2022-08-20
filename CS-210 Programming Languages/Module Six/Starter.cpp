//============================================================================
// Name        : Starter.cpp
// Author      : Eric Wallace
// Assignment  : Module 6 Assignment	
// Date		   : April 6, 2022
// Description : Module 6 Multiplication Assignment using Python and C++
//============================================================================

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

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
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	// Clean up
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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

// Display menu to user
void displayMenu() {
	cout << "\n\t***************************************" << endl;
	cout << "\tMULTIPLICATION MENU" << endl;
	cout << "\t 1. Display Multiplication Table" << endl;
	cout << "\t 2. Double A Value" << endl;
	cout << "\t 3. Exit" << endl;
	cout << "\t Please enter a choice:  ";
}

// Displays submenu if option 1 or 2 is chosen. Specify subType
	void displaySubMenu(int subType) {
	string prompt = subType == 1 ? "Please enter a number to multiply, must be greater than 0.  " : "Please enter a number to double.  ";
	cout << "\n\t***************************************" << endl;
	cout << "\t" << prompt;
}


// Display user input error
void displayError(string errorMessage, string optionMessage) {
	cin.clear();
	cin.ignore();
	// Display error message
	cout << errorMessage << endl;
	cout << optionMessage << endl;
	cin.clear();
	cin.ignore();
}

// Display MultiplicationTable
void displayMultiplicationTable() {
	int subChoice;
	// Set submenu choice
	cin.clear();
	cin.ignore();

	// Display submenu
	displaySubMenu(1);

	// Get user submenu choice
	cin >> subChoice;

	// Validate user
	if (subChoice <= 0) {
		displayError("Invalid multiple.", "Please enter a number greater than 0");
		displaySubMenu(1);
	}

	// Run Python function to calculate the table
	callIntFunc("MultiplicationTable", subChoice);

	// Enter a blank row
	cout << endl;

	// Clear the output on screen
	cin.clear();
	cin.ignore();
}


// Display Double Value
void displayDoubleValue() {
	int subChoice;
	// Set submenu choice
	cin.clear();
	cin.ignore();

	// Display submenu
	displaySubMenu(2);

	// Get user submenu choice
	cin >> subChoice;

	// Validate user
	if (subChoice <= 0) {
		displayError("Invalid number to double.", "Please enter a number greater than 0");
		displaySubMenu(2);
	}

	// Run Python function to calculate the table
	int result = callIntFunc("DoubleValue", subChoice);
	cout << subChoice << " doubled is " << result << endl;


	// Clear the output on screen
	cin.clear();
	cin.ignore();
}


int choice;


int main() {
	int choice = 0;
	int maxChoice = 3;
	int minChoice = 1;
	string errorMessage;
	int subType = 1;

	while (choice != 3) {

		displayMenu();

		cin >> choice;

		//Validate user input
		if (choice > maxChoice || choice < minChoice) {
			displayError("Incorrect choice made!!", "Please choose either 1, 2, or 3!!");
		}

		// Determine which 
		switch (choice) {
		case 1:
			displayMultiplicationTable();
			break;
		case 2:
			displayDoubleValue();
			break;
		default: 
			displayMenu();
		}
	}

	cout << "Thank You, Goodbye!!!";

	return 0;
}