/******************************************************************************/
/*!
\file   Functions.cpp
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #4
\date   22/03/2017
\brief  
  This is the implementation file for function templates.
  
  function templates include:

  - copy
  - count
  - display
  - equal
  - fill
  - find
  - max_element
  - min_element
  - remove
  - replace
  - sum
  - swap
  - swap_ranges
  
 Hours spent on this assignment: 1.5hrs
 
 Specific portions that gave you the most trouble: Nil
  
*/
/******************************************************************************/

#include <iostream> // cout, endl

/******************************************************************************/
/*!
  \brief
    Function template to copy over values from one container to another
    container.
  
  \param start
    Iterator to the start of the first container.
  
  \param end
    Iterator to the end of the first container.
    
  \param right
    Iterator to the start of the second container.
    
  \return 
    Iterator to the end of the second container.
*/
/******************************************************************************/
template <typename InputIterator, typename OutputIterator> 
OutputIterator copy(InputIterator start, InputIterator end,
OutputIterator right)
{
  // While both Iterator are at the same position
  while(start != end)
  {
    // Set the value in the right Iterator to be the value in the start Iterator
    // Increment the values after the copying
    *right++ = *start++;
  }
  //  Return the Iterator to the end of the second container.
  return right;
}

/******************************************************************************/
/*!
  \brief
    Function template to count the number of time a number appears in a 
    container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \param number
    Reference to the number to check.
    
  \return 
    The number of times the number appears.
*/
/******************************************************************************/
template <typename InputIterator, typename T> 
int count(InputIterator start, InputIterator end, const T &number)
{
  int count = 0;
  // While both Iterator are at the same position
  while(start != end)
  {
    // If the value in the Iterator is the same as number increment count
    if(*start++ == number)
      ++count;
  }
  return count;
}

/******************************************************************************/
/*!
  \brief
    Function template to display all the values in a container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
*/
/******************************************************************************/
template <typename InputIterator> 
void display(InputIterator start, InputIterator end)
{
  // if both Iterator are not at the same position
  if(start != end)
    std::cout << *start++;
  // While both Iterator are at the same position
  while(start != end)
  {
    std::cout << ", " <<*start++;
  }
  std::cout << std::endl;
}

/******************************************************************************/
/*!
  \brief
    Function template to check values from two container.
  
  \param start
    Iterator to the start of the first container.
  
  \param end
    Iterator to the end of the first container.
    
  \param right
    Iterator to the start of the second container.
    
  \return 
    True if containers are equal else false
*/
/******************************************************************************/
template <typename InputIterator, typename InputIterator2> 
bool equal(InputIterator start, InputIterator end, InputIterator2 right)
{
  // While both Iterator are at the same position
  while(start != end)
  {
    // If values in both Iterator are not the same return false
    if(*start++ != *right++)
      return false;
  }
  return true;
}

/******************************************************************************/
/*!
  \brief
    Function template to fill a container with a number.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \param number
    Reference to the number to fill.
    
*/
/******************************************************************************/
template <typename ForwardIterator, typename T> 
void fill(ForwardIterator start, ForwardIterator end, const T &number)
{
  // While both Iterator are at the same position
  while(start != end)
    // Set the value in the Iterator to be number
    *start++ = number;
}

/******************************************************************************/
/*!
  \brief
    Function template to find a number in a container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \param number
    Reference to the number to find.
    
  \return 
    Iterator that contains the number.
*/
/******************************************************************************/
template <typename InputIterator, typename T> 
InputIterator find(InputIterator start, InputIterator end, const T& number)
{
  // While both Iterator are at the same position
  while(start != end)
  {
    // if the value in the Iterator is equal to the number
    if(*start == number)
      // return the Iterator
      return start;
    ++start;
  }
  return end;
}

/******************************************************************************/
/*!
  \brief
    Function template to find the max element in a container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \return 
    Iterator that contains the max element.
*/
/******************************************************************************/
template <typename ForwardIterator> 
ForwardIterator max_element(ForwardIterator start, ForwardIterator end)
{
  ForwardIterator max = start;
  // While both Iterator are at the same position
  while(start != end)
  {
    // if the value in the Iterator is greater then the value in max
    if(*start > *max)
      // set the max to the the current Iterator
      max = start;
    ++start;
  }
  return max;
}

/******************************************************************************/
/*!
  \brief
    Function template to find the min element in a container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \return 
    Iterator that contains the min element.
*/
/******************************************************************************/
template <typename ForwardIterator> 
ForwardIterator min_element(ForwardIterator start, ForwardIterator end)
{
  ForwardIterator min = start;
  // While both Iterator are at the same position
  while(start != end)
  {
    // if the value in the Iterator is less then the value in min
    if(*start < *min)
      // set the min to the the current Iterator
      min = start;
    ++start;
  }
  return min;
}

/******************************************************************************/
/*!
  \brief
    Function template to remove all Iterator of a certain number in a container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \param number
    Reference to the number to remove.
    
  \return 
    Iterator to the new end of the container.
*/
/******************************************************************************/
template <typename ForwardIterator, typename T> 
ForwardIterator remove(ForwardIterator start,
ForwardIterator end, const T &number)
{
  ForwardIterator mover = start;
  // While both Iterator are at the same position
  while(start != end)
  {
    // if the value in the Iterator is not equal to the number to remove
    if(*start != number)
    {
      // set the value in start to mover
      *mover = *start;
      ++mover;
    }
    ++start;
  }
  // returns the new end of the container
  return mover;
}

/******************************************************************************/
/*!
  \brief
    Function template to replace a certain number in a container with another
    number.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \param oldnumber
    Reference to the oldnumber to replace.
    
  \param newnumber
    Reference to the newnumber to replace.
*/
/******************************************************************************/
template <typename ForwardIterator, typename T> 
void replace(ForwardIterator start, ForwardIterator end,
const T &oldnumber, const T &newnumber)
{
  // While both Iterator are at the same position
  while(start != end)
  {
    // if the value in the Iterator is equal to the oldnumber 
    if(*start == oldnumber)
      // set the value in the Iterator to be the newnumber 
      *start = newnumber;
    ++start;
  }
}

/******************************************************************************/
/*!
  \brief
    Function template to find the sum of all elements in a container.
  
  \param start
    Iterator to the start of the container.
  
  \param end
    Iterator to the end of the container.
    
  \return 
    Sum of all elements in a container.
*/
/******************************************************************************/
template <typename InputIterator> 
int sum(InputIterator start, InputIterator end)
{
  int sum = 0;
  // While both Iterator are at the same position
  while(start != end)
    // Add the value in the Iterator to sum
    sum += *start++;
  return sum;
}

/******************************************************************************/
/*!
  \brief
    Swaps two objects. There is no return value but the two objects are
    swapped in place.
  
  \param left
    The first object to swap.
  
  \param right
    The second object to swap.
*/
/******************************************************************************/
template <typename T> 
void swap(T &left, T &right)
{
  T temp(right); // need a temporary copy
  right = left;
  left = temp;
}

/******************************************************************************/
/*!
  \brief
    Function template to swap values in two different containers.
  
  \param start
    Iterator to the start of the first container.
  
  \param end
    Iterator to the end of the first container.
    
  \param right
    Iterator to the start of the second container.
    
*/
/******************************************************************************/
template <typename ForwardIterator> 
void swap_ranges(ForwardIterator start, ForwardIterator end, 
ForwardIterator right)
{
  // While both Iterator are at the same position
  while(start != end)
  {
    // swap the values in both Iterator
    swap(*start,*right);
    ++start;
    ++right;
  }
}

