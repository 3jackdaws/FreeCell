//
//  DoubleLinkedList.hpp
//  DoubleLL
//
//  Created by Ian Murphy on 1/6/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//


#ifndef DoubleLinkedList_hpp
#define DoubleLinkedList_hpp

#include <iostream>
#include "LLNode.hpp"

template <typename T>
class DoubleLinkedList
{
public:
    
    bool isEmpty();
    const T& First() const;
    const T& Last() const;
    void Prepend(T);
    void Append(T);
    void Purge();
    T Extract(T);
    void InsertAfter(const T & put, const T & find);
    void InsertBefore(const T & put, const T & find);
    void PrintForwards();
    void PrintBackwards();
    
    LLNode<T> * getHead();
    LLNode<T> * getTail();
    
    DoubleLinkedList();
    ~DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList<T> &);
    DoubleLinkedList<T> & operator = (const DoubleLinkedList<T> &);
    
    //data members
    
    LLNode<T> * _head;
    LLNode<T> * _tail;
    
private:
    LLNode<T> & Find(T);
    
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : _head(nullptr), _tail(nullptr)
{
    
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    Purge();
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T> & cp) : _head(nullptr), _tail(nullptr)
{
    LLNode<T> * travel = cp._head;
    while(travel != nullptr)
    {
        Append(travel->_data);
        travel = travel->_next;
    }
}

template <typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList<T> & rhs)
{
    if(this != &rhs)
    {
        Purge();
        LLNode<T> * travel = rhs._head;
        while(travel != nullptr)
        {
            Append(travel->_data);
            travel = travel->_next;
        }

    }
    return *this;
}

template <typename T>
bool DoubleLinkedList<T>::isEmpty()
{
    if(_head == nullptr)
        return true;
    return false;
}

template <typename T>
const T & DoubleLinkedList<T>::First() const
{
    if(!_head)
        throw "No first";
    else
        return _head->_data;
}

template <typename T>
const T & DoubleLinkedList<T>::Last() const
{
    if(!_tail)
        throw "No last";
    return _tail->_data;
}

template <typename T>
void DoubleLinkedList<T>::Prepend(T data)
{
    if(_head == nullptr)
    {
        _head = new LLNode<T>(data);
        _tail = _head;
    }
    else{
        LLNode<T> * old_head = _head;
        _head = new LLNode<T>(data);
        old_head->_prev = _head;
        _head->_next = old_head;
    }
    
}

template <typename T>
void DoubleLinkedList<T>::Append(T data)
{
    if(_tail != nullptr)
    {
        _tail->_next = new LLNode<T>(data);
        _tail->_next->_prev = _tail;
        _tail = _tail->_next;
    }
    else
    {
        Prepend(data);
    }
    
}

template <typename T>
void DoubleLinkedList<T>::Purge()
{
    if(_head != nullptr)
    {
        LLNode<T> * travel = _tail;
        while(travel->_prev != nullptr)
        {
            travel = travel->_prev;
            delete travel->_next;
            //travel->_next = nullptr;
        }
        delete travel;
        _head = nullptr;
        _tail = nullptr;

    }
}

template <typename T>
T DoubleLinkedList<T>::Extract(T data)
{
    
    LLNode<T> * travel = _head;
    while (travel != nullptr && travel->_data != data)
    {
        travel = travel->_next;
    }
    if(travel)
    {
        if(travel == _head)
        {
            _head = travel->_next;
//            _head->_prev = nullptr;
        }
        if(travel == _tail)
        {
            _tail = travel->_prev;
//            _tail->_next = nullptr;
        }
            
        else if(travel->_prev != nullptr){
            travel->_prev->_next = travel->_next;
            travel->_next->_prev = travel->_prev;
        }
        if(_head)
            _head->_prev = nullptr;
        if(_tail)
            _tail->_next = nullptr;
        delete travel;
    }
    else
        throw "Data not found within list";
    return data;
}


template <typename T>
void DoubleLinkedList<T>::InsertAfter(const T & put, const T & find)
{
    LLNode<T> * travel = _head;
    while (travel != nullptr && travel->_data != find)
    {
        travel = travel->_next;
    }
    if(travel)
    {
        if(travel == _tail)
        {
            Append(put);
        }
        else if(travel == _head)
        {
            LLNode<T> * nn = new LLNode<T>(put);
            nn->_prev = _head;
            nn->_next = _head->_next;
            
            _head->_next->_prev = nn;
            _head->_next = nn;
        }
        else
        {
            LLNode<T> * nn = new LLNode<T>(put);
            nn->_next = travel->_next;
            nn->_prev = travel;
            travel->_next->_prev = nn;
            travel->_next = nn;
        }
    }
    else
        throw "Data not found within list";
}

template <typename T>
void DoubleLinkedList<T>::InsertBefore(const T & put, const T & find)
{
    LLNode<T> * travel = _head;
    while (travel != nullptr && travel->_data != find)
    {
        travel = travel->_next;
    }
    if(travel)
    {
        
        
        if(travel == _head)
        {
            Prepend(put);
        }
        else if(travel == _tail)
        {
            LLNode<T> * nn = new LLNode<T>(put);
            nn->_next = _tail;
            nn->_prev = _tail->_prev;
            _tail->_prev->_next = nn;
            _tail->_prev = nn;
        }
        else
        {
            LLNode<T> * nn = new LLNode<T>(put);
            nn->_prev = travel->_prev;
            nn->_next = travel;
            travel->_prev->_next = nn;
            travel->_prev = nn;
        }
    }
    else
        throw "Data not found within list";
}


template <typename T>
void DoubleLinkedList<T>::PrintForwards()
{
    LLNode<T> * travel = _head;
    while (travel != nullptr)
    {
        std::cout<<travel->_data<<std::endl;
        travel = travel->_next;
    }
}

template <typename T>
void DoubleLinkedList<T>::PrintBackwards()
{
    LLNode<T> * travel = _tail;
    while (travel != nullptr) {
        std::cout<<travel->_data<<std::endl;
        travel = travel->_prev;
    }
}

template <typename T>
LLNode<T> * DoubleLinkedList<T>::getHead()
{
    return _head;
}

template <typename T>
LLNode<T> * DoubleLinkedList<T>::getTail()
{
    return _tail;
}
#endif /* DoubleLinkedList_hpp */
