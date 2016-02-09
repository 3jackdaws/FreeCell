//
//  DisplayManager.hpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef DisplayManager_hpp
#define DisplayManager_hpp

#include <iostream>
#include "GameBoard.hpp"
#include <chrono>
using timepoint = std::chrono::high_resolution_clock::time_point;
#include <Windows.h>
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
	void DrawSuit(int, int, Suit suit);
	coords ScanF(char * chars);
private:
	char _console_buffer[BUFFER_HEIGHT][BUFFER_WIDTH + 1];
	HANDLE _main_buffer;
	HANDLE _secondary_buffer;
	CHAR_INFO _char_info[BUFFER_HEIGHT*BUFFER_WIDTH];
	SMALL_RECT mainRect;
	SMALL_RECT secRect;
	COORD coordBufSize;
	COORD coordBufCoord;
};

#endif /* DisplayManager_hpp */
