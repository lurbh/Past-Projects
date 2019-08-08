#include <math.h>

double circle_pi(int num_rectangles)
{
  double r, h, x, pi;
  int n, k;

  r = 2;
  pi = 0;
  n = 1;

  for (k = 1; k <= num_rectangles; ++k)
  {
    for(; n == 2 * k - 1 ; n += 2)
    {
      x = r / (num_rectangles * 2) * n;
      h = sqrt(r * r - x * x);
      pi += h * r / num_rectangles;
    }
  }
  return pi;
}

double leibniz_pi(int num_iterations)
{
  int i, n, k;
  double  pi, pi4;

  pi = i = k = 0;
  n = 1;

  while(k < num_iterations)
  {
    while(i <= k)
    {
      if(i == 0)
      pi += 1;
      else 
      {
        if(i % 2 == 1)
        pi -= (1.00 / n);
        else if(i % 2 == 0)
        pi += (1.00 / n);
      }
    ++i;
    }
    n += 2;
    ++k;
  }

  pi4 = pi * 4;
  return pi4;
}