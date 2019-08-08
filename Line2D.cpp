#include "Line2D.h"

// Default Constructor for Line2D 
Line2D::Line2D()
  :pt1{0,0},pt2{0,0}
{
  
}

// Non-Default Constructor for Line2D that takes in two Point2D
Line2D::Line2D(Point2D pt1,Point2D pt2)
  : pt1{pt1},pt2{pt2}
{
  setLength();
}

// Destructor for Line2D
Line2D::~Line2D()
{
  
}

// A getter function to get pt1
Point2D Line2D::getPt1() const
{
  return pt1;
}

// A getter function to get pt2
Point2D Line2D::getPt2() const
{
  return pt2;
}

// A getter function to get length
double Line2D::getScalarValue() const
{
  return length;
}

// A setter function to set pt1
void Line2D::setPt1(Point2D pt)
{
  pt1 = pt;
}

// A setter function to set pt2
void Line2D::setPt2(Point2D pt)
{
  pt2 = pt;
}

// A setter function to set and compute length
void Line2D::setLength()
{
  int x = pt1.getX() - pt2.getX();
  int y = pt1.getY() - pt2.getY();
  length = sqrt (x * x + y * y);
}

// Overloaded operator for ==
bool Line2D::operator==(const Line2D& rhs) const
{
  if(pt1 == rhs.pt1)
    if(pt2 == rhs.pt2)
      return true;
  return false;
}

// Overloaded operator for !=
bool Line2D::operator!=(const Line2D& rhs) const
{
  if(pt1 != rhs.pt1)
    if(pt2 != rhs.pt2)
      return true;
  return false;
}

// Overloaded operator for <
bool Line2D::operator<(const Line2D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 < rhs.pt2;
  else
    return pt1 < rhs.pt1;
}

// Overloaded operator for >
bool Line2D::operator>(const Line2D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 > rhs.pt2;
  else
    return pt1 > rhs.pt1;
}

// Overloaded operator for <=
bool Line2D::operator<=(const Line2D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 <= rhs.pt2;
  else
    return pt1 <= rhs.pt1;
}

// Overloaded operator for >=
bool Line2D::operator>=(const Line2D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 >= rhs.pt2;
  else
    return pt1 >= rhs.pt1;
}

// Overloaded operator for <<
ostream& operator<<(ostream & out,const Line2D & obj)
{
  out << "[" << right << setw(4) << obj.pt1.getX() << ", " << right << setw(4) << obj.pt1.getY() <<  "]   ";
  out << "[" << right << setw(4) << obj.pt2.getX() << ", " << right << setw(4) << obj.pt2.getY() <<  "]   ";
  out << fixed << setprecision(3) << obj.length;
  return out;
}