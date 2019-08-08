#include "Point2D.h"

// Default Constructor for Point2D 
Point2D::Point2D()
  :x{0}, y{0}
{

}

// Non-Default Constructor for Point2D that takes in two ints
Point2D::Point2D(int x, int y)
  : x{x}, y{y}
{
  setDistFrOrigin();
}

// Destructor for Point2D
Point2D::~Point2D()
{
  
}

// A getter function to get x value
int Point2D::getX() const
{
  return x;
}

// A getter function to get y value
int Point2D::getY() const
{
  return y;
}

// A getter function to get distFrOrigin
double Point2D::getScalarValue() const
{
  return distFrOrigin;
}

// A setter function to set x value
void Point2D::setX(int x)
{
  this->x = x;
}

// A setter function to set y value
void Point2D::setY(int y)
{
  this->y = y;
}

// A setter function to set and compute distFrOrigin
void Point2D::setDistFrOrigin()
{
  distFrOrigin = sqrt(x * x + y * y);
}

// Overloaded operator for =
Point2D& Point2D::operator=(const Point2D& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  return *this;
}

// Overloaded operator for ==
bool Point2D::operator==(const Point2D& rhs) const
{
  if(x == rhs.x)
    if(y == rhs.y)
      return true;
  return false;
}

// Overloaded operator for !=
bool Point2D::operator!=(const Point2D& rhs) const
{
  if(x != rhs.x)
    if(y != rhs.y)
      return true;
  return false;
}

// Overloaded operator for <
bool Point2D::operator<(const Point2D& rhs) const
{
  if(x == rhs.x)
    return y < rhs.y;
  else
    return x < rhs.x;
}

// Overloaded operator for >
bool Point2D::operator>(const Point2D& rhs) const
{
  if(x == rhs.x)
    return y > rhs.y;
  else
    return x > rhs.x;
}

// Overloaded operator for <=
bool Point2D::operator<=(const Point2D& rhs) const
{
  if(x == rhs.x)
    return y <= rhs.y;
  else
    return x <= rhs.x;
}

// Overloaded operator for >=
bool Point2D::operator>=(const Point2D& rhs) const
{
  if(x == rhs.x)
    return y >= rhs.y;
  else
    return x >= rhs.x;
}

// // Overloaded operator for << 
ostream& operator<<(ostream & out,const Point2D & obj)
{
  out << "[" << right << setw(4) << obj.x << ", " << right << setw(4) << obj.y << "]   " << fixed << setprecision(3) << obj.distFrOrigin;
  return out;
}
