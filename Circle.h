#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include "ShapeTwoD.h"
#include "Grid.h"

using namespace std;

// Derived Class Circle
class Circle : public ShapeTwoD
{
  Grid centre;
  int radius;
  
public:
  Circle(unsigned);
  Circle(string, bool, Grid, int, unsigned);
  ~Circle();
  
  Grid getCentre() const;
  int getRadius() const;
  
  void setCentre(Grid);
  void setRadius(int);
  void setCircle(Grid,int);
  
  string toString() const override;
  
  double computeArea() const override;
  bool isPointInShape(int,int) const override;
  bool isPointOnShape(int,int) const override;
  void CheckPoints() override;
  
  void Read(ifstream&) override;  
  void Write(ofstream&) const override;
};

#endif