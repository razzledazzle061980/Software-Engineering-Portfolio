//============================================================================
// Filename    : main.cpp
// Assignment  : Project Two
// Author      : Eric Wallace
// Description : Main file for project two
//============================================================================

#include<iostream>
#include "interest.h"

using namespace std;

int main()
{
    
    while(1) {
        // Display Form
        cout << "**********************************" << endl;
        cout << "*********** Data Input ***********" << endl;
        cout << "Initial Investment Amount: " << endl;
        cout << "Monthly Deposit: " << endl;
        cout << "Annual Interest: " << endl;
        cout << "Number of years: " << endl;
        
        system("read -p 'Press Enter to continue...'var");
        cout << endl;
        
        // Get user Input
        cout << "**********************************" << endl;
        cout << "*********** Data Input ***********" << endl;
        
        // Display investment prompt
        cout << "Initial Investment Amount: $";
        
        double investment, monthlyDeposit, rate;
        int years;
        
        // Get investment amount
        cin >> investment;
        
        // Display monthly Deposit
        cout << "Monthly Deposit: $";
        // Get monthly Deposit
        cin >> monthlyDeposit;
        
        // Display interest rate prompt
        cout << "Annual Interest: %";
        // Get interest rate
        cin >> rate;
        
        // Display number of years
        cout << "Number of years: ";
        // Get number of years
        cin >> years;
        
        // Wait for user to press key
        // system("PAUSE")
        system("read -p 'Press Enter to continue...'var");
        
        // Instantiate interest object using user inputs
        interest myInterest = interest(investment, monthlyDeposit, rate, years);
        
        cout << endl;
        
        // Run monthly no deposit report
        myInterest.reportNoMonthlyDeposit();
        
        cout << endl;
        
        // Run monthly with deposit report
        if (monthlyDeposit > 0) {
            myInterest.reportMonthlyDeposit();
        }
        
        // Prompt user if they want to do another entry
        cout << endl;
        cout << "Do you want to enter another? (y/n): ";
        
        string choice;
        
        cin >> choice;
        
        // If user does not want to enter another entry exit the loop
        if(choice != "y") {
            break;
        }
        
        cout << endl;
    }

    return 0;
}