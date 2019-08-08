#ifndef GRID_H
#define GRID_H

#include <string>
#include <iostream>
#include <math.h> 

using namespace std;

// A class that stores a two ints x and y
class Grid
{
  int x;
  int y;
  
public:
  Grid();
  Grid(const Grid &);
  Grid(int, int);
  ~Grid();
  
  int getXGrid() const;
  int getYGrid() const;
  
  string toString() const;
  void printGrid() const;
  bool checkInBetween(Grid,Grid) const;
  
  void setXGrid(int);
  void setYGrid(int);
  
  Grid& operator=(Grid);
  bool operator==(Grid rhs) const;
  bool operator!=(Grid rhs) const;
};

#endif