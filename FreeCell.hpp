/*************************************************************
* Author:		Ian Murphy
* Filename:		FreeCell.hpp
* Date Created:	2/6/2016
* Modifications:	2/10/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: FreeCell
*
* Purpose: Encapuslates movement logic and other classes in order to implement freecell.
*
* Manager functions:
* 	FreeCell(int gamenumber = 99476635345443);
		ctor with default gamenumebr
    FreeCell(const FreeCell & cp);
		copy c'tor, works, but why would you use this?
    ~FreeCell();
		dtor
    FreeCell & operator = (const FreeCell & rhs);	
		also works, but why?
    
    void StartNewGame();
		called to start a new game
*
* 
*		...
*************************************************************************/

#ifndef FreeCell_hpp
#define FreeCell_hpp

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
#include "GameBoard.hpp"
#include <string>
#include <conio.h>


class FreeCell
{
public:
    FreeCell(int gamenumber = 99476635345443);
    FreeCell(const FreeCell & cp);
    ~FreeCell();
    FreeCell & operator = (const FreeCell & rhs);
    
    void StartNewGame();
private:
    void Deal(DisplayManager & dm);
    void StartGameUI();
  
    GameBoard _board;
    Deck _deck;
    bool _gameover;
    //std::string _error_msg;
};

#endif /* FreeCell_hpp */
