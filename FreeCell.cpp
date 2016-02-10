/*************************************************************
* Author:		Ian Murphy
* Filename:		FreeCell.cpp
* Date Created:	2/6/16
* Modifications:	2/10/16 - Added documentation
*
**************************************************************/

#include "FreeCell.hpp"

/**********************************************************************
* Purpose: This is a default ctor.
*
* Precondition:
*     None
*
* Postcondition:
*     has some saved game in it
*
************************************************************************/
FreeCell::FreeCell(int gamenumber) : _gameover(false), _deck(52)
{
	switch (gamenumber)
	{
	case 1:
		break;
	case 2:
		_deck.Init(1234);
		break;
	default:
		_deck.Init(gamenumber);
	}
	
	
}

/**********************************************************************
* Purpose: copy ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      copies it
*
************************************************************************/
FreeCell::FreeCell(const FreeCell & cp) : _board(cp._board), _deck(cp._deck), _gameover(cp._gameover)
{
    
}

/**********************************************************************
* Purpose: destructor.
*
* Precondition:
*     None
*
* Postcondition:
*      destructs it
*
************************************************************************/
FreeCell::~FreeCell()
{
    
}

/**********************************************************************
* Purpose: op = overload
*
* Precondition:
*     objects
*
* Postcondition:
*      basically copies it
*
************************************************************************/
FreeCell & FreeCell::operator=(const FreeCell &rhs)
{
    if(this != &rhs)
    {
		_board = rhs._board;
		_gameover = rhs._gameover;
		_deck = rhs._deck;
    }
    return *this;
}

/**********************************************************************
* Purpose: starts a new game

*
* Precondition:
*     None
*
* Postcondition:
*      starts a new game
*
************************************************************************/
void FreeCell::StartNewGame()
{
    StartGameUI();
}

/**********************************************************************
* Purpose: Initializes game UI and control logic.
*
* Precondition:
*     Consumer can't call this
*
* Postcondition:
*      Game is playable
*
************************************************************************/
void FreeCell::StartGameUI()
{
    DisplayManager dm; //instantiate a DisplayManager
	/*system("MODE CON COLS=101 LINES=40");*/
    dm.Fill(L" ");
    _board.DrawStatics(dm);		//draw the non moving display elements
    
    Deal(dm);				//deal the deck to the playing field
    char d = '0';
   // std::string choice;
    Card temp;
    int i = 0;
	bool quit = false;
    
    while(!_board.CheckWinCondition() && !quit)
    {
        _board.Update(dm);		//update display buffer
        //WriteError(dm);
        dm.Display();			//display updated buffer
		d = getch();			//get unbuffered keyboard command
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
				_board.DebugPlaceCard();		//this will force place a single card on top of any stack
				break;
			case 'q':
				quit = _board.QuitGamePrompt(dm);	//no
				break;
			default:;
				//std::wcout << (unsigned char)d << endl;
        }
    }
	if (!quit)
	{
		_board.WinSplash(dm);
		dm.Display();
	}
	
}

/**********************************************************************
* Purpose: Deals the deck to playing field
*
* Precondition:
*     None
*
* Postcondition:
*      no more deck
*
************************************************************************/
void FreeCell::Deal(DisplayManager & dm)
{
    for (int i = 0; i<52; i++)
    {
        Card temp = _deck.Draw();
        _board.ForceToPlayArea(i%8, temp);
    }
}

