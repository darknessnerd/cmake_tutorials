#include "randomGenerator/RandomGenerator.h"
#include "helloWorldPrinter/HelloWorldPrinter.h"
#include <iostream>
int main(int argc, char *argv[])
{
    RandomGenerator randomGenerator(2.0, 5.0);
    double number = randomGenerator.next();
    std::cout << "RandomGenerator result:"  << number << std::endl;
    number = randomGenerator.next();
    std::cout << "RandomGenerator result:"  << number << std::endl;
    number = randomGenerator.next();
    std::cout << "RandomGenerator result:"  << number << std::endl;
    number = randomGenerator.next();
    std::cout << "RandomGenerator result:"  << number << std::endl;
    
    HelloWorldPrinter helloWorldPrinter;
    helloWorldPrinter.sayHello();

    return 0;
}
