#ifndef LAB3_DYNAMICARRAY_H
#define LAB3_DYNAMICARRAY_H

#include <cstddef>

typedef bool Comparator(const int&, const int&);

int* array_constructor(int*& intPtr, const size_t& size);
int* array_resize(int*& intPtr, const size_t& currSize, const size_t& newSize);
void initializeArray(int*& intPtr, size_t begin, size_t end);
void array_destructor(int*& intPtr);
void array_set(int*& intPtr, const size_t& size);
void mysort(int*& intPtr, size_t size, Comparator* comp);
bool my_less_equal(const int& x, const int& y);
bool my_greater_equal(const int& x, const int& y );

#endif //LAB3_DYNAMICARRAY_H
