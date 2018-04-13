#include "VectorADT.h"
#include "ListADT.h"
#include <iostream>

int main()
{
    VectorADT v1;
    v1.push_back(12);
    v1.push_back(11111);
    VectorADT v2 = v1;
    v2.push_back(23);
    v2.push_back(11);
    auto v3(v2);
    v3.pop_back();
    std::cout << v1 << "\n" << v2 << "\n" << v3 << "\n" << std::endl;

    ListADT l1;
    l1.push_back(12);
    l1.push_back(11111);
    ListADT l2 = l1;
    l2.push_back(23);
    l2.push_back(11);
    auto l3 = l2;
    l3.pop_front();
    std::cout << l1 << "\n" << l2 << "\n" << l3 << "\n" << std::endl;

    ListADT list;

    return 0;
}