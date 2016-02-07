#ifndef ARRAY_H
#define ARRAY_H
#include "Exception.h"
template <typename T>
class Array
{
	T * m_array;
	int m_length;
	int m_start_index;
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array & copy);

	~Array();

	Array<T> & operator = (const Array & rhs);
	T & operator [] (int index);
	int getStartIndex();
	void setStartIndex(int index);
	int getLength();
	void setLength(int len);
};

template <typename T>
Array<T>::Array() :m_array(nullptr), m_length(0), m_start_index(0)
{
	
}

template <typename T>
Array<T>::Array(int length, int start_index) : m_length(length), m_start_index(start_index)
{
    if(length < 0)
        throw Exception("NegativeLengthException");
    if(length>0)
        m_array = new T[length];
    else{
        m_array = nullptr;
    }
}

template <typename T>
Array<T>::Array(const Array<T> & cp): m_length(cp.m_length), m_start_index(cp.m_start_index)
{
    if(m_length>0)
    {
        m_array = new T[m_length];
        for (int i = 0; i < m_length; i++)
        {
            m_array[i] = cp.m_array[i];
        }
    }
    else
        m_array = nullptr;
}

template <typename T>
Array<T>::~Array()
{
    delete[] m_array;
    m_array = nullptr;
}

template <typename T>
Array<T> & Array<T>::operator = (const Array<T> & rhs)
{
    if(this != &rhs)
    {
        delete[] m_array;
        m_array = nullptr;
        this->m_length = rhs.m_length;
        this->m_start_index = rhs.m_start_index;
        
        m_array = new T[m_length];
        for (int i = 0; i < m_length; i++)
        {
            m_array[i] = rhs.m_array[i];
        }
    }
    
	
    return *this;
}

template <typename T>
T & Array<T>::operator [] (int index)
{
	if (index >= m_start_index + m_length || index < m_start_index)
	{
        throw Exception("OutOfBoundsException");
	}
	return m_array[index - m_start_index];
}

template <typename T>
int Array<T>::getStartIndex()
{
	return m_start_index;
}

template <typename T>
void Array<T>::setStartIndex(int index)
{
	m_start_index = index;
}

template <typename T>
int Array<T>::getLength()
{
	return m_length;
}

template <typename T>
void Array<T>::setLength(int new_len)
{
    if(new_len < 0)
        throw Exception("NegativeLengthException");
    T * hold = new T[new_len];
    int smallest = 0;
    m_length < new_len ? smallest = m_length : smallest = new_len;
    for (int i = 0; i < smallest; i++)
    {
        hold[i] = m_array[i];
    }
    delete[] m_array;
    m_array = nullptr;
    m_array = hold;
	m_length = new_len;
}

#endif