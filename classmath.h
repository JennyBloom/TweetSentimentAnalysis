#ifndef CLASSMATH_H
#define CLASSMATH_H

class classMath
{
  public:
    classMath();
    classMath(double cp, double cn, double ttl); //cp: counter of pertinent tweets
    double mathPert(); //cn: counter of negative tweets
    double mathNegpert();
  private:
    double _total;
    double _perts;
    double _negs;
};

#endif
