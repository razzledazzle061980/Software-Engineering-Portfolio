//============================================================================
// Name        : Temperature.cpp
// Author      : Eric Wallace
// Date		   : March 26, 2022
// Description : Reads temperature file to get temperatures
//============================================================================

#include<chrono>
#include<thread>
#include<iostream>
#include<fstream>
#include<cmath>
#include <queue>

using namespace std;

class CityInfo {
public:
	queue<int>cityTemp;
	queue<string>cityName;

	/*
	* Function to convert from Fahrenheit to
	* Celsius
	*
	* @param int inTemp - Temperature in Fahrenheit
	*	to be converted
	*
	* @return int outTemp - Temperature in Celsius
	*	to be inserted into a file
	*/
	int convertToCelsius(int inTemp) {
		int outTemp;

		// Convert Fahrenheit to Celsius
		outTemp = (int)round(((inTemp - 32) * 5) / (int)9);

		return outTemp;
	}

	/*
	*Function to open a file, if unable to
	* open an error message will be return.
	*
	*If successful it will return an object
	* of the file contents
	*
	*@param string filename - Filename of file to be
	* opened include path
	*
	*@return object tempData - Object containing the temperature data
	*/
	void ReadFileContents(string filename) {
		// Array to hold temperatures for each city
		// Instantiate a object for opening and reading a file
		ifstream readFile;

		// Output message indicating opening file is taking place
		cout << "Reading contents of  " << filename << " and saving data in a queue." << endl;

		// Open file
		readFile.open(filename);

		// Output message indicating a problem encountered while opening file
		if (!readFile.is_open()) {
			cout << "There was a problem opening " << filename << endl;
			return;
		}

		// Iterate through each row until end of file
		while (!readFile.eof()) {
			string city;
			int temp;
			// Add current values into an array to be used later
			readFile >> city >> temp;

			// Add data to queue
			cityName.push(city);
			cityTemp.push(temp);
		}

		// Close file after it has saved data
		readFile.close();

		// Output message indicating file processing complete
		cout << "Reading files has been completed, moving on to writing data to Celsius file" << endl;
	}

	/*
	* Function to write temperatures to
	* a file in Celsius
	*
	* @param string filename - Filename of file to be
	*	opened include path
	*
	* @param array data - Array containing temperature data
	*/
	void WriteContentsToFile(string filename) {
		// Instantiate a object for opening and writing to a file
		int temp;
		string city;
		ofstream writeFile;
		writeFile.open(filename);

		// Output message indicating a problem encountered while opening file
		if (!writeFile.is_open()) {
			cout << "There was a problem opening " << filename << endl;
			return;
		}

		// Checks to make sure the two queues have data
		if (this->cityName.empty() || this->cityTemp.size() == 0) {
			cout << "One or more queues are empty...";
			return;
		}

		// Get data from queues and save it in temp variables
		while (this->cityName.size() > 0 && this->cityTemp.size() > 0) {
			temp = convertToCelsius(this->cityTemp.front());
			this->cityTemp.pop();
			city = this->cityName.front();
			this->cityName.pop();

			// Write content to file
			writeFile << city << " " << temp << endl;
		}

		// Close file after completion
		writeFile.close();

		cout << "Processing has completed";
	}

	void sleep(int duration) {
		std::this_thread::sleep_for(std::chrono::seconds(duration));
	}
};

int main() {
	string FahrenheitFile = "FahrenheitTemperatures.txt";
	string CelsiusFile = "CelsiusTemperatures.txt";

	CityInfo cityInfo;
	


	// Read data from file
	cityInfo.ReadFileContents(FahrenheitFile);
	
	cityInfo.sleep(2);

	// Write data to file
	cityInfo.WriteContentsToFile(CelsiusFile);



}

