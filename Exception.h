/************************************************************************
* Class: Exception
*
* Purpose: This class provides some type of bare bones framework for throwing exceptions.  Why is this not built into C++?
*
* Manager functions:
* 	Exception ( )
* 		sets the message to the default value: "Default Exception".
*	Exception (char * msg)
*		creates an exception object containing the message passed in msg
*
*	Exception (const Exception & copy)
copies an exception because it's a copy ctor
*	operator = (const Array & copy)
not sure why this would be used, but will set the values of one exception object to the values of another
*	~Array()
*
* Methods:
*	getMessage()
`		returns the message inside
setMessage(char * msg)
sets the internal message
op << overload for ostream object
allows easy outputting of Exception objects
*		...
*************************************************************************/
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
class Exception
{
	char * m_message;
public:
	
	Exception();
	Exception(const char * msg);
	Exception(const Exception & cp);

	~Exception();

	Exception & operator = (const Exception &);
	const char * getMessage();
	void setMessage(const char * msg);
	friend std::ostream & operator << (std::ostream & stream, const Exception & except);

};

#endif