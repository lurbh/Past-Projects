#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int n)
  :size{n}
{
  adj = new int* [n];
  for (int i = 0; i < n; i++)
  {
    adj[i] = new int [n];
    for(int j = 0; j < n; j++)
      adj[i][j] = 0;
  }
}

void AdjacencyMatrix::add_edge(int origin, int destin)
{
  if( origin > size || destin > size || origin < 0 || destin < 0)
   cout << "Invalid edge!" << endl;
  else
    adj[origin][destin]++;
}

void AdjacencyMatrix::display()
{
  for (int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
      cout << adj[i][j] << " ";
    cout << endl;
  }
 
}

int AdjacencyMatrix::checkline(int n)
{
  int count = 0;
  for (int i = 0; i < size; i++)
  {
    if(adj[i][n] == 0)
      count++;
  }
  return count;
}

int AdjacencyMatrix::getblank(int n, int j)
{
  for (int i = 0; i < size; i++)
  {
    if(adj[n][i] == 0)
    {
      if(j == 0)
        return i;
      else
        --j;
    }
  }
  return 100;
}