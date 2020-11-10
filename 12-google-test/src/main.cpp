#include <iostream>
#include "include/Reverse.h"
int main(int argc, char *argv[])
{
   Reverse r;
   std::string toRev = "Hello Google test!";
   std::cout << r.reverse(toRev) << std::endl;
   return 0;
}