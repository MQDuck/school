#include <iostream>
#include "dynamicArray.h"

using namespace std; // I feel dirty.

void printArray(int*& intPtr, size_t size)
{
    std::cout << "arr1[" << size << "] = {";
    for(size_t i = 0; i < size-1; ++i)
        std::cout << intPtr[i] << ", ";
    std::cout << intPtr[size-1] << "}\n\n" << std::flush;
}

int main()
{
    int* intArr = nullptr;
    const size_t size1 = 20, size2 = 25, size3 = 10;

    struct myNumpunct : std::numpunct<char>
    {
        std::string do_grouping() const override { return "\03"; }
    };
    std::locale loc(std::cout.getloc(), new myNumpunct);
    std::cout.imbue(loc);

    array_constructor(intArr, size1);
    printArray(intArr, size1);

    std::cout << "resizing intArr to size " << size2 << "...\n";
    array_resize(intArr, size1, size2);
    printArray(intArr, size2);

    std::cout << "resizing intArr to size " << size3 << "...\n";
    array_resize(intArr, size2, size3);
    printArray(intArr, size3);

    std::cout << "randomizing intArr...\n";
    array_set(intArr, size3);
    printArray(intArr, size3);

    std::cout << "sorting intArr from smallest to largest...\n";
    mysort(intArr, size3, &my_less_equal);
    printArray(intArr, size3);

    std::cout << "randomizing intArr...\n";
    array_set(intArr, size3);
    printArray(intArr, size3);

    std::cout << "sorting intArr from largest to smallest...\n";
    mysort(intArr, size3, &my_greater_equal);
    printArray(intArr, size3);

    return 0;
}