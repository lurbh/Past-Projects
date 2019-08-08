#include "Square.h"

// Non-Default Constructor for Square that takes in a string, bool, unsigned int and a array of 4 Grids
Square::Square(string name, bool containsWarpSpace, Grid points[4], unsigned id)
  : ShapeTwoD{name,containsWarpSpace,id}
{
  for(int i = 0; i < 4; i ++)
    this->points[i] = points[i];
  CheckPoints();
}

// Non-Default Constructor for Square that takes in an unsigned int
Square::Square(unsigned id)
  : ShapeTwoD{"Square",id}
{
}

// Destructor for Square
Square::~Square()
{
  
}

// A getter function that returns a specific point 
Grid Square::getPoint(int no) const
{
  return this->points[no];
}

// A setter function that sets a specific point
void Square::setPoint(int x,int y,int no)
{
  this->points[no].setXGrid(x);
  this->points[no].setYGrid(y);
}

// A setter function that sets a specific point
void Square::setPoint(Grid point,int no)
{
  this->points[no] = point;
}

// A setter function that sets all the points
void Square::setSquare(Grid points[4])
{
  for(int i = 0; i < 4; i ++)
    this->points[i] = points[i];
}

// A function that converts Square into a string
string Square::toString() const
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

// A function that computes the area for a Square
double Square::computeArea() const
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
bool Square::isPointInShape(int x, int y) const
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
bool Square::isPointOnShape(int x, int y) const
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

// A function that gets min x 
int Square::getMinX() const
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
int Square::getMinY() const
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
int Square::getMaxX() const
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
int Square::getMaxY() const
{
  int max = -999999;
  for (int i=0; i<4; i++)
  {
    if(points[i].getYGrid() > max)
      max = points[i].getYGrid();
  }
  return max;
}

// A function that set a bounding square to check the points within it
void Square::CheckPoints()
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

// A function that reads data from a file for a Square obj
void Square::Read(ifstream& s)
{
  ShapeTwoD::Read(s);
  for(int i = 0; i < 4; i++)
  {
    s.read((char*)&points[i], sizeof(Grid));
  }
  CheckPoints();
}

// A function that writes data from to file for a Square obj
void Square::Write(ofstream& s) const
{
  int type = 3;
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
