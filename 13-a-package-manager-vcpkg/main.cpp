#include <iostream>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
   std::cout << sqlite3_libversion() << std::endl;
   return 0;
}
