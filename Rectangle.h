#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "ShapeTwoD.h"
#include "Grid.h"

using namespace std;

// Derived Class Rectangle
class Rectangle : public ShapeTwoD
{
  Grid points[4];
  
public:
  Rectangle(unsigned);
  Rectangle(string, bool, Grid[4], unsigned);
  Rectangle(Grid,Grid,Grid);
  Rectangle(const Rectangle &);
  ~Rectangle();
  
  Grid getPoint(int) const;
  int getMinX() const;
  int getMinY() const;
  int getMaxX() const;
  int getMaxY() const;
  
  void setPoint(int,int,int);
  void setPoint(Grid,int);
  void setRectangle(Grid[4]);
  
  string toString() const override;
  
  double computeArea() const override;
  bool isPointInShape(int,int) const override;
  bool isPointOnShape(int,int) const override;
  void CheckPoints() override;
  
  void Read(ifstream&) override;  
  void Write(ofstream&) const override;
};

#endif