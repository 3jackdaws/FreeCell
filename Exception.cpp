#include "Exception.h"

/**********************************************************************
* Purpose: Default ctor for Exception.
*
* Precondition:
*     none
*
* Postcondition:
*      sets m_message to Default Exception
*
************************************************************************/
Exception::Exception()
{
    m_message = new char[18];
    strcpy(m_message, "Default Exception");
}

/**********************************************************************
* Purpose: 1 arg ctor for exception.
*
* Precondition:
*     none
*
* Postcondition:
*      sets m_message to
*
************************************************************************/
Exception::Exception(const char * msg)
{
    m_message = new char[strlen(msg)+1];
    strcpy(m_message, msg);
}

/**********************************************************************
* Purpose: copy ctor for exception.
*
* Precondition:
*     cp must be object
*
* Postcondition:
*      exception object is instantiated with the values of cp
*
************************************************************************/
Exception::Exception(const Exception & cp)
{
    m_message = new char[strlen(cp.m_message)+1];
    strcpy(m_message, cp.m_message);
}

/**********************************************************************
* Purpose: Dtor for exception.
*
* Precondition:
*     object, pls
*
* Postcondition:
*      deletes the old message
*
************************************************************************/
Exception::~Exception()
{
    delete[] m_message;
}

/**********************************************************************
* Purpose: op = for exception.
*
* Precondition:
*     both objects must exist
*
* Postcondition:
*      object now has same values as rhs
*
************************************************************************/
Exception & Exception::operator = (const Exception & rhs)
{
    if(this != &rhs)
    {
        delete [] m_message;
        m_message = new char[strlen(rhs.m_message)+1];
        strcpy(m_message, rhs.m_message);
    }
    return *this;
}

/**********************************************************************
* Purpose: getter for m_message.
*
* Precondition:
*     m_message must be a thing
*
* Postcondition:
*      returns m_message
*
************************************************************************/
const char * Exception::getMessage()
{
    return m_message;
}


/**********************************************************************
* Purpose: setter for m_message.
*
* Precondition:
*     object must be instantiated
*
* Postcondition:
*      sets m_message to msg
************************************************************************/
void Exception::setMessage(const char * msg)
{
    delete [] m_message;
    m_message = new char[strlen(msg)+1];
    strcpy(m_message, msg);
}

/**********************************************************************
* Purpose: op << overload for ostream.
*
* Precondition:
*     none
*
* Postcondition:
*      pushes m_message to ostream object
*
************************************************************************/
std::ostream & operator << (std::ostream & stream, const Exception & except)
{
    stream << except.m_message;
    return stream;
}