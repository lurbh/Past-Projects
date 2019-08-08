#include "Point3D.h"

// Default Constructor for Point3D 
Point3D::Point3D()
  : Point2D{}, z{0}
{

}

// Non-Default Constructor for Point3D that takes in three ints
Point3D::Point3D(int x, int y, int z)
  : Point2D{x,y}, z{z}
{
  setDistFrOrigin();
}

// Destructor for Point3D
Point3D::~Point3D()
{
  
}


// A getter function to get z value
int Point3D::getZ() const
{
  return z;
}

// A setter function to set z value
void Point3D::setZ(int z)
{
  this->z = z;
}

// A setter function to set and compute distFrOrigin
void Point3D::setDistFrOrigin()
{
  distFrOrigin = sqrt(x * x + y * y + z * z);
}

// Overloaded operator for =
Point3D& Point3D::operator=(const Point3D& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  return *this;
}

// Overloaded operator for ==
bool Point3D::operator==(const Point3D& rhs) const
{
  if(x == rhs.x)
    if(y == rhs.y)
      if(z == rhs.z)
        return true;
  return false;
}

// Overloaded operator for !=
bool Point3D::operator!=(const Point3D& rhs) const
{
  if(x != rhs.x)
    if(y != rhs.y)
      if(z != rhs.z)
        return true;
  return false;
}

// Overloaded operator for <
bool Point3D::operator<(const Point3D& rhs) const
{
  if(x == rhs.x)
    if (y == rhs.y)
      return z < rhs.z;
    else
      return y < rhs.y;
  else
    return x < rhs.x;
}

// Overloaded operator for >
bool Point3D::operator>(const Point3D& rhs) const
{
  if(x == rhs.x)
    if (y == rhs.y)
      return z > rhs.z;
    else
      return y > rhs.y;
  else
    return x > rhs.x;
}

// Overloaded operator for <=
bool Point3D::operator<=(const Point3D& rhs) const
{
  if(x == rhs.x)
    if (y == rhs.y)
      return z <= rhs.z;
    else
      return y <= rhs.y;
  else
    return x <= rhs.x;
}

// Overloaded operator for >=
bool Point3D::operator>=(const Point3D& rhs) const
{
  // 
  if(x == rhs.x)
    if (y == rhs.y)
      return z >= rhs.z;
    else
      return y >= rhs.y;
  else
    return x >= rhs.x;
}

// Overloaded operator for <<
ostream& operator<<(ostream & out,const Point3D & obj)
{
  out << "[" << right << setw(4) << obj.x << ", " << right << setw(4) << obj.y  << ", " << right << setw(4) << obj.z << "]   ";
  out << fixed << setprecision(3) << obj.distFrOrigin;
  return out;
}