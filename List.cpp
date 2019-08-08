/******************************************************************************/
/*!
\file   List.cpp
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #5
\date   01/04/2017
\brief  
  This is the implementation file for all functions for List class.
  
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
  - Overloads the subscript operator to access a node at a position
  - Creating a new node
  - Getting the number of nodes created
  - Non-Default constructor for Node
  - Destructor for Node

*/
/******************************************************************************/
namespace CS170
{

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// static members

template <typename T>
int List<T>::Node::node_count_ = 0;

/******************************************************************************/
/*!
  \brief
    Get the number of Nodes created.
  
  \return 
    The number of nodes created.

*/
/******************************************************************************/
template <typename T>
int List<T>::node_count(void)
{
  return Node::node_count_;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// List::Node methods
/******************************************************************************/
/*!
  \brief
    Non-Default constructor for Node
  
*/
/******************************************************************************/
template <typename T>
List<T>::Node::Node(T value) : data(value)
{
  node_count_++;
}

/******************************************************************************/
/*!
  \brief
    Destructor for Node
  
*/
/******************************************************************************/
template <typename T>
List<T>::Node::~Node(void)
{
  node_count_--;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// public methods
/******************************************************************************/
/*!
  \brief
    Default Constructor for List.
  
*/
/******************************************************************************/
template <typename T>
List<T>::List()
  :head_{nullptr}, tail_{nullptr}, size_{0}
{
  
}

/******************************************************************************/
/*!
  \brief
    Copy Constructor for List.
  
*/
/******************************************************************************/
template <typename T>
List<T>::List(const List &list)
  :List()
{
  Node * copy = list.head_;
  for(int i = 0; i < list.size(); ++i)
  {
    push_back(copy->data);
    copy = copy->next;
  }
}

/******************************************************************************/
/*!
  \brief
    Non-Default constructor using an array for List
  
*/
/******************************************************************************/
template <typename T>
List<T>::List(const T *array, int size)
  :List()
{
  for(int i = 0; i < size; ++i)
    push_back(array[i]);
}

/******************************************************************************/
/*!
  \brief
    Destructor for List
  
*/
/******************************************************************************/
template <typename T>
List<T>::~List()
{
  clear();
}

/******************************************************************************/
/*!
  \brief
    Creates a new node at the front of the list.
  
  \param Value
    A number for the new node.

*/
/******************************************************************************/
template <typename T>
void List<T>::push_front(const T& Value)
{
  // Create a new node
  Node *n = new_node(Value);
  n->next = head_;
  head_ = n;
  // if the list is empty
  if(size_ == 0)
    tail_ = n;
  ++size_;
}

/******************************************************************************/
/*!
  \brief
    Creates a new node at the end of the list.
  
  \param Value
    A number for the new node.

*/
/******************************************************************************/
template <typename T>
void List<T>::push_back(const T& Value)
{
  // Create a new node
  Node *n = new_node(Value);
  // if the list is not empty
  if(size_)
  {
    tail_->next = n;
    tail_ = n;
  }
  else
  {
    head_ = n;
    tail_ = n;
  }
  ++size_;
}

/******************************************************************************/
/*!
  \brief
    Removes the node at the front of the list.
    
*/
/******************************************************************************/
template <typename T>
void List<T>::pop_front(void)
{
  Node * remove = head_;
  head_ = head_->next;
  delete remove;
  --size_;
}

/******************************************************************************/
/*!
  \brief
    Gets a value in the node at the start of the list.
  
  \return 
    Value in the node at the start of the list.

*/
/******************************************************************************/
template <typename T>
T List<T>::front(void) const
{
  return head_->data;
}

/******************************************************************************/
/*!
  \brief
    Gets a size of the list.
  
  \return 
    Size of the list

*/
/******************************************************************************/
template <typename T>
int List<T>::size(void) const 
{
  return size_;
}

/******************************************************************************/
/*!
  \brief
    Check if the list is empty.
  
  \return 
    True if the list is empty else false

*/
/******************************************************************************/
template <typename T>
bool List<T>::empty(void) const
{
  return !size_;
}

/******************************************************************************/
/*!
  \brief
    Removes all of the nodes in the list.

*/
/******************************************************************************/
template <typename T>
void List<T>::clear(void)
{
  while (!empty())
    pop_front();
}

/******************************************************************************/
/*!
  \brief
    Operator overloading for assignment operator to copy another list
  
  \param list
    Reference to the list to copy.
  
  \return 
    The copied list

*/
/******************************************************************************/
template <typename T>
List<T>& List<T>::operator=(const List &list)
{
  // Create a new list
  List<T> newlist;
  // Create a copy of the pointer to the first node
  Node * tmp = list.head_;
  // While tmp is not null
  while (tmp)
  {
    // push back the value in tmp into the new list
    newlist.push_back(tmp->data);
    // set tmp to be the next node
    tmp = tmp->next;
  }
  // Delete the old list
  clear();
  // Set the first and last to the first and last from the new list
  head_ = newlist.head_;
  tail_ = newlist.tail_;
  size_ = newlist.size_;
  newlist.head_ = nullptr;
  newlist.head_ = nullptr;
  newlist.size_ = 0;
  return *this;
}

/******************************************************************************/
/*!
  \brief
    Operator overloading for addition operator to merge two list into a new
    list
  
  \param list
    Reference to the list to merge.
  
  \return 
    The merge list

*/
/******************************************************************************/
template <typename T>
List<T> List<T>::operator+(const List &list) const
{
  List addedlist(*this);
  Node * tmp = list.head_;
  // while the list has not been tranversed till the end
  while(tmp)
  {
    // push back all the value in list into the new list
    addedlist.push_back(tmp->data);
    tmp = tmp->next;
  }
  return addedlist;
}

/******************************************************************************/
/*!
  \brief
    Operator overloading for addition assignment operator to another list into
    the current list
  
  \param list
    Reference to the list to merge.
  
  \return 
    The current list after merging

*/
/******************************************************************************/
template <typename T>
List<T>& List<T>::operator+=(const List &list)
{
  Node * tmp = list.head_;
  // while the list has not been tranversed till the end
  while(tmp)
  {
    // push back all the value in list into the current list
    push_back(tmp->data);
    tmp = tmp->next;
  }
  return *this;
}

/******************************************************************************/
/*!
  \brief
    Operator overloading for subscript operator access a node at a position.
  
  \param index
    Position of node to access.
  
  \return 
    The const reference value in the node at the position.

*/
/******************************************************************************/
template <typename T>
const T& List<T>::operator[](int index) const
{
  Node * tmp = head_;
  // Finds the node at the position
  for(int i = 0; i < index; ++i)
  {
    tmp = tmp->next;
  }
  return tmp->data;
}

/******************************************************************************/
/*!
  \brief
    Operator overloading for subscript operator access a node at a position.
  
  \param index
    Position of node to access.
  
  \return 
    The reference value in the node at the position.

*/
/******************************************************************************/
template <typename T>
T& List<T>::operator[](int index)
{
  Node * tmp = head_;
  // Finds the node at the position
  for(int i = 0; i < index; ++i)
  {
    tmp = tmp->next;
  }
  return tmp->data;
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// private methods

/******************************************************************************/
/*!
  \brief
    Allocate a node, initialize the data and next pointer.
  
  \param data
    The data to put in the node.
  
  \return 
    A pointer to the node.

*/
/******************************************************************************/
template <typename T>
typename List<T>::Node *List<T>::new_node(const T& data) const
{
  Node *node = new Node(data); // create the node
  node->next = nullptr;        // no next pointer yet
  return node;
}

} // namespace CS170


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// non-members

#include <iomanip>

/******************************************************************************/
/*!
  \brief
    Overloads left shift operator to output the list into an ostream object.
  
  \param os
    ostream object to output to.
    
  \param list
    The List to output.
  
  \return 
    The ostream object that was passed in.

*/
/******************************************************************************/
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the top
  typename CS170::List<T>::Node *pnode = list.head_;

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  return os;
}

