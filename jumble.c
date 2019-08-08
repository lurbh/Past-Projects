/******************************************************************************
Filename   : jumble.c
Author     : Lur Bing Huii
DP Email   : binghuii.lur@digipen.edu
Course     : CS120A
Assignment : Assignment 4
Due Date   : 28/11/2016
Brief Description:
This program contains the functions that finds the length of a string and 
encodes/decodes a string.
******************************************************************************/

#include "jumble.h"

/******************************************************************************
Function    : mystrlen
Description : Find the length of a string
Inputs      : const unsigned char *string
Outputs     : The length of the string
******************************************************************************/
int mystrlen(const unsigned char *string)
{
  int i;
  /* Loops till the character is a null */
  for(i=0; *string != '\0'; string++)
    ++i;
  return i;
}

/******************************************************************************
Function    : jumble
Description : Encode/Decodes a given string based on the input given
Inputs      : unsigned char *string, const unsigned char *password,
              enum CODE_METHOD method, int passes
Outputs     : Nil
******************************************************************************/
void jumble(unsigned char *string, const unsigned char *password,
            enum CODE_METHOD method, int passes)
{
  int i, lengthS, lengthP;
  /* Pointer to a unsigned char */
  unsigned char *start = string;
  /* Pointer to a constant unsigned char */
  const unsigned char *pass = password;
  
  lengthS = mystrlen(string); /* Finds the length of given string */
  lengthP = mystrlen(password); /* Finds the length of given password */
  
  /* Loops for the amt of passes inputed */
  for(i=0; i < passes; ++i)
  {
    string = start; /* Resets pointer to string back to first char */
    pass = password; /* Resets pointer to password back to first char */
    
    /* Loops to every char in string */
    while(string - start < lengthS)
    {
      /* If Encoding */
      if(method == 0)
        *string += *pass; /* Encodes char */
      
      /* If Decoding */
      if(method == 1)
        *string -= *pass; /* Decodes char */
      
      string++; /* Points to the next char in string */
      pass++; /* Points to the next char in password */
      
      /* If pointer to char in password reaches the end */
      if(pass - password > lengthP - 1)
        pass = password; /* Resets pointer to password back to first char */
    }
  }
}