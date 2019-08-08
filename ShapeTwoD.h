#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <string>
#include <math.h> 
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Grid.h"

using namespace std;

// Base Class containing items and functions for derived classes
class ShapeTwoD
{
protected:
  unsigned id;
  string name;
  bool containsWarpSpace;
  double area;
  vector<Grid> InShape;
  vector<Grid> OnShape;
  
public:
  ShapeTwoD(string, unsigned);
  ShapeTwoD(string, bool);
  ShapeTwoD(string, bool, unsigned);
  virtual ~ShapeTwoD();
  
  string getName() const; 
  bool getContainsWarpSpace() const;
  double getArea() const;
  unsigned getShapeId() const;
  vector<Grid> getInShape();
  vector<Grid> getOnShape();
  
  virtual string toString() const;
  
  virtual double computeArea() const = 0;
  virtual bool isPointInShape(int,int) const = 0;
  virtual bool isPointOnShape(int,int) const = 0;
  virtual void CheckPoints() = 0;
  
  string stringWarpSpace() const;
  string stringInShape() const;
  string stringOnShape() const;
  
  void setName(string);
  void setContainsWarpSpace(bool);
  void setArea(double);
  
  virtual void Read(ifstream&);  
  virtual void Write(ofstream&) const ;
};

#endif