/*----------------------------------------------------
	Student:  Eric Wallace
	Course: CS-405 Secure Coding
	Assignment: Module 1 Activity: Numeric Overflow Coding
	Date: Feb. 27, 2023
	Description: Use existing code and add logic to the
		add_numbers() and subtract_numbers() to detect,
		prevent, and notify of numeric overflow.  Modify
		test_overflow and test_underflow functions to be
		notified of success or failure.
	Objective: The source code has been commented with TODOs
		to explain the detailed rules you must follow.
	There are comments that mark code that must be changed.
	There may be more than one way to solve this problem,
		so be sure to demonstrate that you can detect an
		underflow or overflow, prevent it, and communicate
		it back to the calling function.
	Remember to leverage capabilities provided by the standard
		C++ library to help you achieve success.
#------------------------------------------------------*/

// NumericOverflows.cpp : This file contains the 'main' function.
// Program execution begins and ends there.

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <cstdlib>      // include standard library
#include <any>

using namespace std;

enum result_code
{
    OVER,
    UNDER,
    WRAP,
    SUCCESS,
    NONE,
} result_code;


const char* message;

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;
    result_code = NONE;
    T* temp_result = new T;
    
    for (unsigned long int i = 0; i < steps; ++i)
    {
        *temp_result = result + increment;
	    // Precondition test for sum of two positive numbers and result is negative
        if (result > 0 && increment > 0 && *temp_result < numeric_limits<T>::min()) {
            result_code = OVER;
            return result;

        }
	    // Precondition test for sum of two negative numbers and result is positive
        else if (result < 0 && increment < 0 && *temp_result > numeric_limits<T>::max()) {
            result_code = OVER;
            return result;
        }
        else if (*temp_result <= result)
        {
            result_code = WRAP;
            return result;
        }
	    else
	    // If no error is thrown, increment result
	    result += increment;
    }
    result_code = SUCCESS;
    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="decrement">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;
    result_code = NONE;
    T* temp_result = new T;
    
    for (unsigned long int i = 0; i < steps; ++i)
    {
        *temp_result = result - decrement;
        // Precondition test for subtraction of two positive numbers and result is negative
        if (result > 0 && decrement > 0 && *temp_result < 0) {
            result_code = UNDER;
            return result;
        }
        // Precondition test for sum of two negative numbers and result is positive
        else if (result < 0 && decrement < 0 && *temp_result > 0) {
            result_code = UNDER;
            return result;
        }
        // Precondition test for wraparound, if max minus temp result is less than result
        else if (*temp_result >= result) {
            result_code = WRAP;
            return result;
        }
        else // If no error is thrown, increment result
        result -= decrement;
    }
    result_code = SUCCESS;
    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    //      The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        [✔️] 1. Detect when an overflow will happen
    //        [✔️] 2. Prevent it from happening
    //        [✔️] 3. Return the correct value when no overflow happened or
    //        [✔️] 4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        [✔️]  1. Detect when an add_numbers failed
    //        [✔️]  2. Inform the user the overflow happened
    //        [✔️]  3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps);
    if (result_code == OVER)
        cout << "Addition failed with result : " << +result << endl;
    else if (result_code == WRAP)
        cout << "Addition failed with result: " << +result << endl;
	else
        cout << +result << endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1);
    if (result_code == OVER)
        cout << "Addition Overflow detected, failed with result : " << +result << endl;  // NOLINT(bugprone-branch-clone)
    else if (result_code == WRAP)
        cout << "Addition Wraparound detected, failed with result: " << +result << endl;
    else
        cout << +result << endl;

}

template <typename T>
void test_underflow()
{
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        [✔️]  1. Detect when an underflow will happen
    //        [✔️]  2. Prevent it from happening
    //        [✔️]  3. Return the correct value when no underflow happened or
    //        [✔️]  4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        [✔️]  1. Detect when an subtract_numbers failed
    //        [✔️]  2. Inform the user the underflow happened
    //        [✔️]  3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps);
    if (result_code == UNDER)
        cout << "Subtraction failed with result:  " << +result << endl;
    else if (result_code == WRAP)
        cout << "Subtraction failed with result:  " << +result << endl;
    else
        cout << +result << endl;


    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1);
    if (result_code == UNDER)
        cout << "Subtraction failed with result:  " << +result << endl;
    else if (result_code == WRAP)
        cout << "Subtraction failed with result:  " << +result << endl;
    else
	std::cout << +result << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

