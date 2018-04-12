#include "dynamicArray.h"

#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <new>
#include <iostream>

static constexpr size_t MAX_SIZE = static_cast<size_t>( std::sqrt(std::numeric_limits<int>::max()) ); // NOLINT

int* array_constructor(int*& intPtr, const size_t& size)
{
    intPtr = nullptr;
    if(size <= MAX_SIZE && size > 0)
    {
        try
        {
            intPtr = new int[size];
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            return nullptr;
        }
        initializeArray(intPtr, 0, size);
    }

    return intPtr;
}

int* array_resize(int*& intPtr, const size_t& currSize, const size_t& newSize)
{
    if(newSize == currSize || newSize < 1)
        return intPtr;

    int* newIntPtr;

    try
    {
        newIntPtr = new int[newSize];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        return intPtr;
    }

    if(newSize < currSize)
        for(size_t i = 0; i < newSize; ++i)
            newIntPtr[i] = intPtr[i];
    else
    {
        for(size_t i = 0; i < currSize; ++i)
            newIntPtr[i] = intPtr[i];
        initializeArray(newIntPtr, currSize, newSize);
    }

    if(currSize > 0)
        array_destructor(intPtr);

    intPtr = newIntPtr;
    return newIntPtr;
}

void initializeArray(int*& intPtr, const size_t begin, const size_t end)
{
    for(size_t i = begin; i < end; ++i)
        intPtr[i] = static_cast<int>(i * i);
}

void array_destructor(int*& intPtr)
{
    delete[] intPtr;
    intPtr = nullptr;
}

void array_set(int*& intPtr, const size_t& size)
{
    static bool unseeded = true;
    if(unseeded)
    {
        std::srand(static_cast<unsigned int>(time(nullptr)));
        unseeded = false;
    }

    for(size_t i = 0; i < size; ++i)
        intPtr[i] = std::rand(); // NOLINT
}

void mysort(int*& intPtr, const size_t size, Comparator* const comp)
{
    for(size_t i = 1; i < size; ++i)
    {
        int key = intPtr[i];
        size_t j;
        for(j = i; j > 0 && (*comp)(key, intPtr[j-1]); --j)
            intPtr[j] = intPtr[j-1];
        intPtr[j] = key;
    }
}

bool my_less_equal(const int& x, const int& y) { return x <= y; }
bool my_greater_equal(const int& x, const int& y) { return x >= y; }



















