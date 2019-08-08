#ifndef LINE2D_H
#define LINE2D_H

#include "Point2D.h"

class Line2D
{
  Point2D pt1;
  Point2D pt2;
  
protected:
  double length;
  
  virtual void setLength();
  
public:
  Line2D();
  Line2D(Point2D pt1,Point2D pt2);
  virtual ~Line2D();
  
  Point2D getPt1() const;
  Point2D getPt2() const;
  double getScalarValue() const;
  
  void setPt1(Point2D pt);
  void setPt2(Point2D pt);

  bool operator==(const Line2D&) const;
  bool operator!=(const Line2D&) const;
  bool operator<(const Line2D&) const;
  bool operator>(const Line2D&) const;
  bool operator<=(const Line2D&) const;
  bool operator>=(const Line2D&) const;

  friend ostream& operator<<(ostream &,const Line2D &);
};

#endif