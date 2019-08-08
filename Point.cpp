/******************************************************************************/
/*!
\file   Point.cpp
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #3
\date   07/03/2017
\brief  
  This is the implementation file for Point class which 
  includes various overloaded operators and constructors.
  
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
  
 Hours spent on this assignment: 1hrs
 
 Specific portions that gave you the most trouble: Nil
  
*/
/******************************************************************************/
#include "Point.h"  // Point members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{

const double PI = 3.1415926535897;
const double EPSILON = 0.00001;

///////////////////////////////////////////////////////////////////////////////
// private member functions 
double Point::DegreesToRadians(double degrees) const
{
  return (degrees * PI / 180.0);
}

double Point::RadiansToDegrees(double radians) const
{
  return (radians * 180.0 / PI);
}


///////////////////////////////////////////////////////////////////////////////
// 16 public member functions (2 constructors, 14 operators) 
Point::Point()
  :x_{0},y_{0}
{
  
}
Point::Point(double x, double y)
  :x_{x},y_{y}
{
  
}

Point Point::operator+(const Point & rhs)
{
  double x,y;
  x = x_ + rhs.x_;
  y = y_ + rhs.y_;
  Point newpoint(x, y);
  return newpoint;
}

Point Point::operator+(const double & rhs)
{
  double x,y;
  x = x_ + rhs;
  y = y_ + rhs;
  Point newpoint(x, y);
  return newpoint;
}

Point Point::operator-(const double & rhs)
{
  double x,y;
  x = x_ - rhs;
  y = y_ - rhs;
  Point newpoint(x, y);
  return newpoint;
}

Point Point::operator*(const double & rhs)
{
  double x,y;
  x = x_ * rhs;
  y = y_ * rhs;
  Point newpoint(x, y);
  return newpoint;
}

Point Point::operator%(const double & rhs)
{
  double x,y;
  /*
  [x'] = [cosr -sinr][x]
  [y']   [sinr  cosr][y]
  [x'] = [cosr*x - sinr*y]
  [y']   [sinr*x + cosr*y]
  */
  x = x_ * cos(DegreesToRadians(rhs)) - y_ * sin(DegreesToRadians(rhs));
  y = x_ * sin(DegreesToRadians(rhs)) + y_ * cos(DegreesToRadians(rhs));
  // If x or y is between -EPSILON and +EPSILON, make it 0.0
  if (x > -EPSILON && x < EPSILON)
    x = 0.0;
  if (y > -EPSILON && y < EPSILON)
    y = 0.0;
  Point newpoint(x, y);
  return newpoint;
}

double Point::operator-(const Point & rhs)
{
  double x,y;
  // difference in x and y values
  x = x_ - rhs.x_;
  y = y_ - rhs.y_;
  // finding the hypotenuse
  double dist = sqrt(x*x+y*y);
  return dist;
}

Point Point::operator^(const Point & rhs)
{
  double x,y;
  // finding the mid point
  x = (rhs.x_ + x_) / 2;
  y = (rhs.y_ + y_) / 2;
  Point newpoint(x, y);
  return newpoint;
}

Point & Point::operator+=(const Point & rhs)
{
  // transform and assigns
  *this = *this + rhs;
  return *this;
}

Point & Point::operator+=(const double & rhs)
{
  // translation and assigns
  *this = *this + rhs;
  return *this;
}

Point & Point::operator++()
{
  ++x_;
  ++y_;
  return *this;
}

Point Point::operator++(int)
{
  // create a newpoint with current x_ and y_ and increment them 
  Point newpoint(x_++, y_++);
  return newpoint;
}

Point & Point::operator--()
{
  --x_;
  --y_;
  return *this;
}

Point Point::operator--(int)
{
  // create a newpoint with current x_ and y_ and decrement them 
  Point newpoint(x_--, y_--);
  return newpoint;
}

Point Point::operator-()
{
  Point newpoint(-x_, -y_);
  return newpoint;
}

///////////////////////////////////////////////////////////////////////////////
// 2 friend functions (operators)
std::ostream& operator<<(std::ostream& os, const Point& pt)
{
  // prints the point within braces with a comma between them
  os << "(" << pt.x_ << ", " << pt.y_ << ")";
  return os;
}

std::istream& operator>>(std::istream& os, Point& pt)
{
  // gets input for the point
  os >> pt.x_ >> pt.y_;
  return os;
}


///////////////////////////////////////////////////////////////////////////////
// 2 non-members, non-friends (operators)
Point operator+(const double & lhs, Point& rhs)
{
  // calls translation
  return rhs + lhs;
}

Point operator*(const double & lhs, Point& rhs)
{
  // calls scalar
  return rhs * lhs;
}


} // namespace CS170



