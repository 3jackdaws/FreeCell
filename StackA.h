//
//  StackA.h
//  StackA Array
//
//  Created by Ian Murphy on 1/29/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef StackA_h
#define StackA_h
#include "Array.h"


template <typename T>
class StackA
{
public:
    StackA();
    StackA(int size);
    StackA(const StackA & cp);
    ~StackA();
    StackA & operator = (const StackA & rhs);
    
    void Push(T);
    T Pop();
    T& Peek();
    int Size();
    bool isFull();
    bool isEmpty();
    
    void Resize(int size);
private:
    Array<T> m_array;
    int m_capacity;
    //int m_size;
    int m_position;
};

template <typename T>
StackA<T>::StackA() : m_array(0), m_capacity(0), m_position(0)
{
    
}

template <typename T>
StackA<T>::StackA(int size) : m_array(size), m_capacity(size), m_position(0)
{
    
}

template <typename T>
StackA<T>::StackA(const StackA<T> & cp) : m_array(cp.m_array), m_capacity(cp.m_capacity), m_position(cp.m_position)
{   }

template <typename T>
StackA<T>::~StackA()
{   }

template <typename T>
StackA<T> & StackA<T>::operator=(const StackA<T> &rhs)
{
    if(this != &rhs)
    {
        m_array = rhs.m_array;
        m_position = rhs.m_position;
        m_capacity = rhs.m_capacity;
    }
    return *this;
}

template <typename T>
void StackA<T>::Push(T data)
{
    if(m_position == m_capacity)
        throw Exception("Overflow Exception");
    m_array[m_position++] = data;
}

template <typename T>
T StackA<T>::Pop()
{
    if(m_position <= 0)
        throw Exception("Underflow Exception");
    return m_array[--m_position];
}

template <typename T>
T & StackA<T>::Peek()
{
    if(m_position <= 0)
        throw Exception("Peek at Empty StackA Exception");
    return m_array[m_position-1];
}

template <typename T>
int StackA<T>::Size()
{
    return m_position;
}

template <typename T>
bool StackA<T>::isEmpty()
{
    return m_position == 0;
}
template <typename T>
bool StackA<T>::isFull()
{
    return m_position == m_capacity;
}

template <typename T>
void StackA<T>::Resize(int size)
{
    m_array.setLength(size);
    m_capacity = size;
}
#endif /* StackA_h */
