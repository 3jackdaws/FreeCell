/*************************************************************
* Author:		Ian Murphy
* Filename:		DisplayManager.hpp
* Date Created:	2/4/2016
* Modifications:	2/10/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: DisplayManager
*
* Purpose: This class manages console output by providing methods to draw shapes and text to a console buffer.

	///////////////      TODO: Convert to a singleton pattern.  There should only ever be one of these. ////////////
*
* Manager functions:
* 	DisplayManager();
		Instantiates the class and sets up the required helper datamembers
	DisplayManager(const DisplayManager & cp);
		DON'T USE THIS.  THIS WILL THROW AN EXCEPTION
		The DisplayManager Class chould never be copied.
	~DisplayManager();
	DisplayManager & operator = (const DisplayManager & rhs);
		Similar to the copy c'tor, this does not function.  It will return a reference to the current object.
*
* Methods:
*	void Display();
		Writes the diplaybuffer to the active console window.
		Call this to update the display and show changes made
	void Fill(const wchar_t * fill);
		Fills the display buffer with one character.  Useful to clear the buffer.
	void Rect(int startrow, int startcol, int rowsize, int colsize, const wchar_t * fill);
		Draws a rectangle to the buffer.
	void ColorBackground(int startrow, int startcol, int height, int width, int color);
		Colors the foreground or background of a rectangular area.  A line is technically a rectangle with width or height of 1
	void Write(int, int, const wchar_t * fill);
		Writes a single character to the display Buffer
	void Text(int startrow, int startcol, int max, const char string[]);
		Writes specified text to the display buffer up to max size
	void Line(int startrow, int startcol, int length, const wchar_t * fill);
		Draws a horizontal line
	void VertLine(int startrow, int startcol, int length, const wchar_t * fill);
		Draws a vertical line
*		...
*************************************************************************/

#ifndef DisplayManager_hpp
#define DisplayManager_hpp

#include <iostream>
#include "GameBoard.hpp"
#include <chrono>
using timepoint = std::chrono::high_resolution_clock::time_point;
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
const int BUFFER_WIDTH = 100;
const int BUFFER_HEIGHT= 60;

struct coords{
    int row;
    int col;
};
class DisplayManager
{
public:
	DisplayManager();
	DisplayManager(const DisplayManager & cp);
	~DisplayManager();
	DisplayManager & operator = (const DisplayManager & rhs);

	void Display();
	void Fill(const wchar_t * fill);
	void Rect(int startrow, int startcol, int rowsize, int colsize, const wchar_t * fill);
	void ColorBackground(int startrow, int startcol, int height, int width, int color);
	void Write(int, int, const wchar_t * fill);
	void Text(int startrow, int startcol, int max, const char string[]);
	void Line(int startrow, int startcol, int length, const wchar_t * fill);
	void VertLine(int startrow, int startcol, int length, const wchar_t * fill);
	
	
private:
	//char _console_buffer[BUFFER_HEIGHT][BUFFER_WIDTH + 1];		//legacy
	HANDLE _main_buffer;										//handle to active console window
	HANDLE _secondary_buffer;									//holdover from when this did double buffering
	CHAR_INFO _char_info[BUFFER_HEIGHT*BUFFER_WIDTH];			//actual display buffer data structure
	SMALL_RECT mainRect;										//required for some reason
	SMALL_RECT secRect;											//same ^
	COORD coordBufSize;											//this does something
	COORD coordBufCoord;
};

#endif /* DisplayManager_hpp */
