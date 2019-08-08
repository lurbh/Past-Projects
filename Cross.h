#ifndef CROSS_H
#define CROSS_H

#include <string>
#include <algorithm> 
#include "ShapeTwoD.h"
#include "Grid.h"
#include "Rectangle.h"

using namespace std;

// Derived Class Cross
class Cross : public ShapeTwoD
{
  Grid points[12];
  vector<int> corner;
  
public:
  Cross(unsigned);
  Cross(string, bool, Grid[12], unsigned);
  ~Cross();
  
  Grid getPoint(int) const;
  int getMinX() const;
  int getMinY() const;
  int getMaxX() const;
  int getMaxY() const;
  
  void getCorner();
  
  void setPoint(int,int,int);
  void setPoint(Grid,int);
  void setCross(Grid[12]);
  
  string toString() const override;
  
  double computeArea() const override;
  bool isPointInShape(int,int) const override;
  bool isPointOnShape(int,int) const override;
  void CheckPoints() override;
  
  void Read(ifstream&) override;  
  void Write(ofstream&) const override;
};

#endif