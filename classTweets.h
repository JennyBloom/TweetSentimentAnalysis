#ifndef CLASSTWEETS_H
#define CLASSTWEETS_H

class tweets
{
  public:
    tweets();
    int parseTweet(std::string currentTweet, std::string currentKeyword);
    int analyzeTweet(std::string currentTweet);

  private:
    std::vector<std::string> _dictionary;
};

#endif
