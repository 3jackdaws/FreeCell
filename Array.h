/*************************************************************
* Author:		Ian Murphy
* Filename:		Array.h
* Date Created:	1/18/2016
* Modifications:	1/18/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: Array
*
* Purpose: This class creates a dynamic one-dimensional array that can be started at any base.
*
* Manager functions:
* 	Array ( )
* 		The default size is zero and the base is zero.
*	Array (int length, int start_index = 0)
*		Creates an appropriate sized array with the starting index
*              either zero or the supplied starting value.
*	Array (const Array & copy)
*	operator = (const Array & copy)
*	~Array()
*
* Methods:
*	operator [ ] (int index)
makes the class behave like a normal array
getStartIndex()
returns an int, obvious function
setStartIndex()
I shouldn't have to say what this does
getLength()
returns the length of the array
setLength()
use this to make the array bigger
*		...
*************************************************************************/
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

/**********************************************************************
* Purpose: This is a default ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      sets up an array object so that it isn't filled with garbage
*
************************************************************************/
template <typename T>
Array<T>::Array() :m_array(nullptr), m_length(0), m_start_index(0)
{
	
}

/**********************************************************************
* Purpose: Allows several data members to be set upon instantiation. WOW!
*
* Precondition:
*     none
*
* Postcondition:
*      sets up an array object to the inout specifications
*
************************************************************************/
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

/**********************************************************************
* Purpose: constructs an array object from another array object
*
* Precondition:
*     cp should prolly be an Array object
*
* Postcondition:
*      There is now an identical array object to the one passed in
*
************************************************************************/
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

/**********************************************************************
* Purpose: This looks like a destructor.
*
* Precondition:
*     Needs to be within valid object
*
* Postcondition:
*      deletes all newed memory
*
************************************************************************/
template <typename T>
Array<T>::~Array()
{
    delete[] m_array;
    m_array = nullptr;
}

/**********************************************************************
* Purpose: Sets an already instantiated object to the values of another similar object.
*
* Precondition:
*     Needs two instantiated objects
*
* Postcondition:
*      the object on the left side of the = operator is now the same as the object on the right side
*
************************************************************************/
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

/**********************************************************************
* Purpose: Allows the Array class to behave like a normal array
*
* Precondition:
*     Array size prolly needs to be a real non-negative integer
*
* Postcondition:
*      Returns the data at that location in the array
*
************************************************************************/
template <typename T>
T & Array<T>::operator [] (int index)
{
	if (index >= m_start_index + m_length || index < m_start_index)
	{
        throw Exception("OutOfBoundsException");
	}
	return m_array[index - m_start_index];
}

/**********************************************************************
* Purpose: Gets start index
*
* Precondition:
*     An object must be instantiated
*
* Postcondition:
*     I'm not sure, but it looks like it returns m_start_index;
*
************************************************************************/
template <typename T>
int Array<T>::getStartIndex()
{
	return m_start_index;
}

/**********************************************************************
* Purpose: sets start index
*
* Precondition:
*     An object must be instantiated
*
* Postcondition:
*     Sets m_start_index to the method's input
*
************************************************************************/
template <typename T>
void Array<T>::setStartIndex(int index)
{
	m_start_index = index;
}

/**********************************************************************
* Purpose: Gets length of array
* Precondition:
*     An object must be instantiated
*
* Postcondition:
*     it returns m_length;
*
************************************************************************/
template <typename T>
int Array<T>::getLength()
{
	return m_length;
}

/**********************************************************************
* Purpose: sets a new length
*
* Precondition:
*     An object must be instantiated
*
* Postcondition:
*     old array is deleted but replaced with a new array of length new_len with all the old data
*
************************************************************************/
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