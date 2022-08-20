//============================================================================
// Name        : VectorSorting.cpp
// Author      : Eric Wallace
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid
{
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid()
    {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid)
{
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid()
{
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath)
{
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try
    {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++)
        {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    }
    catch (csv::Error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid> &bids, int begin, int end)
{
    int low = begin;
    int high = end;
    int pivot;
    bool done = false;

    // Find midpoint of the bids
    pivot = begin + (end - begin) / 2;

    while (!done)
    {
        // Increment low long as it is less than pivot
        while (bids.at(low).title.compare(bids.at(pivot).title) < 0)
            ++low;

        // Decrement high as long as it is less than pivot
        while (bids.at(pivot).title.compare(bids.at(high).title) < 0)
            --high;

        // Compare high and low, when low is equal to or greater than high, it is done
        if (low >= high)
            done = true;
        // Otherwise swap the low and high
        else
        {
            swap(bids.at(low), bids.at(high));

            // Increment low and decrement high
            ++low;
            --high;
        }
    }
    // Return highest value
    return high;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid> &bids, int begin, int end)
{
    int midpoint = 0;

    // If beginning point is equal to or greater than ending point return
    if (begin >= end)
        return;

    // Partition bids into smaller groups using a beginning and ending point
    midpoint = partition(bids, begin, end);

    // Call quickSort to sort lower part (left side) of partition (begin to midpoint)
    quickSort(bids, begin, midpoint);

    // Call quickSort to sort upper part (right side) of partition (midpoint to end)
    quickSort(bids, midpoint + 1, end);
}

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid> &bids)
{
    // Index of current bid
    int minIndex = 0;
    // Number of bids
    int numberOfBids = bids.size();
    // Index of current bid (outter loop)
    int i;
    // Index of next bid (inner loop)
    int j;

    // Outter loop is position which marks current bid
    for (i = 0; i < numberOfBids; ++i)
    {
        minIndex = i;

        // Inner loop that compares the title of the outter loop to the title of inner loop
        for (j = i + 1; j < numberOfBids; ++j)
        {
            // Compares current bid title to next bid title and results
            //  an int which then finds if it is less than zero
            if (bids.at(j).title.compare(bids.at(minIndex).title) < 0)
            {
                // If next title is less than current title assign
                // minIndex value of next bid index
                minIndex = j;
            }
        }

        // If both titles are not the same or less bid title is numerically
        // less than current bid swap them
        if (minIndex != i)
        {
            swap(bids.at(i), bids.at(minIndex));
        }
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch)
{
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * Allows user to select which file to load
 * 
 * To disable this feature comment out the 
 * selectFile function call under case 1
 * 
 * To use feature make sure both .csv files 
 * reside in the same directory as VectorSorting.cpp
 * 
 * @param currFile current csvPath
 * 
 * @return file filename of file to load
 * 
 */
string selectFile(string currFile)
{
    string file;

    int option = 0;
    // Loop until user chooses 1, 2 or 3
    while (option != 1 && option != 2 && option != 3)
    {
        cout << "File Menu:" << endl;
        cout << "  1. Load Dec 2016 Sales File" << endl;
        cout << "  2. Load Monthly Sales File" << endl;
        cout << "  3. Exit Use Currently File" << endl;
        cout << "Enter choice: ";
        cin >> option;

        // Determine which file to load using switch statement
        switch (option)
        {
        case 1:
            file = "eBid_Monthly_Sales_Dec_2016.csv";
            cout << "Dec Monthly Sales Loaded\n"
                 << endl;
            return file;
        case 2:
            file = "eBid_Monthly_Sales.csv";
            cout << "Monthly Sales Loaded\n"
                 << endl;
            return file;
        case 3:
            cout << "No Change In File\n"
                 << endl;
            file = currFile;
            return file;
        }
    }
}

/**
 * The one and only main() method
 */
int main(int argc, char *argv[])
{

    // process command line arguments
    string csvPath;
    switch (argc)
    {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    string fileToLoad;
    int choice = 0;
    while (choice != 9)
    {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {

        // User chose to load bids from file
        case 1:
            // File select - To disable comment out the following 3 lines (line 268)
            fileToLoad = selectFile(csvPath);
            // Change value of csvPath - comment out next line to disable file select
            csvPath = fileToLoad;

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // User chose to display all bids
        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i)
            {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // User chose to run selectionSort
        case 3:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Runs selectionSort function
            selectionSort(bids);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // User chose to run quickSort
        // User chose to run selectionSort
        case 4:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Runs quickSort function
            quickSort(bids, 0, bids.size() - 1);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
