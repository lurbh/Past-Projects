/******************************************************************************/
/*!
\file   FileStrings.cpp
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #6
\date   14/04/2017
\brief  
  This is the implementation file for a FileStringsr.
  
  Operations include:

  - Converting a string to UpperCase
  - Word Wrap a given string
  - Tokenize a given string
  - Constructor for SpellChecker
  - Get Info of a dictionary
  - Spell Check a given word with the dictionary
  - Count number of words with length
  - Count number of words starting with letter.
  - Given a string, find words in the dictionary 
    composed of the letters in the same order.
*/
/******************************************************************************/
#include <iostream>
#include <fstream>        // ifstream
#include "FileStrings.h"  // SpellChecker, StringUtils, DictionaryInfo

namespace CS170
{

/******************************************************************************/
/*!
  \brief
    Convert a string to UpperCase.
  
  \param string
    Reference to string to convert.
    
  \return 
    Reference to string to converted.
*/
/******************************************************************************/
std::string& StringUtils::UpperCase(std::string& string)
{
  std::string::iterator it;
  // Goes to every char and caps them if the char is a small letter
  for (it = string.begin(); it != string.end(); ++it)
    if (*it >= 'a' && *it <= 'z')
      *it -= SPACE;

  return string;
}

/******************************************************************************/
/*!
  \brief
    Word Wrap a given string.
  
  \param words
    Reference to string to wrap.
    
  \param line_length
    Length of each line.
    
  \return 
    Vector of strings wraped.
*/
/******************************************************************************/
std::vector<std::string> StringUtils::WordWrap
(const std::string& words, size_t line_length)
{
  std::vector<std::string> Para;
  std::string line;
  auto it = words.begin();
  unsigned pos, spacing;
  // Goes to every char in the string
  while(it != words.end())
  {
    // If the char is a space or if at the last char
    if(*it == ' ' || it == words.end() - 1)
    {
      // Finds the position of the next space
      pos = words.find_first_of(' ',it - words.begin() + 1);
      // If at the last word set pos to be max length
      if(pos > words.length())
        pos = words.length();
      // Caculate the end of the next word
      spacing = line.length() + ((words.begin() + pos) - it);
      
      // If at the last char
      if(it == words.end() - 1)
      {
        // Push back the char and add line to the vector
        line.push_back(*it);
        Para.push_back(line);
        line.clear();
      }
      // If the line with the next word is too long
      else if(spacing > line_length)
      {
        // Push back line into the vector
        Para.push_back(line);
        line.clear();
      }
      else
        line.push_back(*it);
    }
    // push back the char into line
    else
      line.push_back(*it);
    ++it;
  }
  return Para;
}

/******************************************************************************/
/*!
  \brief
    Tokenize a given string.
  
  \param words
    Reference to string to Tokenize.
    
  \return 
    Vector of strings Tokenize.
*/
/******************************************************************************/
std::vector<std::string> StringUtils::Tokenize(const std::string& words)
{
  std::vector<std::string> tokenize;
  std::string word;
  auto it = words.begin();
  // Goes to every char in the string
  while(it != words.end())
  {
    // When there is a space Push back the word to the vector if there is one
    if(*it == ' ')
    {
      if(!word.empty())
        tokenize.push_back(word);
      word.clear();
    }
    // Push back the char and add word to the vector when at the end
    else if (it == words.end() - 1)
    {
      word.push_back(*it);
      tokenize.push_back(word);
      word.clear();
    }
    // push back the char into word
    else
      word.push_back(*it);
    ++it;
  }
  return tokenize;
}

/******************************************************************************/
/*!
  \brief
    Constructor to add dictionary.
  
  \param dictionary
    Reference dictionary.
*/
/******************************************************************************/
SpellChecker::SpellChecker(const std::string &dictionary)
  :dictionary_{dictionary}
{
  
}

/******************************************************************************/
/*!
  \brief
    Get info of the dictionary.
  
  \param info
    Reference to info to set.
    
  \return 
    SCResult if file was open.
*/
/******************************************************************************/
SpellChecker::SCResult SpellChecker::GetInfo(DictionaryInfo &info) const
{
  std::ifstream filename;
  std::string str;
  info.shortest = 99;
  info.longest = 0;
  info.count = 0;
  filename.open(dictionary_.c_str());
  // If file is able to open
  if(filename.is_open())
  {
    // While not at the end of the file
    while(!filename.eof())
    {
      // Read in the word
      filename >> str;
      // Get length and check if its the longest or shortest
      unsigned length = str.length();
      if(length > info.longest)
        info.longest = length;
      if(length < info.shortest)
        info.shortest = length;
      ++info.count;
    }
    --info.count;
    filename.close();
    return scrFILE_OK;
  }
  else
     return scrFILE_ERR_OPEN; 
}

/******************************************************************************/
/*!
  \brief
    Check the spelling of a word with the dictionary.
  
  \param word
    Reference to word to check.
    
  \return 
    SCResult if word is found or if file was not open.
*/
/******************************************************************************/
SpellChecker::SCResult SpellChecker::SpellCheck(const std::string& word) const
{
  std::ifstream filename;
  std::string str, Capsword;
  Capsword = word;
  StringUtils::UpperCase(Capsword);
  filename.open(dictionary_.c_str());
  // If file is able to open
  if(filename.is_open())
  {
    // While not at the end of the file
    while(!filename.eof())
    {
      // Read in the word
      filename >> str;
      StringUtils::UpperCase(str);
      // Compare the word with every word in the dictionary
      // If word is found return scrWORD_OK
      if(str.compare(Capsword) == 0)
        return scrWORD_OK;
    }
    filename.close();
    // Word not found
    return scrWORD_BAD;
  }
  else
     return scrFILE_ERR_OPEN;
}

/******************************************************************************/
/*!
  \brief
    Count number of words with a each length and store them in a vector.
  
  \param lengths
    Reference to vector to set.
    
  \param count
    Longest length to check.
    
  \return 
    SCResult if file was open.
*/
/******************************************************************************/
SpellChecker::SCResult SpellChecker::WordLengths
(std::vector<int>& lengths, size_t count) const
{
  std::ifstream filename;
  std::string str;
  unsigned length = 0;
  filename.open(dictionary_.c_str());
  // If file is able to open
  if(filename.is_open())
  {
    // While not at the end of the file
    while(!filename.eof())
    {
      // Read in the word
      filename >> str;
      length = str.length();
      // If length is not more than max length
      if(length <= count)
        // Increase the value in the vector at the specific length
        ++lengths[length]; 
    }
    --lengths[length];
    filename.close();
    return scrFILE_OK;
  }
  else
     return scrFILE_ERR_OPEN;
}

/******************************************************************************/
/*!
  \brief
    Count number of words starting with letter .
  
  \param letter
    Letter to check with.
    
  \param count
    Reference to count to set.
    
  \return 
    SCResult if file was open.
*/
/******************************************************************************/
SpellChecker::SCResult SpellChecker::WordsStartingWith
(char letter, int& count) const
{
  std::ifstream filename;
  std::string str, Capsletter;
  Capsletter.push_back(letter);
  StringUtils::UpperCase(Capsletter);
  filename.open(dictionary_.c_str());
  // If file is able to open
  if(filename.is_open())
  {
    // While not at the end of the file
    while(!filename.eof())
    {
      // Read in the word
      filename >> str;
      StringUtils::UpperCase(str);
      // If starting letter matches increase count
      if(str.front() == Capsletter.front())
        ++count;
    }
    filename.close();
    return scrFILE_OK;
  }
  else
     return scrFILE_ERR_OPEN; 
}

/******************************************************************************/
/*!
  \brief
    Given a string, find words in the dictionary composed of the letters 
    in the same order.
  
  \param acronym
    Reference to acronym to check with.
    
  \param words
    Reference to vector of string to set.
    
  \param maxlen
    Maximun length to check.
    
  \return 
    SCResult if file was open.
*/
/******************************************************************************/
SpellChecker::SCResult SpellChecker::AcronymToWord
(const std::string& acronym, std::vector<std::string>& words, 
size_t maxlen) const
{
  std::ifstream filename;
  filename.open(dictionary_.c_str());
  std::string str, caps, caps2;
  caps = acronym;
  StringUtils::UpperCase(caps);
  // If file is able to open
  if(filename.is_open())
  {
    // While not at the end of the file
    while(!filename.eof())
    {
      // Read in the word
      filename >> str;
      caps2 = str;
      StringUtils::UpperCase(caps2);
      auto it = caps.begin();
      // If length is too long skip the word
      if(maxlen)
        if(caps2.length() > maxlen)
          continue;
      // Checks if the first letter matches
      if(*it == *caps2.begin())
      {
        ++it;
        // Check if the words has the rest of the Acronym
        for(unsigned i = 1; i < caps2.length(); ++i)
        {
          if(*it == caps2[i])
          {
            ++it;
            if(it == caps.end())
            {
              // If all letters in Acronym is found push back the word
              words.push_back(str);
              break;
            }
          }
        }
      }
    }
    filename.close();
    return scrFILE_OK;
  }
  else
     return scrFILE_ERR_OPEN; 
}
}

