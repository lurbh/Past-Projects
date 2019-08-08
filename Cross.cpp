#include "Cross.h"

// Non-Default Constructor for Cross that takes in a string, bool, unsigned int and a array of 12 Grids
Cross::Cross(string name, bool containsWarpSpace, Grid points[12], unsigned id)
  : ShapeTwoD{name,containsWarpSpace,id}
{
  for(int i = 0; i < 12; i ++)
    this->points[i] = points[i];
  getCorner();
  CheckPoints();
}

// Non-Default Constructor for Cross that takes in an unsigned int
Cross::Cross(unsigned id)
  : ShapeTwoD{"Cross",id}
{
  
}

// Destructor for Cross
Cross::~Cross()
{
  corner.clear();
}

// A getter function that returns a specific point
Grid Cross::getPoint(int no) const
{
  return this->points[no];
}

// A setter function that sets a specific point
void Cross::setPoint(int x,int y,int no)
{
  this->points[no].setXGrid(x);
  this->points[no].setYGrid(y);
}

// A setter function that sets a specific point
void Cross::setPoint(Grid point,int no)
{
  this->points[no] = point;
}

// A setter function that sets all the points
void Cross::setCross(Grid points[12])
{
  for(int i = 0; i < 12; i ++)
    this->points[i] = points[i];
}

// A function that converts Cross into a string
string Cross::toString() const
{
  ostringstream oss;
  
  // Calling toString() from the base class ShapeTwoD
  oss << ShapeTwoD::toString();
  oss << "Vertices  : " << endl;
  for(int i = 0; i < 12; i ++)
  {
    if(i < 10)
    {
      oss << "Point[" << i << + "]  : ";
      oss << points[i].toString() << endl;
    }
    else
    {
      oss << "Point[" << i << + "] : ";
      oss << points[i].toString() << endl;
    }
  }
  oss << "Points on perimeter : ";
  oss << stringOnShape() << endl;
  oss << "Points within shape : ";
  oss << stringInShape() << endl;
  
  return (oss.str());
}

// A function that computes the area for a cross
double Cross::computeArea() const
{
  double area = 0;
  int j = 11;
  // Goes through every two points beside each other
  for (int i=0; i<12; i++)
  {
    area += (points[j].getXGrid()+points[i].getXGrid()) * (points[j].getYGrid()-points[i].getYGrid());
    j = i;
  }
  return fabs(area/2);
}

// A function that checks if a point is in shape
bool Cross::isPointInShape(int x, int y) const
{
  // Get min and max for x and y
  int minX = getMinX();
  int minY = getMinY();
  int maxX = getMaxX();
  int maxY = getMaxY();
  Grid test(x,y);
  // Makes the four bounding corners
  Grid c1(minX,minY);
  Grid c2(minX,maxY);
  Grid c3(maxX,maxY);
  Grid c4(maxX,minY);
  // check if the points are on the corners of bounding rectangle
  if(test == c1)
    return false;
  if(test == c2)
    return false;
  if(test == c3)
    return false;
  if(test == c4)
    return false;
  // check if point is one of the points stored
  for(int i = 0; i < 12; i++)
  {
    if(points[i] == test)
      return false;
  }
  // makes the four rectangles within bounding rectangle
  for(int i : corner)
  {
    int j = i - 1;
    int k = i + 1;
    if( i == 11)
      k = 0;
    else if(i == 0)
      j = 11;
    // make the rectangle and check the points
    Rectangle newrec(points[j],points[i],points[k]);
    for(Grid i : newrec.getInShape())
    {
      if( i == test)
        return false;
    }
    for(Grid i : newrec.getOnShape())
    {
      if( i == test)
        return false;
    }
  }
  return true;
}

// A function that checks if a point is on shape
bool Cross::isPointOnShape(int x, int y) const
{
  int j = 11;
  Grid test(x,y);
  // Goes through every two points beside each other
  for (int i=0; i<12; i++)
  {
    // Check if point is inbetween two points
    if(points[i].checkInBetween(points[j],test))
      return true;
    j = i;
  }
  return false;
}

// A function that set a bounding rectangle to check the points within it
void Cross::CheckPoints()
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
int Cross::getMinX() const
{
  int min = 999999;
  for (int i=0; i<12; i++)
  {
    if(points[i].getXGrid() < min)
      min = points[i].getXGrid();
  }
  return min;
}

// A function that gets min y
int Cross::getMinY() const
{
  int min = 999999;
  for (int i=0; i<12; i++)
  {
    if(points[i].getYGrid() < min)
      min = points[i].getYGrid();
  }
  return min;
}

// A function that gets max x
int Cross::getMaxX() const
{
  int max = -999999;
  for (int i=0; i<12; i++)
  {
    if(points[i].getXGrid() > max)
      max = points[i].getXGrid();
  }
  return max;
}

// A function that gets max y
int Cross::getMaxY() const
{
  int max = -999999;
  for (int i=0; i<12; i++)
  {
    if(points[i].getYGrid() > max)
      max = points[i].getYGrid();
  }
  return max;
}

// A function that finds the inner corners for the cross
void Cross::getCorner()
{
  int minX = getMinX();
  int minY = getMinY();
  int maxX = getMaxX();
  int maxY = getMaxY();
  for(int i = 0; i < 12; i++)
  {
    if(points[i].getXGrid() != minX && points[i].getXGrid() != maxX
    && points[i].getYGrid() != minY && points[i].getYGrid() != maxY)
      corner.push_back(i);
  }
}

// A function that reads data from a file for a cross obj
void Cross::Read(ifstream& s) 
{
  ShapeTwoD::Read(s);
  for(int i = 0; i < 12; i++)
  {
    s.read((char*)&points[i], sizeof(Grid));
  }
  getCorner();
  CheckPoints();
}

// A function that writes data to a file for a cross obj
void Cross::Write(ofstream& s) const
{
  int type = 1;
  // write a type to know shape type
  s.write((char*)&type, sizeof(int));
  // write ShapeTwoD data in
  ShapeTwoD::Write(s);
  // write data for all the points
  for(int i = 0; i < 12; i++)
  {
    s.write((char*)&points[i], sizeof(Grid));
  }
}
