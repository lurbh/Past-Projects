#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "ShapeTwoD.h"
#include "Grid.h"

using namespace std;

// Derived Class Square
class Square : public ShapeTwoD
{
  Grid points[4];
  
public:
  Square(unsigned);
  Square(string, bool, Grid[4], unsigned);
  ~Square();
  
  Grid getPoint(int) const;
  int getMinX() const;
  int getMinY() const;
  int getMaxX() const;
  int getMaxY() const;
  
  void setPoint(int,int,int);
  void setPoint(Grid,int);
  void setSquare(Grid[4]);
  
  string toString() const override;
  
  double computeArea() const override;
  bool isPointInShape(int,int) const override;
  bool isPointOnShape(int,int) const override;
  void CheckPoints() override;
  
  void Read(ifstream&) override;  
  void Write(ofstream&) const override;
};

#endif