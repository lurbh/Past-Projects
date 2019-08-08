#include "Grid.h"

// Default Constructor for Grid class
Grid::Grid()
  : x{0}, y{0}
{
  
}

// Non-Default Constructor for Grid class that takes in two ints
Grid::Grid(int x, int y)
  :x{x}, y{y}
{
  
}

// Copy Constructor for Grid 
Grid::Grid(const Grid &rhs)
  :x{rhs.x}, y{rhs.y}
{
  
}

// Destructor for Grid
Grid::~Grid()
{

}

// A getter function to get x value
int Grid::getXGrid() const
{
  return this->x;
}

// A getter function to get y value
int Grid::getYGrid() const
{
  return this->y;
}

// A function that converts Grid into a string
string Grid::toString() const
{
  string s;
  s = "(" + to_string(x) + ", " + to_string(y) + ")";
  return s;
}

// A function that prints a Grid
void Grid::printGrid() const
{
  cout << "(" << x << ", " << y << ")";
}

// A setter function that sets the x value
void Grid::setXGrid(int x)
{
  this->x = x;
}

// A setter function that sets the y value
void Grid::setYGrid(int y)
{
  this->y = y;
}

// A funtion that takes in two other Grids and check if they are on the same line
bool Grid::checkInBetween(Grid rhs,Grid check) const
{
  // check if on the same x line
  if(x == check.x && check.x == rhs.x)
  {
    // check if inbetween the two points
    if((check.y < y && check.y > rhs.y) || (check.y > y && check.y < rhs.y))
      return true;  
  }
  // check if on the same y line
  else if(y == check.y && check.y == rhs.y)
  {
    // check if inbetween the two points
    if((check.x < x && check.x > rhs.x) || (check.x > x && check.x < rhs.x))
      return true;
  }
  return false;
}

// Overloaded operator for =
Grid& Grid::operator=(Grid rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  return *this;
}

// Overloaded operator for ==
bool Grid::operator==(Grid rhs) const
{
  if(x == rhs.getXGrid() && y == rhs.getYGrid())
    return true;
  else
    return false;
}

// Overloaded operator for !=
bool Grid::operator!=(Grid rhs) const
{
  if(x == rhs.getXGrid() && y == rhs.getYGrid())
    return false;
  else
    return true;
}