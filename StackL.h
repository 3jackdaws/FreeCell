//
//  StackL.h
//  StackL Array
//
//  Created by Ian Murphy on 1/29/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef StackL_h
#define StackL_h
#include "LinkedList.hpp"
#include "Exception.h"

template <typename T>
class StackL
{
public:
    StackL();
    StackL(const StackL & cp);
    ~StackL();
    StackL & operator = (const StackL & rhs);
    
    void Push(T);
    T Pop();
    const T& Peek();
    int Size();
    bool isEmpty();
    
private:
    DoubleLinkedList<T> m_list;
    int m_size;
};

template <typename T>
StackL<T>::StackL() : m_size(0)
{
    
}

template <typename T>
StackL<T>::StackL(const StackL<T> & cp) : m_list(cp.m_list), m_size(cp.m_size)
{   }

template <typename T>
StackL<T>::~StackL()
{   }

template <typename T>
StackL<T> & StackL<T>::operator=(const StackL<T> &rhs)
{
    if(this != &rhs)
    {
        m_list = rhs.m_list;
        m_size = rhs.m_size;
    }
    return *this;
}

template <typename T>
void StackL<T>::Push(T data)
{
    m_list.Prepend(data);
    m_size++;
}

template <typename T>
T StackL<T>::Pop()
{
    if(m_size <= 0)
        throw Exception("Underflow Exception");
    m_size--;
    T data = m_list.First();
    return m_list.Extract(data);
}

template <typename T>
const T & StackL<T>::Peek()
{
    if(m_size <= 0)
        throw Exception("Underflow Exception");
    return m_list.First();
}

template <typename T>
int StackL<T>::Size()
{
    return m_size;
}

template <typename T>
bool StackL<T>::isEmpty()
{
    return m_size == 0;
}

#endif /* StackL_h */
