/******************************************************************************
Filename   : spellcheck.c
Author     : Lur Bing Huii
DP Email   : binghuii.lur@digipen.edu
Course     : CS120A
Assignment : Assignment 5
Due Date   : 07/12/2016
Brief Description:
This program contains the functions that makes any string uppercase, finds 
the infomation of the text, counts the amount of words starting with a 
certain letter, the number of words for each length and checks the spelling 
of the text.
******************************************************************************/
#include <string.h> /*                                     */
#include <stdio.h>  /* FILE                                */

/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h" 

/******************************************************************************
Function    : mystrupr
Description : Converts a strings to uppercase
Inputs      : char *string
Outputs     : Pointer to the start of the same string
******************************************************************************/
char *mystrupr(char *string)
{
  char *capsstring = string;
  int length = strlen(string);
  int i;
  for(i=0; i<length; ++i)
    /* If the ASCII value represents a small letter */
    if(*(capsstring + i) >= 97 && *(capsstring + i) <= 122)
      /* changes it to a Capital letter */
      *(capsstring + i) = *(string + i) - 32;
  return capsstring;
}

/******************************************************************************
Function    : words_starting_with
Description : Counts the number of words starting with a certain letter
Inputs      : const char *dictionary, char letter
Outputs     : Number of words starting with the letter or FILE_ERR_OPEN
******************************************************************************/
int words_starting_with(const char *dictionary, char letter)
{
  FILE *doc;
  int wordcount = 0;
  char read[LONGEST_WORD];
  char* caps;
  
  /* Open the file for reading and checks if it's successful */
  if(doc = fopen(dictionary, "rt"))
  {
    /* While not at the end of the file */
    while (!feof(doc))
    {
      /* Read in the next line */
      if(fgets(read, LONGEST_WORD, doc))
      {
        /* If first letter is same as letter */
        if(read[0] == letter)
          ++wordcount;
        /* Make all the letter caps */
        mystrupr(read);
        /* If first letter is same as letter */
        if(read[0] == letter)
          ++wordcount;
      }
    }
    /* Close the file */
    fclose(doc);
    return wordcount;
  }
  else
    return FILE_ERR_OPEN;
}

/******************************************************************************
Function    : word_lengths
Description : Counts the number of words based on the length of the word
Inputs      : const char *dictionary, int lengths[], int count
Outputs     : FILE_OK or FILE_ERR_OPEN
******************************************************************************/
int word_lengths(const char *dictionary, int lengths[], int count)
{
  FILE *doc;
  char read[LONGEST_WORD];
  int length;
  
  /* Open the file for reading and checks if it's successful */
  if(doc = fopen(dictionary, "rt"))
  {
    /* While not at the end of the file */
    while (!feof(doc))
    {
      /* Read in the next line */
      if(fgets(read, LONGEST_WORD, doc))
      {
        /* Calculates the lenth of the string */
        length = strlen(read) - 1;
        /* if length is less than count */
        if(length <= count)
        {
          /* increase lengths[length] by one */
          lengths[length] += 1;
        }
      }
    }
    /* Close the file */
    fclose(doc);
  
    return FILE_OK;
  }
  else
    return FILE_ERR_OPEN;
}

/******************************************************************************
Function    : info
Description : Finds the shortest and longest word together with the total 
              number of words in the text file.
Inputs      : const char *dictionary, int *shortest, int *longest, 
              int *num_words
Outputs     : FILE_OK or FILE_ERR_OPEN
******************************************************************************/
int info(const char *dictionary, int *shortest, int *longest, int *num_words)
{
  FILE *doc;
  int longestlength = 0;
  int shortestlength  = LONGEST_WORD;
  int length = 0;
  int num = 0;
  char read[LONGEST_WORD];
  
  /* Open the file for reading and checks if it's successful */
  if(doc = fopen(dictionary, "rt"))
  {
    /* While not at the end of the file */
    while (!feof(doc))
    {
      /* Read in the next line */
      if(fgets(read, LONGEST_WORD, doc))
      {
        ++num;
        /* Calculates the lenth of the string */
        length = strlen(read) - 1;
        /* if length is longer than longestlength */
        if(length > longestlength)
          longestlength = length;
        /* if length is shorter than shortestlength */
        if(length < shortestlength)
          shortestlength = length;
      }
    }
    /* Close the file */
    fclose(doc);
  
    /* set shortest to be shortestlength */
    *shortest = shortestlength;
    /* set longest to be longestlength */
    *longest = longestlength;
    /* set num_words to be num */
    *num_words = num;
    
    return FILE_OK;
  }
  else
    return FILE_ERR_OPEN;
}

/******************************************************************************
Function    : spell_check
Description : Checks the spelling of a word with the dictionary
Inputs      : const char *dictionary, const char *word
Outputs     : WORD_OK or WORD_BAD or FILE_ERR_OPEN
******************************************************************************/
int spell_check(const char *dictionary, const char *word)
{
  FILE *doc;
  char read[LONGEST_WORD];
  char Word[LONGEST_WORD];
  char *caps;
  const char* capsword;
  
  /* Open the file for reading and checks if it's successful */
  if(doc = fopen(dictionary, "rt"))
  {
    /* Copies the a editable pointer */
    strcpy(Word,word);
    /* Make all the letter caps */
    mystrupr(Word);
    
    /* While not at the end of the file */
    while (!feof(doc))
    {
      /* Read in the next line */
      if(fgets(read, LONGEST_WORD, doc))
      {
        char *position_letter = read;
        
        /* Finds the end of string */
        while(*position_letter++ != '\n');
        /* Replaces \n with \0 character */
        *--position_letter = '\0';
        /* Make all the letter caps */
        mystrupr(read);
        /* if words are the same */
        if(strcmp(Word, read) == 0)
        {
          /* Close the file */
          fclose(doc);
          return WORD_OK;
        }
          
      }
    }
    /* Close the file */
    fclose(doc);
    return WORD_BAD;
  }
  else
    return FILE_ERR_OPEN;
}