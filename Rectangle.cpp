#include "Rectangle.h"

// Non-Default Constructor for Rectangle that takes in a string, bool, unsigned int and a array of 4 Grids
Rectangle::Rectangle(string name, bool containsWarpSpace, Grid points[4], unsigned id)
  : ShapeTwoD{name,containsWarpSpace,id}
{
  for(int i = 0; i < 4; i ++)
    this->points[i] = points[i];
  CheckPoints();
}

// Non-Default Constructor for Rectangle that takes in an unsigned int
Rectangle::Rectangle(unsigned id)
  : ShapeTwoD{"Rectangle",id}
{
}

// Non-Default Constructor for Rectangle that takes 3 Grids
Rectangle::Rectangle(Grid a,Grid b,Grid c)
  : ShapeTwoD{"Rectangle",false,0}
{
  int x, y;
  // set last point
  if( a.getXGrid() == b.getXGrid())
  {
    x = c.getXGrid();
    y = a.getYGrid();
  }
  else
  {
    x = a.getXGrid();
    y = c.getYGrid();
  }
  Grid test(x,y);
  points[0] = a;
  points[1] = b;
  points[2] = c;
  points[3] = test;
  CheckPoints();
}

// Copy Constructor for Rectangle 
Rectangle::Rectangle(const Rectangle &rhs)
  : ShapeTwoD{rhs.name,rhs.containsWarpSpace,rhs.id}
{
  for(int i = 0; i < 4; i ++)
    points[i] = rhs.points[i];
  CheckPoints();
}

// Destructor for Rectangle
Rectangle::~Rectangle()
{

}
 
// A getter function that returns a specific point 
Grid Rectangle::getPoint(int no) const
{
  return this->points[no];
}

// A setter function that sets a specific point
void Rectangle::setPoint(int x,int y,int no)
{
  this->points[no].setXGrid(x);
  this->points[no].setYGrid(y);
}

// A setter function that sets a specific point
void Rectangle::setPoint(Grid point,int no)
{
  this->points[no] = point;
}

// A setter function that sets all the points
void Rectangle::setRectangle(Grid points[4])
{
  for(int i = 0; i < 4; i ++)
    this->points[i] = points[i];
}

// A function that converts Rectangle into a string
string Rectangle::toString() const
{
  ostringstream oss;
  
  // Calling toString() from the base class ShapeTwoD
  oss << ShapeTwoD::toString();
  oss << "Vertices  : " << endl;
  for(int i = 0; i < 4; i ++)
  {
    oss << "Point[" << i << "]  : ";
    oss << points[i].toString() << endl;
  }
  oss << "Points on perimeter : ";
  oss << stringOnShape() << endl;
  oss << "Points within shape : ";
  oss << stringInShape() << endl;
  
  return (oss.str());
}

// A function that computes the area for a Rectangle
double Rectangle::computeArea() const
{
  double area = 0;
  int j = 3;
  // Goes through every two points beside each other
  for (int i=0; i<4; i++)
  {
    area += (points[j].getXGrid()+points[i].getXGrid()) * (points[j].getYGrid()-points[i].getYGrid());
    j = i;
  }
  return fabs(area/2);
}

// A function that checks if a point is in shape
bool Rectangle::isPointInShape(int x, int y) const
{
  Grid test(x,y);
  // if point is the corner point in not in shape
  for(int i = 0; i < 4; i++)
  {
    if(points[i] == test)
      return false;
  }
  return true;
}

// A function that checks if a point is on shape
bool Rectangle::isPointOnShape(int x, int y) const
{
  int j = 3;
  Grid test(x,y);
  // Goes through every two points beside each other
  for (int i=0; i<4; i++)
  {
    // Check if point is inbetween two points
    if(points[i].checkInBetween(points[j],test))
      return true;
    j = i;
  }
  return false;
}

// A function that set a bounding rectangle to check the points within it
void Rectangle::CheckPoints()
{
  int minX = getMinX();
  int minY = getMinY();
  int maxX = getMaxX();
  int maxY = getMaxY();
  // Goes through all the points
  for(int x = minX; x <= maxX; x++)
    for(int y = minY; y <= maxY; y++)
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

// A function that gets min x 
int Rectangle::getMinX() const
{
  int min = 999999;
  for (int i=0; i<4; i++)
  {
    if(points[i].getXGrid() < min)
      min = points[i].getXGrid();
  }
  return min;
}

// A function that gets min y
int Rectangle::getMinY() const
{
  int min = 999999;
  for (int i=0; i<4; i++)
  {
    if(points[i].getYGrid() < min)
      min = points[i].getYGrid();
  }
  return min;
}

// A function that gets max x 
int Rectangle::getMaxX() const
{
  int max = -999999;
  for (int i=0; i<4; i++)
  {
    if(points[i].getXGrid() > max)
      max = points[i].getXGrid();
  }
  return max;
}

// A function that gets max y
int Rectangle::getMaxY() const
{
  int max = -999999;
  for (int i=0; i<4; i++)
  {
    if(points[i].getYGrid() > max)
      max = points[i].getYGrid();
  }
  return max;
}

// A function that reads data from a file for a Rectangle obj
void Rectangle::Read(ifstream& s) 
{
  ShapeTwoD::Read(s);
  for(int i = 0; i < 4; i++)
  {
    s.read((char*)&points[i], sizeof(Grid));
  }
  CheckPoints();
}

// A function that writes data to a file for a Rectangle obj
void Rectangle::Write(ofstream& s) const
{
  int type = 2;
  // write a type to know shape type
  s.write((char*)&type, sizeof(int));
  // write ShapeTwoD data in
  ShapeTwoD::Write(s);
  // write data for all the points
  for(int i = 0; i < 4; i++)
  {
    s.write((char*)&points[i], sizeof(Grid));
  }
}
