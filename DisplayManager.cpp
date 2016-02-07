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
    VertLine(0, BUFFER_WIDTH, BUFFER_HEIGHT, '\0');
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
    
    for (int row = 0; row <BUFFER_HEIGHT; row++)
    {
        std::cout<<_console_buffer[row]<<"\n";
    }
    std::cout<<std::endl;
    
}

void DisplayManager::Fill(char c)
{
    for (int row = 0; row < BUFFER_HEIGHT; row++)
    {
        for (int col = 0; col<BUFFER_WIDTH; col++)
        {
            _console_buffer[row][col] = c;
        }
    }
    
}


void DisplayManager::Write(int row, int col, char w)
{
    _console_buffer[row][col] = w;
}

void DisplayManager::Rect(int startrow, int startcol, int width, int height, char fill)
{
    
    for (int row = startrow; row < height+startrow; row++)
    {
        for (int col = startcol; col<startcol+width; col++)
        {
            _console_buffer[row][col] = fill;
        }
    }
}

void DisplayManager::Text(int startrow, int startcol, int max, const char string[])
{
    for (int col = startcol, i = 0; col<startcol+max && i<strlen(string); col++, i++)
    {
        _console_buffer[startrow][col] = string[i];
    }
}

void DisplayManager::Line(int startrow, int startcol, int length, char fill)
{
    for (int i = startcol; i<startcol+length; i++)
    {
        _console_buffer[startrow][i] = fill;
    }
    
}

void DisplayManager::VertLine(int startrow, int startcol, int length, char fill)
{
    for (int i = startrow; i<startrow+length+1; i++)
    {
        _console_buffer[i][startcol] = fill;
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