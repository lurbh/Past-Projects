/******************************************************************************
Filename   : array.c
Author     : Lur Bing Huii
DP Email   : binghuii.lur@digipen.edu
Course     : CS120A
Assignment : 2
Due Date   : 7/11/2016
Brief Description:
This program contains functions that reverse arrays, add arrays, scale arrays, 
sum the dot product of any number arrays and cross product of three arrays.
******************************************************************************/

/******************************************************************************
Function    : reverse_array
Description : Reverses the order values that are in an array.
Inputs      : An int array a and the size of array a.
Outputs     : None.
******************************************************************************/
void reverse_array(int a[], int size)
{
  int i, tmp;
  /* Loops till the middle element of the array */
  for(i = 0; size > i; --size, ++i) 
  {
    /* Holds a value from the front half of the array */
    tmp = a[i]; 
    /* Switches the value from the front half the back half of the array */
    a[i] = a[size-1]; 
    /* Switches the value from the back half of the array with the value held */
    a[size-1] = tmp; 
  }
}

/******************************************************************************
Function    : add_arrays
Description : Adds the value of two given arrays into a single array.
Inputs      : Two int array a and b, the size of array a and an output array c.
Outputs     : None.
******************************************************************************/
void add_arrays(const int a[], const int b[], int c[], int size)
{
  int i;
  /* Loops to every element in the array */
  for(i = 0; i < size ; ++i) 
    c[i] = a[i] + b[i]; 
}

/******************************************************************************
Function    : scalar_multiply
Description : Scales a given array by a given multiplier.
Inputs      : An int array a, size of array a and a multiplier.
Outputs     : None.
******************************************************************************/
void scalar_multiply(int a[], int size, int multiplier)
{
  int i;
  /* Loops to every element in the array */
  for(i = 0; i < size ; ++i) 
    a[i] *= multiplier;
}

/******************************************************************************
Function    : dot_product
Description : Sums the value of the dot product of two given arrays.
Inputs      : Two int array a and array b and the size of array a.
Outputs     : Sum of dot product of arrays.
******************************************************************************/
int dot_product(const int a[], const int b[], int size)
{
  int sum, i;
  /* Loops to every element in the array */
  for(i = 0, sum = 0; i < size; ++i)
    /* Adds the dot product of two different arrays into a total value */  
    sum += a[i] * b[i]; 
  return sum; 
}

/******************************************************************************
Function    : cross_product
Description : Cross product of two given array to another array with all three 
              arrays having 3 elements in the array.
Inputs      : Two int array a and array b and and an output array c.
Outputs     : None.
******************************************************************************/
void cross_product(const int a[], const int b[], int c[])
{
  c[0] = a[1] * b[2] - a[2] * b[1]; 
  c[1] = -(b[2] * a[0] - b[0] * a[2]); 
  c[2] = a[0] * b[1] - a[1] * b[0]; 
}