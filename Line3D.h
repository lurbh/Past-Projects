#ifndef LINE3D_H
#define LINE3D_H

#include "Point3D.h"
#include "Line2D.h"

class Line3D : public Line2D
{
  Point3D pt1;
  Point3D pt2;
  
protected:
  void setLength() override;
  
public:
  Line3D();
  Line3D(Point3D pt1, Point3D pt2);
  ~Line3D();
  
  Point3D getPt1() const;
  Point3D getPt2() const;
  
  void setPt1(Point3D pt);
  void setPt2(Point3D pt);

  bool operator==(const Line3D&) const;
  bool operator!=(const Line3D&) const;
  bool operator<(const Line3D&) const;
  bool operator>(const Line3D&) const;
  bool operator<=(const Line3D&) const;
  bool operator>=(const Line3D&) const;

  friend ostream& operator<<(ostream &,const Line3D &);
};

#endif