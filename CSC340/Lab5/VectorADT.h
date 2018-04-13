#ifndef LAB5_VECTORADT_H
#define LAB5_VECTORADT_H


#include <cstddef>
#include <utility>
#include <ostream>
#include <cstring>

template<typename T>
class VectorADTTemplate
{
    // ==CONSTANTS==
    static constexpr T DEFAULT_VAL = 0; // TODO: find out how this shit works for non-numeric types
    static const size_t DEFAULT_CAPACITY = 10;

    // ==DATA==
private:
    T* array = nullptr;
    size_t size;      //the number of doubles stored in array
    size_t capacity;  //the maximum number of doubles that can be stored in array

    // ==METHODS==
private:
    void change_capacity(size_t new_capacity);
    void clone(const VectorADTTemplate<T>& other);
public:
    explicit VectorADTTemplate(size_t capacity = DEFAULT_CAPACITY);
    VectorADTTemplate(const VectorADTTemplate<T>& other);
    void resize(size_t new_size);
    void push_back(const T& val);
    void pop_back();
    void assign(size_t n, const T& val); // TODO: && version
    T operator[](size_t i);
    VectorADTTemplate& operator=(const VectorADTTemplate& other);
    VectorADTTemplate<T> operator+(const VectorADTTemplate<T>& rhs);
    size_t length() const;
    size_t curr_capacity() const;

    // ==FRIEND FUNCTIONS==
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const VectorADTTemplate<U>& vec);
};

//using VectorADT = VectorADTTemplate<double>;
typedef VectorADTTemplate<double> VectorADT;

template<typename T>
void VectorADTTemplate<T>::change_capacity(const size_t new_capacity)
{
    T* const new_array = new T[new_capacity];
    if(array)
    {
        size_t count = new_capacity < size ? new_capacity : size;
        for(size_t i = 0; i < new_capacity && i < size; ++i)
            new_array[i] = std::move(array[i]);
        //std::memmove(new_array, array, count * sizeof(VectorADTTemplate<T>)); // UNTESTED
        delete array;
    }
    array = new_array;
    capacity = new_capacity;
}

template<typename T>
void VectorADTTemplate<T>::clone(const VectorADTTemplate<T>& other)
{
    if(array)
        delete array;
    capacity = other.capacity;
    size = other.size;
    array = new T[capacity];
    std::memmove(array, other.array, size * sizeof(*array));
}

template<typename T>
VectorADTTemplate<T>::VectorADTTemplate(const size_t capacity)
{
    size = 0;
    change_capacity(capacity);
}

template<typename T>
VectorADTTemplate<T>::VectorADTTemplate(const VectorADTTemplate& other)
{
    clone(other);
}

template<typename T>
void VectorADTTemplate<T>::resize(const size_t new_size)
{
    if(new_size > size)
    {
        if(new_size > capacity)
            change_capacity(new_size<<1); // TODO: check for overflow
        for(size_t i = size; i < new_size; ++i)
            array[i] = DEFAULT_VAL;
    }

    size = new_size;
}

template<typename T>
void VectorADTTemplate<T>::push_back(const T& val)
{
    ++size;
    if(size > capacity)
        change_capacity(size<<1);
    array[size-1] = val;
}

template<typename T>
void VectorADTTemplate<T>::pop_back()
{
    --size;
    array[size] = DEFAULT_VAL; // Is there a better way to make sure the old object is destroyed?
}

template<typename T>
void VectorADTTemplate<T>::assign(const size_t n, const T& val)
{
    resize(n);
    for(size_t i = 0; i < n; ++i)
        array[i] = val;
}

template<typename T>
T VectorADTTemplate<T>::operator[](const size_t i)
{
    return array[i];
}

template<typename T>
VectorADTTemplate<T>& VectorADTTemplate<T>::operator=(const VectorADTTemplate<T>& other)
{
    clone(other);
    return *this;
}

template<typename T>
VectorADTTemplate<T> VectorADTTemplate<T>::operator+(const VectorADTTemplate<T>& rhs)
{
    if(size == rhs.size)
    {
        VectorADTTemplate<T> sum(size);
        for(size_t i = 0; i < size; ++i)
            sum.array[i] = array[i] + rhs.array[i];
        return sum;
    }
    else
    {
        VectorADTTemplate<T> empty;
        return empty;
    }
}

template<typename T>
size_t VectorADTTemplate<T>::length() const
{
    return size;
}

template<typename T>
size_t VectorADTTemplate<T>::curr_capacity() const
{
    return capacity;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const VectorADTTemplate<U>& vec)
{
    if(vec.size)
    {
        os << vec.array[0];
        for(size_t i = 1; i < vec.size; ++i)
            os << ", " << vec.array[i];
    }
    return os;
}


#endif //LAB5_VECTORADT_H
