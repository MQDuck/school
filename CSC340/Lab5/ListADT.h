#ifndef LAB5_LISTADT_H
#define LAB5_LISTADT_H

#include <cstddef>
#include <ostream>

template<typename T>
class ListADTTemplate
{
    // ==CONSTANTS==
private:

    // ==TYPES==
private:
    struct Node
    {
        T value;
        Node* next;
        Node() : next(nullptr) {}
        Node(const T& value, Node* const next = nullptr) : value(value), next(next) {}
    };

    // ==DATA==
private:
    Node head;
    Node* backPtr = &head;
    size_t size = 0;

    // ==METHODS==
private:
    Node* seek(const size_t index) const;
    void clone(const ListADTTemplate<T>& other);

public:
    ListADTTemplate() = default;
    ListADTTemplate(ListADTTemplate<T>& other) { clone(other); };
    void push_back(const T& value);
    void push_front(const T& value);
    size_t length() const { return size; }
    void pop_back();
    void pop_front();
    void clear();
    void operator=(ListADTTemplate<T>& other) { clone(other); };
    T operator[](const size_t index) const;

    // ==FRIEND FUNCTIONS==

public:
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, ListADTTemplate<U>& list);
};

typedef ListADTTemplate<int> ListADT;

// ==Private Method Definitions==

template<typename T>
typename ListADTTemplate<T>::Node* ListADTTemplate<T>::seek(const size_t index) const
{
    Node* nodePtr = head.next;
    for(size_t i = 0; i < index; ++i)
        nodePtr = nodePtr->next;
    return nodePtr;
}

template<typename T>
void ListADTTemplate<T>::clone(const ListADTTemplate<T>& other)
{
    clear();
    for(Node* nodePtr = other.head.next; nodePtr; nodePtr = nodePtr->next)
        push_back(nodePtr->value);
}

// ==Public Method Definitions==

template<typename T>
void ListADTTemplate<T>::push_back(const T& value)
{
    backPtr->next = new Node(value);
    backPtr = backPtr->next;
    ++size;
}

template<typename T>
void ListADTTemplate<T>::push_front(const T& value)
{
    if(backPtr == &head)
        return push_back(value);
    Node* nodePtr = head.next;
    head.next = new Node(value, nodePtr);
    ++size;
}

template<typename T>
void ListADTTemplate<T>::pop_back()
{
    if(size == 0)
        return;

    Node* nodePtr;
    if(size == 1)
        nodePtr = &head;
    else
        nodePtr = seek(size-2);

    delete nodePtr->next;
    nodePtr->next = nullptr;
}

template<typename T>
void ListADTTemplate<T>::pop_front()
{
    if(head.next)
    {
        Node* nodePtr = head.next;
        head.next = nodePtr->next;
        delete nodePtr;
    }
}

template<typename T>
void ListADTTemplate<T>::clear()
{
    Node* np1 = head.next;
    Node* np2;
    while(np1)
    {
        np2 = np1;
        np1 = np1->next;
        delete np2;
    }
}

template<typename T>
T ListADTTemplate<T>::operator[](const size_t index) const
{
    // TODO: check bounds
    return seek(index)->value;
}

// ==Friend Functions==

template<typename U>
std::ostream& operator<<(std::ostream& os, ListADTTemplate<U>& list)
{
    typename ListADTTemplate<U>::Node* nodePtr = list.head.next;
    if(nodePtr)
    {
        os << nodePtr->value;
        for(nodePtr = nodePtr->next; nodePtr; nodePtr = nodePtr->next)
            os << "," << nodePtr->value;
    }
    return os;
}


#endif //LAB5_LISTADT_H
