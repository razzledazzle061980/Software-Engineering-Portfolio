/**************************************************************************
* Author: Eric Wallace
* Assignment : CS-405 4-1 Activity: Exce
* Description : Practices the use of try/catch/throw to produce exceptions
* Filename : CS-405 4-1 Exceptions.cpp
**************************************************************************/

#include <iostream>
#include <exception>
#include <utility>

using namespace std;



// Custom exception used for catching errors
struct CustomException : public exception
{
	virtual const char *what() const override
	{
		return "This is a custom exception.";
	}
};

bool do_even_more_custom_application_logic()
{

    // Throw standard exception
    throw bad_exception();

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic())
        {
            
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    } catch(exception& e)
    {
        // Output standard exception
        cerr << "Exception:  " << e.what() << endl;
    }

    // Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    throw CustomException();

    cout << "Leaving Custom Application Logic." << endl;

}

float divide(float num, float den)
{
    // Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception

    // If denominator is zero then through a runtime error
    if (static_cast<int>(den) == 0)
    {
        //  Throws runtime error
        throw runtime_error("Attempted to divide by zero");
    }
    return (num / den);

}

void do_division() noexcept
{
    // Create an exception handler to capture ONLY the exception thrown
    //  by divide.

    constexpr float numerator = 10.0f;
    constexpr float denominator = 0;

    try
    {
	    const auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;

    } catch(exception &e)
    {
        //  Output capturing only the exception
        cerr << "Exception:  " << e.what() << endl;
    }

    }

int main()
{
    try {
        std::cout << "Exceptions Tests!" << std::endl;

        // Create exception handlers that catch (in this order):
        //  your custom exception
        //  std::exception
        //  uncaught exception 
        //  that wraps the whole main function, and displays a message to the console.
        do_division();
        do_custom_application_logic();
		// Catches custom exception
    } catch (CustomException &err)
    {
        cerr << "Exception:  " << err.what() << endl;
        // Catches standard exception
    } catch (exception &err)
    {
        cerr << "Exception:  " << err.what() << endl;
        // Catches uncaught exceptions
    } catch(...)
    {
        cerr << "Uncaught Exceptions" << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
