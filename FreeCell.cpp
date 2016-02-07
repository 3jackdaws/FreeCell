//
//  FreeCell.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "FreeCell.hpp"

FreeCell::FreeCell(int gamenumber) : _gameover(false), _deck(52, gamenumber)
{
    
}

FreeCell::FreeCell(const FreeCell & cp)
{
    
}

FreeCell::~FreeCell()
{
    
}

FreeCell & FreeCell::operator=(const FreeCell &rhs)
{
    if(this != &rhs)
    {
        
    }
    return *this;
}

void FreeCell::StartNewGame()
{
    StartGameUI();
}

void FreeCell::StartGameUI()
{
    DisplayManager dm;
    dm.Fill(' ');
    _board.DrawStatics(dm);
    
    Deal(dm);
    char d = '0';
    std::string choice;
    Card temp;
    int i = 0;
    
    while(!_gameover)
    {
        _board.Update(dm);
        WriteError(dm);
        dm.Display();
        std::getline(std::cin, choice);
        switch(toupper(*choice.c_str()))
        {
            case 'W':
                _board.SelUp();
                break;
            case 'A':
                _board.SelLeft();
                break;
            case 'S':
                _board.SelDown();
                break;
            case 'D':
                _board.SelRight();
                break;
            case ' ':
                _board.PickUpCard();
            default:;
        }
        
        
        //_board.SelRight();
//        temp = _board.RemoveFromPlayArea(i%8);
//        if(!_board.PutToFreeCells(i%4, temp))
//        {
//            _board.PutToPlayArea(i%8, temp);
//            _error_msg = "That Free Cell is already full.";
//        }
//        _board.Update(dm);
//        WriteError(dm);
//        dm.Display();
//
//        temp = _board.RemoveFromPlayArea(6);
//        if(!_board.PutToPlayArea(5, temp))
//        {
//            _board.ForceToPlayArea(6, temp);
//            _error_msg = "That Card cannot go there.";
//        }
        //i++;
    }
}

void FreeCell::Deal(DisplayManager & dm)
{
    for (int i = 0; i<52; i++)
    {
        Card temp = _deck.Draw();
        _board.ForceToPlayArea(i%8, temp);
    }
}

void FreeCell::WriteError(DisplayManager & dm)
{
    int size = _error_msg.length();
    dm.Rect(BUFFER_HEIGHT-1, 0, size, 1, ' ');
    dm.Text(BUFFER_HEIGHT-1, 0, size+1, _error_msg.c_str());
}