#ifndef __RANDOM_GENERATOR_H__
#define __RANDOM_GENERATOR_H__s

#include <random>
using namespace std;
class RandomGenerator
{
public:
    double next();
    RandomGenerator(double lowerBound, double upperBound);  // This is the constructor
private:
  random_device rd;
  mt19937 mt;
  uniform_real_distribution<double> dist;
};

#endif
