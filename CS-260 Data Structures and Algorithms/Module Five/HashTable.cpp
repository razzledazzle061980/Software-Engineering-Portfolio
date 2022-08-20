#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;
//============================================================================
// Global definitions visible to all methods and classes
//============================================================================
const unsigned int DEFAULT_SIZE = 179;
// forward declarations
double strToDouble(string str, char ch);
// define a structure to hold bid information
struct Bid {
	string bidId;
	string title;
	string fund;
	double amount;

	Bid()
	{
		amount = 0.0;
	}
};
void displayBid(Bid bid);
//============================================================================
// Hash Table class definition
//============================================================================
/**
* Define a class containing data members and methods to
* implement a hash table with chaining.
*/
class HashTable {
private:

	//Implementation of HashNode
	struct HashNode
	{
		//Declare bid as type of Bid
		Bid bid;
		//Declare key as type of unsigned
		unsigned key;
		//Declare nextPtr as type of HashNode*

		HashNode* nextPtr;
		// Implementation of default constructor

		HashNode()
		{
			//assign UINT_MAX to key
			key = UINT_MAX;
			//assign nullptr to nextPtr
			nextPtr = nullptr;
		}
		// Implementation of HashNode with parameter
		HashNode(Bid thisBid) : HashNode()
		{
			//assign thisBid to bid
			bid = thisBid;
		}
		// Implementation of HashNode with parameters
		HashNode(Bid thisBid, unsigned thisKey) : HashNode(thisBid)
		{
			//assign thisKey to key
			key = thisKey;
		}
	};
	
	//Declare a vector of HashNode
	vector<HashNode> nodeObject;

	//Declare nodeSize
	unsigned nodeSize = DEFAULT_SIZE;

	// Declare a hash with key
	unsigned int hash(int key);
public:

	//Declaration of Default constructor
	HashTable();
	HashTable(unsigned size);

	//Destructor
	virtual ~HashTable();

	//Declare of Insert function
	void Insert(Bid bid);

	//Declare of PrintAll function
	void PrintAll();

	//Declare of Remove function
	void Remove(string bidId);

	//Declare of Search function
	Bid Search(string bidId);
};
/**
* Default constructor
*/
HashTable::HashTable()
{
	//Call resize function on nodeObject
	nodeObject.resize(nodeSize);
}

HashTable::HashTable(unsigned size) {
	this->nodeSize = size;
	nodeObject.resize(nodeSize);
}
/**
* Destructor
*/
/// Declare Destructor
HashTable::~HashTable() {

	// Erase function to destructor nodeObject
	nodeObject.erase(nodeObject.begin());
}
/**
* Calculate the hash value of a given key.
* Note that key is specifically defined as
* unsigned int to prevent undefined results
* of a negative list index.
* @param key The key to hash
* @return The calculated hash
*/
unsigned int HashTable::hash(int key) {

	// Return modulus of key
	return key % nodeSize;
}
/**
* Insert a bid
* @param bid The bid to insert
*/
//Implementation of Insert function
void HashTable::Insert(Bid bid)
{
	// Declare key
	unsigned key = hash(atoi(bid.bidId.c_str()));

	// Get a previous key
	HashNode* prevNode = &(nodeObject.at(key));

	// Check if previous node is null
	if (prevNode == nullptr)
	{
		// Instantiate a new HashNode
		HashNode* next = new HashNode(bid, key);

		// Insert new nodeObject
		nodeObject.insert(nodeObject.begin() + key, (*next));
	}
	// Check if previous node is not null
	else if (prevNode != nullptr)
	{
		// Check if previous node key 
		// is equal to UINT_MAX
		if (prevNode->key == UINT_MAX)
		{
			// Declare key with value of prevNode->key
			prevNode->key = key;

			// Declare key with value of prevNode->bid
			prevNode->bid = bid;

			// Declare nextPrt with value of prevNode->nextPtr
			prevNode->nextPtr = nullptr;
		}
		// Check if previous node key 
		// is not equal to UINT_MAX
		else if (prevNode->key != UINT_MAX)
		{
			// Iterate over previous node
			while (prevNode->nextPtr != nullptr)
			{
				// Assign previous nextPtr to previous node
				prevNode = prevNode->nextPtr;
			}
		}
	}
}
/**
* Print all bids
*/
//Implementation of printAll function
void HashTable::PrintAll() {

	// Assign value of k to 0
	unsigned int k = 0;

	// Iterate through the nodeObject
	while (k < nodeObject.size())
	{
		//call displayBid function
		displayBid(nodeObject[k].bid);
		//increment k by 1
		++k;
	}
}
/**
* Remove a bid
* @param bidId The bid id to search for
*/
//Implementation of Remove function
void HashTable::Remove(string bidId) {

	// Delare deleteKey which is the key to delete
	unsigned deleteKey = hash(atoi(bidId.c_str()));

	// Destructor the object associated with the key
	nodeObject.erase(nodeObject.begin() + deleteKey);
}
/**
* Search for the specified bidId
* @param bidId The bid id to search for
*/
//Implementation of Search function
Bid HashTable::Search(string bidId)
{
	//Declare bid as type of Bid
	Bid bid;

	// Declare key
	unsigned key = hash(atoi(bidId.c_str()));

	//Declare hasBid as a new object from key
	HashNode* hasBid = &(nodeObject.at(key));

	// Check if hasBid key is not equal to UINT_MAX and
	// and hasBid is not equal to null and hasBid bidId
	// when compared to bidId equals 0
	if (hasBid->key != UINT_MAX && hasBid != nullptr
		&& hasBid->bid.bidId.compare(bidId) == 0)
	{
		// Return hasBid bid
		return hasBid->bid;
	}
	// Check if hasBid key is equal to UINT_MAX
	// or hasBid is equal to null
	if (hasBid->key == UINT_MAX || hasBid == nullptr)
	{
		// Return bid
		return bid;
	}
	// Iterate through hasBid as long as
	// it is not equal to null
	while (hasBid != nullptr)
	{
		// Check if hasBid bidId compared to bidId equals 0
		// and hasBid key does not equal UINT_MAX
		if (hasBid->bid.bidId.compare(bidId) == 0 && hasBid->key != UINT_MAX)
		{
			return hasBid->bid;
		}
		// Assign hasBid->nextPtr to hasBid
		hasBid = hasBid->nextPtr;
	}
	// Return bid
	return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << endl;
	return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	// read and display header row - optional
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;

	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			hashTable->Insert(bid);
		}
	}
	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
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
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath, bidKey;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		bidKey = "98109";
		break;
	case 3:
		csvPath = argv[1];
		bidKey = argv[2];
		break;
	default:
		csvPath = "eBid_Monthly_Sales.csv";
		bidKey = "98109";
	}

	// Define a timer variable
	clock_t ticks;

	// Define a hash table to hold all the bids
	HashTable* bidTable{};

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  4. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			bidTable = new HashTable();

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			loadBids(csvPath, bidTable);

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 2:
			// Initialize a timer variable before loading bids
			ticks = clock();

			bidTable->PrintAll();
			
			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 3:
			ticks = clock();

			bid = bidTable->Search(bidKey);

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) {
				displayBid(bid);
			}
			else {
				cout << "Bid Id " << bidKey << " not found." << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 4:
			cout << "Removing key: " << bidKey << endl;
			bidTable->Remove(bidKey);
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
