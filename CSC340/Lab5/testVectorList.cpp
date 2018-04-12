#include "VectorADT.h"
#include <iostream>

int main()
{
    VectorADT foo;
    foo.push_back(12);
    foo.push_back(11111);
    foo.resize(100);
    std::cout << foo << std::endl;
    return 0;
}