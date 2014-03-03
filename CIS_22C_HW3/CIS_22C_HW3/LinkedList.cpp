/*
* Implementation file for LinkedList
* 
*/


//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "LinkedList.h"
using namespace std;



//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
    ListNode<T> *newNode;             // A new node
    ListNode<T> *nodePtr;             // To traverse the list
    ListNode<T> *previousNode = NULL; // The previous node

    newNode = new ListNode<T>(newValue); // Allocate a new node and store newValue there.
    nodePtr = sentinel;                  // Position nodePtr at the head of list.
    previousNode = NULL;                 // Initialize previousNode to NULL.

	// Moves nodePtr to the end of the list
    while (nodePtr != NULL)
    {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
    }

    // If the new node is to be the 1st in the list,
    // set up the sentinel and have head point to it.
	// insert it before all other nodes.
    if (previousNode == NULL)
    {
		sentinel = newNode;
    }
    else  // Otherwise insert after the previous node.
    {
        previousNode->next = newNode;
		newNode->prev = previousNode;
    }
    newNode->next = nodePtr;
	//nodePtr->next = sentinel;
    count++;
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
// Overloaded to accomidate inserting a line at a  *
// specific point in the list.					   *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue, int lineNumber)
{
    ListNode<T> *newNode;             // A new node
    ListNode<T> *nodePtr;             // To traverse the list
    ListNode<T> *previousNode = NULL; // The previous node

    newNode = new ListNode<T>(newValue); // Allocate a new node and store newValue there.
	nodePtr = sentinel;					  // Position nodePtr at the sentinel.
    previousNode = NULL;                 // Initialize previousNode to NULL.

	// Moves nodePtr to the point of insertion
    for (int i = 0; i < lineNumber - 1; i++)	 //funky but works
    {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
    }
	// Insert the new node at the pointer 
	previousNode->next = newNode;
	newNode->prev = previousNode;
    newNode->next = nodePtr;
    count++;
}

//**************************************************
// The deleteNode function deletes node(s) with    *
// from the index(s) provided by the user.         *
// Deleting first node crashes program.					   *
// TODO: Need to test for first node. Will fix     *
// After circular / sentinal is implemented.	   *
//**************************************************
template <class T>
void LinkedList<T>::deleteNode(int fromLineNumber)
{
    ListNode<T> *nodePtr;             // To traverse the list
    ListNode<T> *previousNode = NULL; // The previous node

    nodePtr = sentinel;					 // Position nodePtr to the sentinel.
    previousNode = NULL;                 // Initialize previousNode to NULL.

	// Moves nodePtr to the point of deletion
    for (int i = 1; i < fromLineNumber; i++)
    {
		 previousNode = nodePtr;
         nodePtr = nodePtr->next;
    }
	

	// Delete the node at the pointer 
	previousNode->next = nodePtr->next;
    nodePtr->next->prev = previousNode->next;
	delete nodePtr;
    count--;
}

//**************************************************
// Definition of function saveToFile.
// This function will read all the data from
// the file. 
// Really should have put this in the cpp file
// but since ListNode is private I didn't have
// access. Well - I think.
//**************************************************
template <class T>
bool LinkedList<T>::saveToFile() const
{
   cout << "DEBUG in save\n";
   ofstream outFile;
   string fileName;
   bool success = true;
   cout << "Enter file name\n";
   cin >> fileName;

// Open file to write, if couldn't open, display error
// and exit with false
   outFile.open(fileName);
   if (!outFile)
   {
      cout << "Error opening " << fileName << "!\n";
      return false;
   }

    ListNode<T> *nodePtr;  // To move through the list.
	nodePtr = sentinel;		// Position nodePtr to the sentinel.

    while (nodePtr)
    {
       outFile << nodePtr->value << endl;	// Write to the file.
       nodePtr = nodePtr->next;				// Move to the next node.
   }

   outFile.close();
 
   if (!success)
      return false;

   return true;
}
//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template <class T>
void LinkedList<T>::displayList(int fromLine, int toLine) const
{
    ListNode<T> *nodePtr;  // To move through the list.
	int line = 1;		   // To display line numbers.
	nodePtr = sentinel;		// Position nodePtr to the sentinel.
	int nodesToDisplay = toLine - fromLine;		// Number of nodes to display.
	if(nodesToDisplay == 0)
		nodesToDisplay = 1;		// To be able to display one line when from and to are equal.

	// To display a range of nodes
	// Moves nodePtr to the point to display
    for (int i = 1; i < fromLine; i++)
    {
         nodePtr = nodePtr->next;
		 line ++;		// Allows the correct line number to be displayed
    }
	
    // While nodePtr points to a node, traverse the list.
    for (int i = nodesToDisplay; i >= 0; i--)
    {
        std::cout << line << ": " << nodePtr->value << std::endl;  // Display the value in this node.
        nodePtr = nodePtr->next;         // Move to the next node.
		line++;
   }
}

//***************************************************
// displayListReverse shows the value stored in each*
// node in reverse. Uses ints to define the nodes   *
// to display so a range of nodes is possible       *
//***************************************************
template <class T>
void LinkedList<T>::displayListReverse(int fromLine, int toLine) const
{
	ListNode<T> *nodePtr;	// To move through the list.
	nodePtr = sentinel;		// Position nodePtr to the sentinel.
	int line = 1;			// To display line numbers
	int nodesToDisplay = fromLine - toLine; // Nodes to display
	if (nodesToDisplay == 0)
		nodesToDisplay = 1;		// Allows one node to be displayed.
	
	// Find the end of the list.
	for (int i = 0; i < fromLine - 1; i++)
	{
		nodePtr = nodePtr->next;
		line++;
	}
	// Walk the list backwards and print
	for (int i = nodesToDisplay + 1; i >= 1; --i)
	{
		cout << line << ": " << nodePtr->value << endl; // Display the value in this node.
		nodePtr = nodePtr->prev;
		line--;
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
   ListNode<T> *nodePtr;    // To traverse the list
   ListNode<T> *nextNode;   // To point to the next node
   nodePtr = sentinel;		// Position nodePtr to the sentinel.

   // While nodePtr is not at the end of the list...
   while (nodePtr != NULL)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
