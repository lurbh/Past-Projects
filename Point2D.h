#ifndef POINT2D_H
#define POINT2D_H

#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

class Point2D
{
protected:
  int x;
  int y;
  double distFrOrigin;
  
  virtual void setDistFrOrigin();
public:
  Point2D();
  Point2D(int x, int y);
  virtual ~Point2D();
  
  int getX() const;
  int getY() const;
  double getScalarValue() const;
  
  void setX(int x);
  void setY(int y);

  Point2D& operator=(const Point2D&);

  bool operator==(const Point2D&) const;
  bool operator!=(const Point2D&) const;
  bool operator<(const Point2D&) const;
  bool operator>(const Point2D&) const;
  bool operator<=(const Point2D&) const;
  bool operator>=(const Point2D&) const;

  friend ostream& operator<<(ostream &,const Point2D &);
};

#endif