#include "Exception.h"


Exception::Exception()
{
    m_message = new char[18];
    strcpy(m_message, "Default Exception");
}
Exception::Exception(const char * msg)
{
    m_message = new char[strlen(msg)+1];
    strcpy(m_message, msg);
}
Exception::Exception(const Exception & cp)
{
    m_message = new char[strlen(cp.m_message)+1];
    strcpy(m_message, cp.m_message);
}

Exception::~Exception()
{
    delete[] m_message;
}

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
const char * Exception::getMessage()
{
    return m_message;
}
void Exception::setMessage(const char * msg)
{
    delete [] m_message;
    m_message = new char[strlen(msg)+1];
    strcpy(m_message, msg);
}

std::ostream & operator << (std::ostream & stream, const Exception & except)
{
    stream << except.m_message;
    return stream;
}