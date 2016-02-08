//
//  DisplayManager.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "DisplayManager.hpp"

DisplayManager::DisplayManager()
{
	

	mainRect.Top = 0;    // top left: row 0, col 0 
	mainRect.Left = 0;
	mainRect.Bottom = BUFFER_HEIGHT; // bot. right: row 1, col 79 
	mainRect.Right = BUFFER_WIDTH;

	coordBufSize.Y = BUFFER_HEIGHT;
	coordBufSize.X = BUFFER_WIDTH;

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	secRect.Top = 0;    // top lt: row 10, col 0 
	secRect.Left = 0;
	secRect.Bottom = BUFFER_HEIGHT; // bot. rt: row 11, col 79 
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
	for (int i = 0; i<BUFFER_HEIGHT; i++)
	{
		_console_buffer[i][BUFFER_WIDTH] = '\0';
	}
}

DisplayManager::DisplayManager(const DisplayManager & cp)
{
    VertLine(0, BUFFER_WIDTH, BUFFER_HEIGHT, '\0');
}
DisplayManager::~DisplayManager()
{
    
}
DisplayManager & DisplayManager::operator = (const DisplayManager & rhs)
{
    return *this;
}

void DisplayManager::Display()
{
	SetConsoleActiveScreenBuffer(_secondary_buffer);

	//for (int row = 0; row <BUFFER_HEIGHT; row++)
	//{
	//	std::cout << _console_buffer[row] << "\n";
	//	/*for (int i = 0; i < BUFFER_WIDTH; i++)
	//	{
	//	std::cout << _console_buffer[row][i];
	//	}
	//	std::cout << "\n";*/
	//}
	//std::cout << std::endl;

	

	//mainRect.Top = 0;    // top left: row 0, col 0 
	//mainRect.Left = 0;
	//mainRect.Bottom = BUFFER_HEIGHT; // bot. right: row 1, col 79 
	//mainRect.Right = BUFFER_WIDTH;

	//coordBufSize.Y = BUFFER_HEIGHT;
	//coordBufSize.X = BUFFER_WIDTH;

	//coordBufCoord.X = 0;
	//coordBufCoord.Y = 0;

	//ReadConsoleOutput(
	//	_main_buffer,        // screen buffer to read from 
	//	_char_info,      // buffer to copy into 
	//	coordBufSize,   // col-row size of chiBuffer 
	//	coordBufCoord,  // top left dest. cell in chiBuffer 
	//	&mainRect);

	//secRect.Top = 0;    // top lt: row 10, col 0 
	//secRect.Left = 0;
	//secRect.Bottom = BUFFER_HEIGHT; // bot. rt: row 11, col 79 
	//secRect.Right = BUFFER_WIDTH;

	WriteConsoleOutput(
		_main_buffer, // screen buffer to write to 
		_char_info,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&secRect);

	SetConsoleActiveScreenBuffer(_main_buffer);

	WriteConsoleOutput(
		_secondary_buffer, // screen buffer to write to 
		_char_info,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&secRect);
    
    
}

void DisplayManager::Fill(char c)
{
    for (int row = 0; row < BUFFER_HEIGHT; row++)
    {
        for (int col = 0; col<BUFFER_WIDTH; col++)
        {
            _console_buffer[row][col] = c;
			_char_info[row*BUFFER_WIDTH + col].Char.AsciiChar = c;
        }
    }
    
}


void DisplayManager::Write(int row, int col, char w)
{
	if (row >= BUFFER_HEIGHT || row < 0 || col >= BUFFER_WIDTH || col < 0)
		throw Exception("Buffer out of bounds");
    _console_buffer[row][col] = w;
	_char_info[row*BUFFER_WIDTH + col].Char.AsciiChar = w;
}

void DisplayManager::Rect(int startrow, int startcol, int width, int height, wchar_t fill)
{
	if (startrow+height >= BUFFER_HEIGHT || startrow < 0 || startcol+width >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");
    for (int row = startrow; row < height+startrow; row++)
    {
        for (int col = startcol; col<startcol+width; col++)
        {
            _console_buffer[row][col] = fill;
			_char_info[row*BUFFER_WIDTH + col].Char.AsciiChar = fill;
        }
    }
}

void DisplayManager::ColorBackground(int startrow, int startcol, int width, int height, int color)
{
	for (int row = startrow; row < height + startrow; row++)
	{
		for (int col = startcol; col < startcol + width; col++)
		{
			_char_info[row*BUFFER_WIDTH + col].Attributes = color;
		}
	}

}

void DisplayManager::Text(int startrow, int startcol, int max, const char string[])
{
	if (startrow >= BUFFER_HEIGHT || startrow < 0 || startcol + max >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");
    for (int col = startcol, i = 0; col<startcol+max && i<strlen(string); col++, i++)
    {
        _console_buffer[startrow][col] = string[i];
		_char_info[startrow*BUFFER_WIDTH + col].Char.AsciiChar = string[i];
    }
}

void DisplayManager::Line(int startrow, int startcol, int length, char fill)
{
	if (startrow >= BUFFER_HEIGHT || startrow < 0 || startcol + length >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");
    for (int i = startcol; i<startcol+length; i++)
    {
        _console_buffer[startrow][i] = fill;
		_char_info[startrow*BUFFER_WIDTH + i].Char.AsciiChar = fill;
    }
    
}

void DisplayManager::VertLine(int startrow, int startcol, int length, char fill)
{
	if (startrow + length >= BUFFER_HEIGHT || startrow < 0 || startcol >= BUFFER_WIDTH || startcol < 0)
		throw Exception("Buffer out of bounds");
    for (int i = startrow; i<startrow+length+1; i++)
    {
        _console_buffer[i][startcol] = fill;
		_char_info[i*BUFFER_WIDTH + startcol].Char.AsciiChar = fill;
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