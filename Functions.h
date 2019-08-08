/******************************************************************************/
/*!
\file   Functions.h
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #4
\date   22/03/2017
\brief  
  This is the header file containing the declarations for function templates
  that will be used
  
 Hours spent on this assignment: 1.5hrs
 
 Specific portions that gave you the most trouble: Nil
  
*/
/******************************************************************************/
//---------------------------------------------------------------------------
#ifndef FUT2CTIOT2S_H
#define FUT2CTIOT2S_H
//---------------------------------------------------------------------------

namespace CS170
{
  template <typename InputIterator, typename OutputIterator> 
  OutputIterator copy(InputIterator start, InputIterator end, 
  OutputIterator right);
  template <typename InputIterator, typename T> 
  int count(InputIterator start, InputIterator end, const T &number);
  template <typename InputIterator> 
  void display(InputIterator start, InputIterator end);
  template <typename InputIterator, typename InputIterator2> 
  bool equal(InputIterator start, InputIterator end, InputIterator2 right);
  template <typename ForwardIterator, typename T> 
  void fill(ForwardIterator start, ForwardIterator end, const T &number);
  template <typename InputIterator, typename T> 
  InputIterator find(InputIterator start, InputIterator end, const T &number);
  template <typename ForwardIterator> 
  ForwardIterator max_element(ForwardIterator start, ForwardIterator end);
  template <typename ForwardIterator> 
  ForwardIterator min_element(ForwardIterator start, ForwardIterator end);
  template <typename ForwardIterator, typename T> 
  ForwardIterator remove(ForwardIterator start, ForwardIterator end, 
  const T &remove);
  template <typename ForwardIterator, typename T> 
  void replace(ForwardIterator start, ForwardIterator end, 
  const T &oldnumber, const T &newnumber);
  template <typename InputIterator> 
  int sum(InputIterator start, InputIterator end);
  template <typename T> 
  void swap(T &left, T &right);
  template <typename ForwardIterator> 
  void swap_ranges(ForwardIterator start, ForwardIterator end, 
  ForwardIterator right);
  /* 
   *  Other template function declarations for count, remove, replace, etc.
   *  go here. Make sure all of your declarations are sorted in alphabetical
   *  order. This includes putting the swap function above in the proper
   *  position.
   *
   */ 
  
  #include "Functions.cpp"
}

#endif
//---------------------------------------------------------------------------
