/*************************************************************
* Author:		Ian Murphy
* Filename:		DisplayManager.cpp
* Date Created:	2/4/16
* Modifications:	2/10/16 - Added documentation
*
**************************************************************/

#include "DisplayManager.hpp"

/**********************************************************************
* Purpose: This is the default ctor for the displaymanager class
*
* Precondition:
*     None
*
* Postcondition:
*      creates a charinfo array of appropriate length and initializes the required data members
*
************************************************************************/
DisplayManager::DisplayManager()
{
	mainRect.Top = 0;     
	mainRect.Left = 0;
	mainRect.Bottom = BUFFER_HEIGHT; 
	mainRect.Right = BUFFER_WIDTH;

	coordBufSize.Y = BUFFER_HEIGHT;
	coordBufSize.X = BUFFER_WIDTH;

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	secRect.Top = 0;    
	secRect.Left = 0;
	secRect.Bottom = BUFFER_HEIGHT; 
	secRect.Right = BUFFER_WIDTH;
	_main_buffer = GetStdHandle(STD_OUTPUT_HANDLE);
	_secondary_buffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved;

	ReadConsoleOutput(
	_main_buffer,        // screen buffer to read from 
	_char_info,      // buffer to copy into 
	coordBufSize,   // col-row size of chiBuffer 
	coordBufCoord,  // top left dest. cell in chiBuffer 
	&mainRect);
	/*for (int i = 0; i<BUFFER_HEIGHT; i++)
	{
		_console_buffer[i][BUFFER_WIDTH] = '\0';
	}*/
}

/**********************************************************************
* Purpose: This is a copy ctor.
*
* Precondition:
*     DON'T USE THIS
*
* Postcondition:
*		THIS WILL THROW AN EXCEPTION.  This should not be used.  When I can think of a 
		reason to ever copy an entire DisplayManager object, I will actually implement this contructor
*
************************************************************************/
DisplayManager::DisplayManager(const DisplayManager & cp)
{
	throw Exception("Don't copy a DisplayManager object, there should only be one");
}

/**********************************************************************
* Purpose: This is a destructor.
*
* Precondition:
*     None
*
* Postcondition:
*      destructs the object
*
************************************************************************/
DisplayManager::~DisplayManager()
{
    
}

/**********************************************************************
* Purpose: This is a op = overload.
*
* Precondition:
*     THIS DOESN'T DO ANYTHING
*
* Postcondition:
*		THIS WILL NOT THROW AN EXCEPTION, but should not be used.  When I can think of a
reason to ever copy an entire DisplayManager object, I will actually implement this op = overload
*
************************************************************************/
DisplayManager & DisplayManager::operator = (const DisplayManager & rhs)
{
    return *this;
}

/**********************************************************************
* Purpose: This is called to display what is currently in the CHAR_INFO buffer
*
* Precondition:
*     Nothing in particular, but output is only meaningful when the consumer has been writing to the diaply buffer
*
* Postcondition:
*		This will display the contents of the _char_infor buffer to the Windows console 
*
************************************************************************/
void DisplayManager::Display()
{
	WriteConsoleOutput(
		_main_buffer, // screen buffer to write to 
		_char_info,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&secRect);
}

/**********************************************************************
* Purpose: Fills the entire console buffer with one char
*
* Precondition:
*     none
*
* Postcondition:
*		the console buffer will be completely filled with the provided char
*
************************************************************************/
void DisplayManager::Fill(const wchar_t * fill)
{
    for (int row = 0; row < BUFFER_HEIGHT; row++)
    {
        for (int col = 0; col<BUFFER_WIDTH; col++)
        {
            //_console_buffer[row][col] = c;	//legacy code
			_char_info[row*BUFFER_WIDTH + col].Char.UnicodeChar = *fill;
        }
    }
    
}

/**********************************************************************
* Purpose: Writes one char to the console buffer at the provided location
*
* Precondition:
*     none
*
* Postcondition:
*		the one provided char is put to the display buffer 
*
************************************************************************/
void DisplayManager::Write(int row, int col, const wchar_t * fill)
{
	if (row >= BUFFER_HEIGHT || row < 0 || col >= BUFFER_WIDTH || col < 0);
		//throw Exception("Buffer out of bounds");		//it used to do bounds checking, now it doesn't
	else
		_char_info[row*BUFFER_WIDTH + col].Char.UnicodeChar = *fill;
		
}

