//============================================================================
// File Name   : Lab1-3.cpp
// Project	   : Lab 1-3
// Author      : Eric Wallace
// Version     : 1.0
// Date		   : March, 5, 2022
//============================================================================

#include <algorithm>
#include <iostream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Converts a string to a double, used in the getBid method
double strToDouble(string str, char ch)
{
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // @suppress("Invalid arguments")
    return atof(str.c_str());
}

// BidInfo structure layout for each new bid
struct BidInfo
{
    string title;
    string fund;
    string vehicle;
    double amount;
};

// Displays bid information previously created
void displayBid(BidInfo info)
{
    cout << "Title: " << info.title << endl;
    cout << "Fund: " << info.fund << endl;
    cout << "Vehicle: " << info.vehicle << endl;
    cout << "Bid Amount: " << info.amount << endl;

    return;
}

/* Method used for prompting user for bid
 * information and storing it in a new variable
 */
BidInfo getBid()
{
    BidInfo info;

    // Bid Title prompts and entry
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, info.title);

    // Bid Fund prompt and entry
    cout << "Enter fund: ";
    cin >> info.fund;

    // Bid vehicle prompt and entry
    cout << "Enter vehicle: ";
    cin.ignore();
    getline(cin, info.vehicle);

    // Bid amount prompt and entry
    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    info.amount = strToDouble(strAmount, '$');

    return info;
}

/**
 * The one and only main() method
 */
int main()
{

    // Declare/instantiate a new BidInfo storing
    // it in the info variable
    BidInfo info;

    // loop to display menu until exit chosen
    int choice = 0;
    while (choice != 9)
    {
        cout << "Menu:" << endl;
        cout << "  1. Enter Bid" << endl;
        cout << "  2. Display Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // Switch case determines what to do based on
        // user input
        switch (choice)
        {
        case 1:
            info = getBid();
            break;
        case 2:
            displayBid(info);
            break;
        }
    }

    // Displays Good Bye whenever user selected option 9
    cout << "Good bye." << endl;

    // Exits application whenever user chooses option 9
    return 0;
}
