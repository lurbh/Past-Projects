/******************************************************************************/
/*!
\file   Point.h
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #3
\date   07/03/2017
\brief  
  This is the header file for all overloaded operators and constructors
  of a class called Point.
  
 Hours spent on this assignment: 1hrs
 
 Specific portions that gave you the most trouble: Nil
  
*/
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef POINT_H
#define POINT_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // istream, ostream

namespace CS170
{
/******************************************************************************/
/*!
  \class Point
  \brief  
    The Point class includes various overloaded operators and constructors.
    
    Overloaded operators include:

    - operator+  => translation
    - operator-  => translation
    - operator*  => scale
    - operator%  => rotation
    - operator-  => distance
    - operator^  => midpoint
    - operator+= => assignment
    - operator++ => pre/post increment
    - operator-- => pre/post decrement
    - operator-  => unary
    - operator<< => output
    - operator>> => input

*/
/******************************************************************************/
  class Point
  {
    public:
      // Constructors (2)
      Point();
      Point(double x, double y);
      // Overloaded operators (14 member functions)
      Point operator+(const Point & rhs);
      Point operator+(const double & rhs);
      Point operator-(const double & rhs);
      Point operator*(const double & rhs);
      Point operator%(const double & rhs);
      double operator-(const Point & rhs);
      Point operator^(const Point & rhs);
      Point& operator+=(const Point & rhs);
      Point& operator+=(const double & rhs);
      Point& operator++();
      Point operator++(int);
      Point& operator--();
      Point operator--(int);
      Point operator-();
      
      // Overloaded operators (2 friend functions)
      friend std::ostream& operator<<(std::ostream& os, const Point& pt);
      friend std::istream& operator>>(std::istream& os, Point& pt);
    private:
      double x_; // The x-coordinate of a Point
      double y_; // The y-coordinate of a Point

        // Helper functions
      double DegreesToRadians(double degrees) const;
      double RadiansToDegrees(double radians) const;
  };
  
    // Overloaded operators (2 non-member, non-friend functions)
    Point operator*(const double & lhs, Point& rhs);
    Point operator+(const double & lhs, Point& rhs);
    
    
} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
