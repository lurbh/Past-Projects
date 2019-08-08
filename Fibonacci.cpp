#include <iostream>

using namespace std;

// counters for Recursive and Iterative functions
static int RecursiveCount = 0;
static int IterativeCount = 0;

// Fibonacci Recursive function that returns Fibonacci sequence number
int fibRecursive(int num, bool count  = false)
{
  // to access the counting 
  if(count)
    RecursiveCount++;
  // if num is 0 or 1 return the same no
  if(num == 0 || num == 1)
  {
    return num;
  }
  else
  {
   // to access the counting  
    if(count)
      // returns Recursive function of (n-1) and (n-2)
      return fibRecursive(num - 1, true) + fibRecursive(num - 2, true);
    else
      return fibRecursive(num - 1) + fibRecursive(num - 2);
  }
}

// Fibonacci Iterative function that returns Fibonacci sequence number and prints Fibonacci number sequence
int fibIterative(int num)
{
  int i = 1;
  int j = 0;
  // if value keyed in is 0
  if(num)
    cout << j << ", " ;
  else
    cout << j << endl << endl;
  // Iterative loop from 0 to n;
  for(int k = 0; k < num; k++)
  {
    IterativeCount++;
    j = i + j;
    i = j - i;
    // at last number sequence
    if(k == num -1)
      cout << j << endl << endl;
    else
      cout << j << ", " ;
  }
  return j;
}

int main()
{
  int num;
  bool input = true;
  // Loop to ensure correct type of value in entered
  do
  {
    cout << "Enter a integer: ";
    cin >> num;
    if(cin.good())
    {
      if(num < 0)
      {
        cout << "Enter a positive integer. " << endl;
      }
      else
      {
        input = false;
      }
    }
    else
   {
      cout << "Not an integer." << endl << endl;
      cin.clear();
      cin.ignore();
    }
  }while(input);
  
  cout << endl << "Fibonacci number sequence up to " << num << ":" << endl << endl;
  // call for Fibonacci Recursive function to count Recursive
  fibRecursive(num, true);
  // Printing of Fibonacci number sequence
  for(int i = 0; i <= num; i ++)
    if(i == num)
      cout << fibRecursive(i) << endl << endl;
    else
      cout << fibRecursive(i) << ", ";
  cout << "Number of time the iterative function is called: " << RecursiveCount << endl << endl;
  cout << "Or" << endl << endl;
  cout << "Fibonacci number sequence up to " << num << ":" << endl << endl;
  // call for Fibonacci Iterative function to count Iterative and handles Printing of Fibonacci number sequence
  fibIterative(num);
  cout << "Number of time the iterative loop is executed : " << IterativeCount << endl;
  
  return 0;
}