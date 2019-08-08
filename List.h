/******************************************************************************/
/*!
\file   List.h
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #5
\date   01/04/2017
\brief  
  This is the header file for class template called List.
*/
/*****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
///////////////////////////////////////////////////////////////////////////////

#include <iostream> /* ostream, endl */

namespace CS170
{
  template <typename T> class List;

  template <typename T>
  std::ostream & operator<<(std::ostream & os, const List<T> &list);

/******************************************************************************/
/*!
  \class List
  \brief  
    The List class is a container that implements a linked list
    
    Operations include:

    - Default constructor for List
    - Copy constructor for List
    - Non-Default constructor using an array for List
    - Destructor for List
    - Creating a new node at the end of the List
    - Creating a new node at the front of the List
    - Removing the node at the front of the List
    - Getting the value in the node at the front of the List
    - Getting the size of the List
    - Checking if the List is empty
    - Clears all the node in the List
    - Overloads the assignment operator to copy a List
    - Overloads the addition operator to merge two list
    - Overloads the addition assignment operator to merge two list
    - Overloads the subscript operator to access a node at a pos
    - Creating a new node
    - Getting the number of nodes created

*/
/******************************************************************************/
  template <typename T>
  class List
  {
    public:
        // Default constructor
      List(void);

        // Copy contructor for constructing a list from an existing list
      List(const List &list);

        // Contruct a list from a T array
      List(const T *array, int size);

        // Destructor
      ~List(void);

      void push_front(const T& Value); // adds the item to the front of the list
      void push_back(const T& Value);  // adds the item to the end of the list
      void pop_front(void);       // removes the first item in the list
      T front(void) const;        // retrieves the first item in the list
      int size(void) const;       // returns the number of items in the list
      bool empty(void) const;     // true if empty, else false
      void clear(void);           // clears the list

        // Overloaded assignment operator (=) for assigning one list to another
      List& operator=(const List &list);

        // Overloaded addition operator (+) for adding two lists
      List operator+(const List &list) const;

        // Overloaded addition/assignment (+=) for adding to a list "in place"
      List& operator+=(const List &list);

        // Overloaded subscript operators
      const T& operator[](int index) const;
      T& operator[](int index);

        // Output operator for printing lists (<<)
      friend std::ostream & operator<< <T> 
      (std::ostream & os, const List &list);

        // Returns the number of Nodes that have been created
     static int node_count(void);

    private:
        // Used to build the linked list
/******************************************************************************/
/*!
  \struct Node
  \brief  
    The Node struct that contains a value and the next Node
    
    Operations include:

    - Non-Default constructor for Node
    - Destructor for Node

*/
/******************************************************************************/
      struct Node
      {
        Node *next;     // pointer to the next Node
        T data;         // the actual data in the node
        Node(T value);  // non-default constructor
        ~Node(void);    // destructor
        static int node_count_; // number of Nodes created
      };

      Node *head_; // pointer to the head of the list
      Node *tail_; // pointer to the last node
      int size_;   // number of items on the list

        // All nodes are created in this method
      Node *new_node(const T& data) const;
  };

} // namespace CS170

#include "List.cpp"

#endif
////////////////////////////////////////////////////////////////////////////////

