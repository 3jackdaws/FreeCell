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