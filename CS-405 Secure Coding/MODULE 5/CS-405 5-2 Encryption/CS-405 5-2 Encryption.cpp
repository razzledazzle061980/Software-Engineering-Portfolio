// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

#define SIZE 50  // NOLINT(modernize-macro-to-enum)

// Count number of rows in file
int rowCount(string filename)
{
    ifstream _file(filename);
    return count(istream_iterator<char>(_file >> noskipws), {}, '\n');
}

// Gets the current date and time
std::string getDateTime() {
    const time_t c_time = time(nullptr);
    tm local_time{};

    // ReSharper disable once CppJoinDeclarationAndAssignment
    _localtime64_s(&local_time, &c_time);

    // Create a new time
    mktime(&local_time);  // NOLINT(cert-err33-c)

    char timestamp[SIZE];

    strftime(timestamp, sizeof(timestamp), "%F %T", &local_time);

    // return timestamp
    return timestamp;

}


/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for perfomance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    { // student need to change the next line from output[i] = source[i]
      // transform each character based on an xor of the key modded constrained to key length using a mod
        output[i] = source[i] ^ key[i % key_length];
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

// Reads a file and then returns the content
std::string read_file(const std::string& _filename)
{
	try {
        // Declare filename, open file and get number of rows
        const string& filename = _filename;
        ifstream file(filename);
        const int rows = rowCount(filename);
        const string assignment = "Module 5-2: Encryption Coding\r";

        // If file is open continue
        if (file.is_open())
        {
	        std::string file_text;
	        string line;

            // If there are no rows throw an error stating no data
            if (rows == 0)
            {
                throw runtime_error("No Data in " + filename);
            }

            // While there is another row of data continue
            while (getline(file, line))
            {
            	file_text += line + "\n";
            }

            // Inserts the assignment into the file_text after the file
            // has been parsed.
	        const size_t pos = file_text.find('\n') + 1;
            file_text.insert(pos, assignment);

            
            // Close file and return file_text
            file.close();
            return file_text;
        }
    }
    catch (exception& err) {
        cerr << "Error reading from file:  " << err.what() << endl;
    }
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');

    // did we find a newline
    if (pos != std::string::npos)
    {
    	// we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& _filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    // Call the function to get the date and time
    const string timestamp = getDateTime();

    try
    {
        // Declare filename and open file
        const string& filename = _filename;
        ofstream file(filename);

        // If file is open continue
        if (file.is_open())
        {
            file.clear();
            // Add each piece of data to the file
            file << student_name << endl;
            file << timestamp << endl;
            file << key << endl;
            file << data << endl;
        }

        // Close the file
        file.close();
	    
    } catch(exception &err)
    {
        cerr << "Error writing to file:  " << err.what() << endl;
    } 
}

int main()
{
    std::cout << "Encryption Decryption Test!" << std::endl;

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrytpteddatafile.txt";
	string  source_string = read_file(file_name);
    const std::string key = "password";

    // get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // This removes the student name from the source string so it is not repeated on the output
    const size_t pos = source_string.find('\n');
    source_string = source_string.erase(0, pos+1);

    // encrypt sourceString with key
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // save encrypted_string to file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // decrypt encryptedString with key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // save decrypted_string to file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

    // students submit input file, encrypted file, decrypted file, source code file, and key used
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