/**********************************************************************
* Purpose: Draws a rectangle in the display buffer of specified size and fill
*
* Precondition:
*     none
*
* Postcondition:
*		the console buffer will contain a rectangle described by the input parameters

		IF THE INPUT IS NOT VALID, THE METHOD WILL WRITE UP TO THE INVALID BOUNDS.
		For example, if a rectangle is to be drawn that escapes the bounds of the display buffer, the portion that
		is outside the bounds will not be drawn.  This is not undefined behavior, I just defined it.
*
************************************************************************/
void DisplayManager::Rect(int startrow, int startcol, int width, int height, const wchar_t * fill)
{
	/*if (startrow+height >= BUFFER_HEIGHT || startrow < 0 || startcol+width >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");*/
    for (int row = startrow; row < height+startrow && row < BUFFER_HEIGHT; row++)
    {
        for (int col = startcol; col<startcol+width && col<BUFFER_WIDTH; col++)
        {
			_char_info[row*BUFFER_WIDTH + col].Char.UnicodeChar = *fill;
        }
    }
}

/**********************************************************************
* Purpose: Colors the foreground and background of the display buffer 
*
* Precondition:
*     none
*
* Postcondition:
*		the console buffer will color the foreground and background of the display buffer as described

IF THE INPUT IS NOT VALID, THE METHOD WILL WRITE UP TO THE INVALID BOUNDS.
For example, if a rectangle is to be drawn that escapes the bounds of the display buffer, the portion that
is outside the bounds will not be drawn.  This is not undefined behavior, I just defined it.
*
************************************************************************/
void DisplayManager::ColorBackground(int startrow, int startcol, int width, int height, int color)
{
	for (int row = startrow; row < height + startrow&& row < BUFFER_HEIGHT; row++)
	{
		for (int col = startcol; col < startcol + width && col<BUFFER_WIDTH; col++)
		{
			_char_info[row*BUFFER_WIDTH + col].Attributes = color;
		}
	}

}

/**********************************************************************
* Purpose: Draws text to the display buffer
*
* Precondition:
*     none
*
* Postcondition:
*		this method will draw the input string to the buffer up to the max size

IF THE INPUT IS NOT VALID, THE METHOD WILL WRITE UP TO THE INVALID BOUNDS.
For example, if a rectangle is to be drawn that escapes the bounds of the display buffer, the portion that
is outside the bounds will not be drawn.  This is not undefined behavior, I just defined it.
*
************************************************************************/
void DisplayManager::Text(int startrow, int startcol, int max, const char string[])
{
	/*if (startrow >= BUFFER_HEIGHT || startrow < 0 || startcol + max >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");*/
    for (int col = startcol, i = 0; col<startcol+max && i<strlen(string) && col < BUFFER_WIDTH; col++, i++)
    {
        //_console_buffer[startrow][col] = string[i];
		_char_info[startrow*BUFFER_WIDTH + col].Char.AsciiChar = string[i];
    }
}

/**********************************************************************
* Purpose: Draws a line to the display buffer
*
* Precondition:
*     none
*
* Postcondition:
*		this method will draw the requested line to the buffer

IF THE INPUT IS NOT VALID, THE METHOD WILL WRITE UP TO THE INVALID BOUNDS.
For example, if a rectangle is to be drawn that escapes the bounds of the display buffer, the portion that
is outside the bounds will not be drawn.  This is not undefined behavior, I just defined it.
*
************************************************************************/
void DisplayManager::Line(int startrow, int startcol, int length, const wchar_t * fill)
{
	/*if (startrow >= BUFFER_HEIGHT || startrow < 0 || startcol + length >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");*/
    for (int i = startcol; i<startcol+length&& i < BUFFER_WIDTH; i++)
    {
        //_console_buffer[startrow][i] = fill;
		_char_info[startrow*BUFFER_WIDTH + i].Char.UnicodeChar = *fill;
    }
    
}

void DisplayManager::VertLine(int startrow, int startcol, int length, const wchar_t * fill)
{
	/*if (startrow + length >= BUFFER_HEIGHT || startrow < 0 || startcol >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");*/
    for (int i = startrow; i<startrow+length+1 && i < BUFFER_HEIGHT; i++)
    {
       // _console_buffer[i][startcol] = fill;
		_char_info[i*BUFFER_WIDTH + startcol].Char.UnicodeChar = *fill;
    }
    
}

coords DisplayManager::ScanF(char * chars)
{
    bool found = false;
    for (int row = 0; row<BUFFER_WIDTH; row++)
    {
        for (int col = 0; col<BUFFER_HEIGHT; col++)
        {
            for (int i = 0; i<strlen(chars); i++)
            {
                if(_console_buffer[row][col] == chars[i])
                {
                    return coords{row,col};
                }
            }
        }
    }
    return coords{-1,-1};
}

