// This program demonstrates the displayList member function.
/***********************
James Agua
CIS 22C Deanza Winter
Double Linked List

* Problems parsing string. Was trying to pick up
* and parse the entire string. read somewhat solved
* the problem in getUserInput but that would require
* Strtok to manage a range to tokenize. Decided to 
* get the input in the managers and focus on linking
* the list which is the object of this exercise.
* Remove Strtok if not used.
* Remove vectors if not used.
* Made the header and the member fuctions work by including both in main
***********************/
//#include "stdafx.h";
#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>	//Remove if not used

using namespace std;

// Constants for the menu choices
const char DISPLAY_NUMBER_LINES			= 'T',	// Display the number of lines
           PRINT_FORWARD				= 'F',	// Print the list forward
		   PRINT_BACK					= 'B',	// Print the list backward
		   INSERT_LINE					= 'I',	// Insert <line number> <text>
		   LIST_LINES					= 'L',	// List lines <line number> < line number>
		   DELETE_LINES					= 'D',	// Delete lines <line number> <line number>
		   SAVE_FILE					= 'S',	// Save list to file <filename>
		   HELP_CHOICE					= 'H',	// This menu
		   ABOUT_CHOICE					= 'A',	// About the author
           QUIT_CHOICE					= 'Q';	// End the program

// About String
const string ABOUTSTRING = "\nAuthor: James Agua 20122405\nDate: Feb 02, 2014\nCIS27C HW3-Linked Lists\nWinter Deanza\n";

// Menu Display
const string HELP_MENU = 
	"T\tDisplay the number of lines\n"
	"F\tPrint the list forward\n"
	"B\tPrint the list backward\n"
	"I\tInsert <line number> <text>\n"
	"L\tList lines <line number> < line number>\n"
	"D\tDelete lines <line number> <line number>\n"
	"S\tSave list to file <filename>\n"
	"H\tThis menu\n"
	"A\tAbout the author\nQ\tEnd the program\n\n";

// Function Prototypes
bool processFile(LinkedList<string> *);
void printLineCount(LinkedList<string> *);
void printHelp();
void printAbout();
string getUserChoice();
void Strtok(vector<string>*, string, char*);	// ***Remove if not used***
void insertManager(LinkedList<string> *);
void listManager(LinkedList<string> *);
void deleteManager(LinkedList<string> *);
bool numberInRange(int, int);
int getLineFrom(int);
int getLineTo(int);

int main()
{
   string choice;			// hold a menu choice
   bool success = false;	// User menu success
   bool status = false;		// File read status
   vector<string> vString;	// ***Remove if not used***

   // Define a pointer to a LinkedList object.
   LinkedList<string> *strList;

   // Allocate
   strList = new LinkedList<string>;
   
   // Add the file data to the list
   status = processFile(strList);
   cout << "Enter H for help\n";
   
    while (!success)
    {
		choice = getUserChoice(); // will need the string to carry the args
        switch (toupper(choice[0]))
        {
           case DISPLAY_NUMBER_LINES:
                printLineCount(strList);
                break;
           case PRINT_FORWARD:
                strList->displayList(1, strList->getCount());
				break;
		   case PRINT_BACK:
			   strList->displayListReverse(strList->getCount(), 1);
				break;
		   case INSERT_LINE:
			   insertManager(strList);
			   break;
		   case LIST_LINES:
			   listManager(strList);
			   break;
		   case DELETE_LINES:
			   deleteManager(strList);
			   break;
		   case SAVE_FILE:
			   if(status == strList->saveToFile())
				   cout << "File Saved\n";
			   break;
		   case HELP_CHOICE:
			   printHelp();
				break;
		  case ABOUT_CHOICE:
			  printAbout();
			  break;
		  case QUIT_CHOICE:
			  success = true;
			  break;
		  default:
			  cout << "Type H for help.\n";
			  status = false;
        }
    }

   delete strList;
   return 0;
}

/**~*~*
   This function takes input from the user.
   If the input is not valid (a valid menu choice) it
   prompts the user to type H for help until a vailid input
   is entered.
*~**/
string getUserChoice()
{
	cout << ">";
    string userChoice;
    bool success;
	cin >> userChoice;
    cin.clear();			// to clear the error flag
	cin.ignore(80, '\n');	// to discard the unwanted input from the input buffer
    return userChoice;
}

//**************************************
// Definition of function listManager  *
// Takes a reference from the caller of*
// pointer to object LinkedList.       *
// Prompts for lines to list.          *
// Determines if list should be printed*
// forward or backward and calls       *
// respective method to display the	   *
// list.
//**************************************
void listManager(LinkedList<string> *list)
{
	string LineNumber;
	int fromLine = getLineFrom(list->getCount());	// get the line from
	int toLine = getLineTo(list->getCount());		// get the line to

	// Determine whether to print the list forward or reverse.
	if(fromLine < toLine)
		list->displayList(fromLine, toLine);
	else
		list->displayListReverse(fromLine, toLine);
}

