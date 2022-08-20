//============================================================================
// Filename    : interest.cpp
// Assignment  : Project Two
// Author      : Eric Wallace
// Date        : Apr. 1, 2022
// Description : Used to calculate interest and display the table
//============================================================================

#include<iostream>
#include<iomanip>
#include "interest.h"

using namespace std;

// Set initial value of member variables
interest::interest(double investment, double monthlyDeposit, double rate, int years) {
    this->initialDeposit = investment;
    this->monthlyDeposit = monthlyDeposit;
    this->interestRate = rate;
    this->numberYears = years;
}

// Destructor interest
interest::~interest(){}

// Display report with no monthly deposited
void interest::reportNoMonthlyDeposit() {
    // Display title
    cout << "         Balance and Interest Without Monthly Deposits         " << endl;
    cout << "================================================================" << endl;
    
    // Display column headers
    cout << "    Year          Year End Balance      Year End Interest Earned" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    // Declare variables used in displaying data
    int yearNum;
    double balanceYearEnd = this->initialDeposit;
    
    // Interate through each year until numberYears is reached
    // displaying interest information 
    for (yearNum = 1; yearNum <= this->numberYears; ++yearNum) {
        // Calculate Interest
        double interestEarned = ((balanceYearEnd) * (this->interestRate) / 100);
        
        // Add interest to balanceYearEnd
        balanceYearEnd += interestEarned;
        
        // Display the yearly numbers
        cout << right << setw(7) << yearNum << fixed << setprecision(2);
        cout << setw(20) << balanceYearEnd;
        cout << setw(35) << interestEarned << endl;
    }   
}

// Display report with  monthly deposits
void interest::reportMonthlyDeposit() {
   // Display title
    cout << "     Balance and Interest With Additional Monthly Deposits     " << endl;
    cout << "================================================================" << endl;
    
    // Display column headers
    cout << "    Year          Year End Balance      Year End Interest Earned" << endl;
    cout << "----------------------------------------------------------------" << endl;
     
    // Declare variables used in displaying data
    int yearNum;
    int monthNum;
    double balanceYearEnd = this->initialDeposit;
    double balanceMonthEnd;
    int monthsInYear = 12;
    
    // Interate through each year until numberYears is reached
    // displaying interest information     
    for (yearNum = 1; yearNum <= this->numberYears; ++yearNum) {
        
        double interestEarned = 0.0;
        balanceMonthEnd = balanceYearEnd;
        
        for (monthNum = 1; monthNum <= monthsInYear; ++monthNum) {
            
            // Find compound interest by using formula (open deposit + amount deposited) * ((interestRate / 100) / 12
            double monthlyInterest = (balanceMonthEnd + this->monthlyDeposit) * ((this->interestRate / 100) / 12);
            
            // Add current months interest to the years total interest earned
            interestEarned += monthlyInterest;
            
            // Add monthly interest to the monthly balanceMonthEnd
            balanceMonthEnd += monthlyInterest + this->monthlyDeposit;
        }
        
        // Add the balance month end to the balance year end
        balanceYearEnd = balanceMonthEnd;
        
        // Display the yearly numbers
        cout << right << setw(7) << yearNum << fixed << setprecision(2);
        cout << setw(20) << balanceYearEnd;
        cout << setw(35) << interestEarned << endl;
        
    }
}
