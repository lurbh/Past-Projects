#include "Circle.h"

// Non-Default Constructor for Circle that takes in a string, bool, unsigned int and a array of 4 Grids
Circle::Circle(string name, bool containsWarpSpace, Grid centre, int radius, unsigned id)
  : ShapeTwoD{name,containsWarpSpace,id}, centre{centre}, radius{radius}
{
  CheckPoints();
}

// Non-Default Constructor for Circle that takes in an unsigned int
Circle::Circle(unsigned id)
  : ShapeTwoD{"Circle",id}
{
}

// Destructor for Circle
Circle::~Circle()
{
  
}

// A getter function that returns the centre 
Grid Circle::getCentre() const
{
  return this->centre;
}

// A getter function that returns the radius
int Circle::getRadius() const
{
  return this->radius;
}

// A setter function that sets the centre
void Circle::setCentre(Grid point)
{
  this->centre = point;
}

// A setter function that sets the radius
void Circle::setRadius(int radius)
{
  this->radius = radius;
}

// A setter function that sets the circle
void Circle::setCircle(Grid point, int radius)
{
  this->centre = point;
  this->radius = radius;
}

// A function that converts Square into a string
string Circle::toString() const
{
  ostringstream oss;
  
  // Calling toString() from the base class ShapeTwoD
  oss << ShapeTwoD::toString();
  oss << "Centre : " << centre.toString() << endl;
  oss << "Radius : " << radius << " units" << endl;
  oss << "Points on perimeter : ";
  oss << stringOnShape() << endl;
  oss << "Points within shape : ";
  oss << stringInShape() << endl;
  
  return (oss.str());
}

// A function that computes the area for a Circle
double Circle::computeArea() const
{
  return 3.14159 * pow(radius,2);
}

// A function that checks if a point is in shape
bool Circle::isPointInShape(int x, int y) const
{
  // return true when point is within radius
  if(x < centre.getXGrid() + radius && x > centre.getXGrid() - radius)
    if(y < centre.getYGrid() + radius && y > centre.getYGrid() - radius)
    {
      if(x == centre.getXGrid() && y == centre.getYGrid())
        return false;
      else
        return true;
    }
  return false;
}

// A function that checks if a point is on shape
bool Circle::isPointOnShape(int x, int y) const
{
  // return true when circumference is on grid
  if(x == centre.getXGrid() + radius || x == centre.getXGrid() - radius)
    if(y == centre.getYGrid())
    {
      return true;
    }
  if(y == centre.getYGrid() + radius || y == centre.getYGrid() - radius)
    if(x == centre.getXGrid())
    {
      return true;
    }
  return false;
}

// A function that set a bounding square to check the points within it
void Circle::CheckPoints() 
{
  int maxX = centre.getXGrid() + radius;
  int maxY = centre.getYGrid() + radius;
  
  // Goes through all the points
  for(int x = centre.getXGrid() - radius; x <= maxX; x++)
  {
    for(int y = centre.getYGrid() - radius; y <= maxY; y++)
    {
      // check if on shape 
      if(isPointOnShape(x,y))
        // push in if on shape
        OnShape.push_back(Grid{x,y});
        // check if in shape
      else if(isPointInShape(x,y))
        // push in if in shape
        InShape.push_back(Grid{x,y});
    }
  }
}

// A function that reads data from a file for a Circle obj
void Circle::Read(ifstream& s)
{
  ShapeTwoD::Read(s);
  s.read((char*)&centre, sizeof(Grid));
  s.read((char*)&radius, sizeof(int));
  CheckPoints();
}

// A function that writes data from to file for a Circle obj
void Circle::Write(ofstream& s) const
{
  int type = 4;
  s.write((char*)&type, sizeof(int));
  ShapeTwoD::Write(s);
  s.write((char*)&centre, sizeof(Grid));
  s.write((char*)&radius, sizeof(int));
}