//**************************************
// Definition of function deleteManager
// This funciton takes a reference to the
// LinkedList, asks user for lines to delete
// and calls deleteNode().
//**************************************
void deleteManager(LinkedList<string> *list)
{
	string LineNumber;
	int fromLine = getLineFrom(list->getCount());	// get the line from
	int toLine = getLineTo(list->getCount());		// get the line to

	//swap to and from - no need to care about which way to call deleteNode()
	if (fromLine > toLine)
	{
		int temp;
		temp = toLine;
		toLine = fromLine;
		fromLine = temp;
	}

	int nodesToDelete = toLine - fromLine; // Find the number of nodes to delete
	if(nodesToDelete == 0)				   // To allow only one node to be deleted
		nodesToDelete = 1;

	for(int i = 0; i < nodesToDelete; i++)
	{
		list->deleteNode(fromLine);
	}
}
//**************************************
// Definition of function insertManager
// Function takes the linkList to access it's
// members. Asks user for input and calls 
// overloaded insertNode().
// Will use the vector method if time permits.
// This function takes the vector of strings
// from the users choice and tests string for
// an int. If true it will hand the vector
// to overloaded insert.
//***************************************
void insertManager(LinkedList<string> *list)
{
	string lineNumber;
	int line;
	bool success = false; //delete if not used
	string data;

	cout << "<line>\n";
	lineNumber = getUserChoice();
	if(! (istringstream(lineNumber) >> line) ) line = 0; // convert to int
	
	if(numberInRange(line, list->getCount())) // Test if number in range
	{
		cout << "Enter data to insert:\n";
		getline(cin, data);
		list->insertNode(data, line);
	}
}

//**************************************************
// Definition of function processFile.
// This function will read all the data from
// the file. 
//**************************************************

bool processFile(LinkedList<string> *list)
{
   ifstream inFile;
   string readStr;
   string fileName;
   string data;
   bool empty = true;
   fileName = "input.txt";

// Open file to read, if couldn't open, display error
   // and exit with false
   inFile.open(fileName);
   if (!inFile)
   {
      cout << "Error opening " << fileName << "!\n";
      return false;
   }

   while (getline(inFile, readStr))  // get data from file.
   {
	   list->insertNode(readStr);   
   }

   inFile.close();
 
   if (empty)
      return false;

   return true;
}

//*************************
// Definition of printLineCount
// Prints the number of lines read
// from the test file
//*************************
void printLineCount(LinkedList<string> *list)
{
	cout << "Number of lines in the list: " << list->getCount() << "\n";
}

//*************************
// Definition of printHelp
// Prints the choices available
// for the menu.
//*************************
void printHelp()
{
	cout << "\nHelp Menu\n" << HELP_MENU;
}

//*************************
// Definition of printAbout
// Prints the About information
// for the program
//*************************
void printAbout()
{
	cout << ABOUTSTRING;
}

bool numberInRange(int number, int count)
{
	if(number <= 0 || number > count ) // Test if number in range
	{
		cout << "Invalid input\n";
		return false;
	}
	return true;
}
//**************************************************
// Definition of function getLineFrom
// Takes a int of the list size.
// Promts the user for a line to display from
// Tests for within range.
//**************************************************
int getLineFrom(int nodeCount)
{
	string LineNumber;	// Users input.
	int fromLine;

	// get the line from and test for range.
	do
	{
		cout << "Line from:\n";
		LineNumber = getUserChoice();
		if(! (istringstream(LineNumber) >> fromLine) ) fromLine = 0; // convert to int
	} while(!numberInRange(fromLine, nodeCount));

	return fromLine;
}

//**************************************************
// Definition of function getLineFrom
// Takes a int of the list size.
// Promts the user for a line to display from
// Tests for within range.
//**************************************************
int getLineTo(int count)
{
	string LineNumber;
	int toLine;
	// Get the user input and test for range.
	do
	{
		cout << "Line to:\n";
		LineNumber = getUserChoice();
		if(! (istringstream(LineNumber) >> toLine) ) toLine = 0; // convert to int
	} while(!numberInRange(toLine, count));

	return toLine;
}


//***************************************************
// Definition of function Strok.
// This function tokenizes the string and returns
// each element of the string as a string in a vector.
// REMOVE IF NOT USED
//***************************************************
void Strtok(vector<string>* vstring, string cptr, char* delimiter)
{
	string astring = cptr;
	string stemp;
	int start = 0;
	int index = astring.find(delimiter);
	// Process the string and load the vector
	while (index != string::npos)
	{
		stemp.assign(astring,start,index-start);
		vstring->push_back(stemp);
		start = index + 1;
		index = astring.find(delimiter,start);
	}
	stemp.assign(astring,start,astring.length()-start);
	vstring->push_back(stemp);
}

