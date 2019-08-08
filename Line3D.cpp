#include "Line3D.h"

// Default Constructor for Line3D 
Line3D::Line3D()
  : pt1{0,0,0},pt2{0,0,0}
{

}

// Non-Default Constructor for Line3D that takes in two Point3D
Line3D::Line3D(Point3D pt1, Point3D pt2)
  : pt1{pt1},pt2{pt2}
{
  setLength();
}

// Destructor for Line3D
Line3D::~Line3D()
{
  
}

// A getter function to get pt1
Point3D Line3D::getPt1() const
{
  return pt1; 
}

// A getter function to get pt2
Point3D Line3D::getPt2() const
{
  return pt2;
}

// A setter function to set pt1
void Line3D::setPt1(Point3D pt)
{
  pt1 = pt;
}

// A setter function to set pt1
void Line3D::setPt2(Point3D pt)
{
  pt2 = pt;
}

// A setter function to set and compute length
void Line3D::setLength()
{
  int x = pt1.getX() - pt2.getX();
  int y = pt1.getY() - pt2.getY();
  int z = pt1.getZ() - pt2.getZ();
  length = sqrt (x * x + y * y + z * z);
}

// Overloaded operator for ==
bool Line3D::operator==(const Line3D& rhs) const
{
  if(pt1 == rhs.pt1)
    if(pt2 == rhs.pt2)
      return true;
  return false;
}

// Overloaded operator for !=
bool Line3D::operator!=(const Line3D& rhs) const
{
  if(pt1 != rhs.pt1)
    if(pt2 != rhs.pt2)
      return true;
  return false;
}

// Overloaded operator for <
bool Line3D::operator<(const Line3D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 < rhs.pt2;
  else
    return pt1 < rhs.pt1;
}

// Overloaded operator for >
bool Line3D::operator>(const Line3D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 > rhs.pt2;
  else
    return pt1 > rhs.pt1;
}

// Overloaded operator for <=
bool Line3D::operator<=(const Line3D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 <= rhs.pt2;
  else
    return pt1 <= rhs.pt1;
}

// Overloaded operator for >=
bool Line3D::operator>=(const Line3D& rhs) const
{
  if(pt1 == rhs.pt1)
    return pt2 >= rhs.pt2;
  else
    return pt1 >= rhs.pt1;
}

// Overloaded operator for <<
ostream& operator<<(ostream & out,const Line3D & obj)
{
  out << "[" << right << setw(4) << obj.pt1.getX() << ", " << right << setw(4) << obj.pt1.getY()  << ", " << right << setw(4) << obj.pt1.getZ() << "]   ";
  out << "[" << right << setw(4) << obj.pt2.getX() << ", " << right << setw(4) << obj.pt2.getY()  << ", " << right << setw(4) << obj.pt2.getZ() << "]   ";
  out << fixed << setprecision(3) << obj.length;
  return out;
}