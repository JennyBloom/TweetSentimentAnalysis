/*
classTweets.cpp
Authors: Jeff Nicholson and Jenny Bloom
12.6.2015

this class will also manage the dictionary.
*/

//INCLUDE STATEMENTS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>
#include "classTweets.h"

using namespace std;


//Default Contstuctor
tweets::tweets()
{
  // .db is used to define a database file.
  // populate the dictionary
  ifstream dictionary; //creating locaction to store dictionary.
  string dictLine; //declaring each line inside dictionary.db
  dictionary.open("dictionary.db"); //open the dictionary file
  for (int d = 0; getline(dictionary, dictLine); d++)
  {
    transform(dictLine.begin(), dictLine.end(), dictLine.begin(), ::tolower);
    _dictionary.push_back(dictLine); //populate the vector _dictionary using push_back
  }
  dictionary.close();
}

//Methods
int tweets::parseTweet(string currentTweet, string currentKeyword)
{
  //find keyword inside current tweet. Going to use .find but requres trickery.
  int foundPert;
//  transform(currentTweet.begin(), currentTweet.end(), currentTweet.begin(), ::tolower);
  foundPert = currentTweet.find(currentKeyword); //within current tweet find keyword
  if (foundPert != string::npos) //trickery courtest of Collin Duncan.
  {
    return 0;
  }
  else
  {
    return 1; //if no keywords are found, return 1 (false, move onto next tweet)
  }
}

int tweets::analyzeTweet(string currentTweet)
{
  //find negative words inside dictionary vector. Loop through vector.
  stringstream analyzeStream(currentTweet); //initialize stringstream, put current tweet into stream
  string currentWord; //declare currentWord, counting through these.
  int negwordCount = 0;
  // loop through stream
  for (int w = 0; analyzeStream >> currentWord; w++) //redirect analyzeStream into currentWord using >>
  {
    for (int d = 0; d < _dictionary.size(); d++)
    {
      transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
      if (currentWord == _dictionary.at(d)) //if currentWord is equal to iteration inside dictionary
      {
        negwordCount++; //increment the counter, counts total number of negative words
      }
    }
  }
  //Threshold: If more than 2 negative words, tweet considered negative
  if (negwordCount >= 2)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
