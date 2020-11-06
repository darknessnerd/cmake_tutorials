#include <iostream>
#include "Hello.h"
#include "Version.h"



void Hello::print()
{
    std::cout << "Hello Headers!" << std::endl;
	std::cout << HELLOWORLD_VERSION << std::endl;
	std::cout << " Version " << HELLOWORLD_VERSION_MAJOR << "." << HELLOWORLD_VERSION_MINOR << std::endl;
}
