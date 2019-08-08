#include <math.h>

template <typename T>
double scalar_difference (T obj1, T obj2)
{
  return fabs(obj1.getScalarValue() - obj2.getScalarValue());
}

template <typename T>
bool equals (T obj1, T obj2)
{
  return obj1 == obj2;
}