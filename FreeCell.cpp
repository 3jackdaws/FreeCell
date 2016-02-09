//
//  FreeCell.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "FreeCell.hpp"

FreeCell::FreeCell(int gamenumber) : _gameover(false), _deck(52)
{
	if (gamenumber == 1)
	{

	}
	else
		_deck.Init(gamenumber);
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
	/*system("MODE CON COLS=101 LINES=40");*/
    dm.Fill(L" ");
    _board.DrawStatics(dm);
    
    Deal(dm);
    char d = '0';
    std::string choice;
    Card temp;
    int i = 0;
    
    while(!_board.CheckWinCondition())
    {
        _board.Update(dm);
        //WriteError(dm);
        dm.Display();
		d = getch();
        switch(d)
        {
            case 'w':
                _board.SelUp();
                break;
            case 'a':
                _board.SelLeft();
                break;
            case 's':
                _board.SelDown();
                break;
            case 'd':
                _board.SelRight();
                break;
            case ' ':
                _board.PickUpCard();
				break;
			case 'f':
				_board.DebugPlaceCard();
				break;
			default:;
				//std::wcout << (unsigned char)d << endl;
        }
    }
	std::wcout << "You've won!" << endl;
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
    dm.Rect(BUFFER_HEIGHT-1, 0, size, 1, L"\u0020");
    dm.Text(BUFFER_HEIGHT-1, 0, size+1, _error_msg.c_str());
}