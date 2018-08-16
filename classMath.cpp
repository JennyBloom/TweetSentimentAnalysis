/*
classMath.cpp
Author: Jenny Bloom and Jeff Nicholson
12.6.2015

References:
http://www.cplusplus.com/doc/tutorial/basic_io/
https://www.daniweb.com/programming/software-development/threads/90228/flushing-the-input-stream
https://en.wikipedia.org/wiki/Data_buffer
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include "classmath.h"

using namespace std;

// Constructors
classMath::classMath() //default constructor
{
  _total = 0;
  _perts = 0;
  _negs = 0;
}

classMath::classMath(double cp, double cn, double ttl) //overloaded constructors. doubles for floating point math
{
  _total = ttl;
  _perts = cp;
  _negs = cn;
}

//METHODS
double classMath::mathPert()
{
  //TODO: Processor is not counting properly - See TW.CPP
  double score = (_perts/_total)*100;
  return score;
}

double classMath::mathNegpert()
{
  double score = (_negs/_perts)*100;
  return score;
}
