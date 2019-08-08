/******************************************************************************
Filename   : palindrome1.c
Author     : Lur Bing Huii
DP Email   : binghuii.lur@digipen.edu
Course     : CS120A
Assignment : 3
Due Date   : 17/11/2016
Brief Description:
This program contain a function that checks if an array is a palindrome
******************************************************************************/

/******************************************************************************
Function    : is_palindrome1
Description : Checks if an array is a palindrome
Inputs      : An char array phrase and the length of it.
Outputs     : 0 or 1.
******************************************************************************/
int is_palindrome1(const char phrase[], int length)
{
  int i;
  for(i = 0; i < length; ++i)
    if(phrase[i] != phrase[--length])
      return 0;
  return 1;
}