#include "randomGenerator/RandomGenerator.h"
#include <iostream>


RandomGenerator::RandomGenerator(double lowerBound, double upperBound):mt(rd()), dist(lowerBound, upperBound){
  std::cout << rd() << std::endl;
}

double RandomGenerator::next(){
  return this->dist(this->mt);
}
