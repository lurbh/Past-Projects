#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

class Point3D : public Point2D
{
protected:
  int z;
  
  void setDistFrOrigin() override;
  
public:
  Point3D();
  Point3D(int x, int y, int z);
  ~Point3D();
  
  int getZ() const;
  
  void setZ(int z);

  Point3D& operator=(const Point3D&);
  
  bool operator==(const Point3D&) const;
  bool operator!=(const Point3D&) const;
  bool operator<(const Point3D&) const;
  bool operator>(const Point3D&) const;
  bool operator<=(const Point3D&) const;
  bool operator>=(const Point3D&) const;

  friend ostream& operator<<(ostream &,const Point3D &);
};

#endif