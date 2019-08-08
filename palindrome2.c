/******************************************************************************
Filename   : palindrome2.c
Author     : Lur Bing Huii
DP Email   : binghuii.lur@digipen.edu
Course     : CS120A
Assignment : 3
Due Date   : 17/11/2016
Brief Description:
This program contain a function that checks if a set of character is a 
palindrome
******************************************************************************/

/******************************************************************************
Function    : is_palindrome2
Description : Checks if a set of character is a palindrome
Inputs      : A pointer to a character address phrase and the length of 
              characters to check.
Outputs     : 0 or 1.
******************************************************************************/
int is_palindrome2(const char *phrase, int length)
{
  int i;
  for(i = 0; i < length; ++i)
    if(*(phrase + i) != *(phrase + --length))
      return 0;
  return 1;
}