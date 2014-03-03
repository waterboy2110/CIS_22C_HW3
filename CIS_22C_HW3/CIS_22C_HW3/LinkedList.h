// A class template for holding a linked list.
// The node type is also a class template.
// Header should only declare the class(s)
// And the prototypes
// Header will also define public and private
// cpp file will contain the implementation file

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template <class T>
class ListNode
{
public:
    T value;           // Node value
    ListNode<T> *next; // Pointer to the next node
	ListNode<T> *prev; // Pointer to the prevous node

    // Constructor
    ListNode (T nodeValue){ value = nodeValue; next = NULL; prev = NULL;}
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class T>
class LinkedList
{
private:
    ListNode<T> *head;     // List head pointer
	ListNode<T> *sentinel; // List sentinel node
    int count;

public:
    // Constructor
    LinkedList(){sentinel = head; sentinel = NULL; count = 0;} // Set the links correctly to the sentinel.

   // Destructor
   ~LinkedList();

   // Linked list operations
   int getCount() {return count;}
   // insert
   void insertNode(T);
   void insertNode(T, int);
   // delete
   void deleteNode(int);
   // Display methods
   void displayList(int, int) const;
   void displayListReverse(int, int) const;
   // Method to save to file
   bool saveToFile() const;
};

#endif

