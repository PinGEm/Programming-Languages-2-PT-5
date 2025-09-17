#include <iostream> // used for input output streams
#include <fstream> // used for writing log files
#include <filesystem> // used for the folder directories
#include "logger.h" // implement features for the logger file

using namespace std;
using std::chrono::system_clock;
using std::cout;

// When Class is Instantiated, do the following:
Logger::Logger()
{
	tt = system_clock::to_time_t(system_clock::now());
	timeStamp = ctime(&tt); // returns a string of the time stamp
	tm local_tm = *localtime(&tt);
	pathFile = "Logs/";
	
	std::filesystem::create_directory("Logs"); // If the "Logs" folder does not exist yet, we'll create one.
	cout << timeStamp;
	
	oss << local_tm.tm_year + 1900 << '-' << local_tm.tm_mon + 1 << '-' << local_tm.tm_mday; // +1900 and +1 is there to properly set the date to now.
	fileName = oss.str(); // combine the values together.
	fileName += ".txt";
	
	pathFile += fileName;
};

// Set the Timestamp to Whatever Time it is now
void Logger::setTimeStamp()
{
	tt = system_clock::to_time_t(system_clock::now());
	timeStamp = ctime(&tt);
};

// Get the Timestamp Value
std::string Logger::getTimeStamp()
{
	setTimeStamp();
	return timeStamp;
};

// Creates and Edits Existing Log Files
void Logger::createNewLog(std::string message, bool getNumberList, int numList[], int size)
{
	// Create the file, or append it if it exists
	ofstream MyFile(pathFile, std::ios::app);
	
	// If for some reason the file doesn't open, immediately exit.
	if(!MyFile.is_open())
	{
		return;
	}
	
	// If we're getting a number list, call another function to handle it
	if(getNumberList)
	{
		displayNumberList(numList, size);
		return;
	}
	
	// Input the message in the file.
	MyFile << message;
	
	// Close the file to save memory
	MyFile.close();
};

// Only called when getNumberList is true from createNewLog()
void Logger::displayNumberList(int numList[], int size)
{
	// Iterate through each number and concatenate them inside the fullList string.
	std::string fullList;
	for(int i = 0; i < size; i++)
	{
		fullList += std::to_string(numList[i]);
		if(i != size - 1)
		{
			fullList += '-';
		}
	}
	
	fullList += "\n\n";
	createNewLog(fullList);
};

// Ask the user if they'd like to log the session
bool askSessionLog()
{
	char userInput;
	cout << "Type '1' if you'd like to record this session in the logs." << '\n';
	cin >> userInput;
	
	if(userInput == '1')
	{
		return true;
	}
	
	return false;
}