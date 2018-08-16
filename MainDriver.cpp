/*
MainDriver.cpp
Authors: Jeff Nicholson and Jenny Bloom
12.6.2015

References:
http://www.cplusplus.com/doc/tutorial/basic_io/
https://www.daniweb.com/programming/software-development/threads/90228/flushing-the-input-stream
https://en.wikipedia.org/wiki/Data_buffer
*/

//INCLUDE STATEMENTS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include "classTweets.h"
#include "classmath.h"

using namespace std;

int main(int argc, char* argv[])
{
  //error checking: let user know to include tweet.txt.
  if (argc < 2)
  {
    cout << "Invalid number of arguments\n" << endl;
    cout << "USAGE: a.out <tweetfile_name> [flags]" << endl;
    cout << "-v: Verbose output" << endl;
    return 1;
  }

  string tweetLine; //declaring all lines in .txt file as strings
  vector<string> tweetVector; //declaring a vector to store tweets
  int position;

  ifstream tweetText;
  tweetText.open(argv[1]);
  for (int i = 0; getline(tweetText, tweetLine); i++)
  {
    position = tweetLine.find('|'); //take tweets on right of '|' delimiter
    int beginningCount = position + 1; //Calculate position in string
    tweetVector.push_back(tweetLine.substr(beginningCount)); //Populate vector with each tweet from .txt file.
    transform(tweetVector.at(i).begin(), tweetVector.at(i).end(), tweetVector.at(i).begin(), ::tolower);
  }
  double numTweets=tweetVector.size();
  tweetText.close();

  vector<string> keywords; // declaring a vector to store keywords
  string word;
  cout << "What Tweet #hashtags or keywords do want to look for? (enter one at a time or 'quit') " << endl; // Ask the first question once
  getline(cin, word);
	while ((word.length() > 0) && (word != "quit"))
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (find(keywords.begin(), keywords.end(), word) != keywords.end())
    {
      cout << "[ERROR] Word already inputted into keywords list" << endl;
    }
    else
    {
      keywords.push_back(word);
    }
    cout << "Enter another #hashtag or keyword or 'quit'" << endl;
  	getline(cin, word);
	}

  // loop through tweetVector to parse. Parsing takes place in class
  // class tweets; //creating object tweets which is instance of classTweets
  tweets currentTweet;
  int counterPert = 0; //declaring and assigning pertinent tweets counter
  int counterNeg = 0; //declaring and assigning negative tweets counter
  int negfound = 0; // switch to indicate if negative word already found (0=not found; 1=found)
  for (int i = 0; i < tweetVector.size(); i++)
    {
    negfound=0;
    for (int j = 0; j < keywords.size(); j++)
      {
      int pertTweet = currentTweet.parseTweet(tweetVector.at(i), keywords.at(j)); //.at is the method of the vector class returning that value to the tweetVector or keywords vector location.
      if (pertTweet == 0)
      {
        int negativeTweet = currentTweet.analyzeTweet(tweetVector.at(i)); //send the tweet to the class method analyzeTweet. (NOTE: Inside .analyzeTweet, link to negative words - class notes)
        if ((negativeTweet == 0) && (negfound == 0)) //if tweet is actually negative, 0 = true, negative tweet found
        {
	  negfound=1;
          if (argc > 2)
          {
            if (strcmp(argv[2],"-v")==0)
            {
              cout<<tweetVector.at(i)<< "\n\n";
            }
          }
          //increment counter of negative tweets
          counterNeg++; //if negative tweet is found, count the negative tweet.
        }
        counterPert++; //if pertinent tweet is found, count the pertinent tweet.
      }
    }
  }

  //THE MATH. Likely be another class processing math.
  //creating object percentages which is instance of classMath
  classMath percentages(counterPert, counterNeg, numTweets);
  double percentPert = percentages.mathPert(); //accessing methods mathPert part of percentages class
  double percentNegpert = percentages.mathNegpert();

  cout << "The total number of tweets examined is: " << tweetVector.size() << endl;
  cout << percentPert << "% ("<<counterPert<<" tweets) are pertinent, meaning they contain one or more of the user-defined keywords." << endl;
  cout << "Of the pertinent tweets, " << percentNegpert << "% ("<<counterNeg<<" tweets) are evaluated to be negative about the topic." <<endl;

  return 0;
}
