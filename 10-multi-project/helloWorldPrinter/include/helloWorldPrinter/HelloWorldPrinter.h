#ifndef __HELLO_WORLD_PRINTER_H__
#define __HELLO_WORLD_PRINTER_H__

#include <iostream>

class HelloWorldPrinter
{
public:
    void sayHello()
    {
        std::cout << "Hello world from  HelloWorldPrinter static headers only lib!" << std::endl;
    }
};

#endif
