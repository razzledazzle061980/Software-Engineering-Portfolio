//============================================================================
// Filename    : interest.h
// Assignment  : Project Two
// Author      : Eric Wallace
// Date        : Apr. 1, 2022
// Description : Instantiates constructor for the class used in application
//============================================================================

#ifndef INTEREST_H_
#define INTEREST_H_

// Declare interest class
class interest {
    public:
        interest(double investment, double monthlyDeposit, double rate, int years);
        
        // Destructor interest constructor
        virtual ~interest();
        
        // Declare two report functions
        void reportNoMonthlyDeposit();
        void reportMonthlyDeposit();
    
    // Declare private variables
    private:
        double initialDeposit;
        double monthlyDeposit;
        double interestRate;
        int numberYears;
        
};

#endif