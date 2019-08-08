#include <iostream>

using namespace std;

class AdjacencyMatrix
{
  int size;
  int **adj;
public:
  AdjacencyMatrix(int n);
  void add_edge(int origin, int destin);
  void display();
  int checkline(int n);
  int getblank(int n, int j = 0);
};