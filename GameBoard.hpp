//
//  GameBoard.hpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef GameBoard_hpp
#define GameBoard_hpp



#include <stdio.h>
#include "Deck.hpp"
#include "StackL.h"
#include "DisplayManager.hpp"
class DisplayManager;

const unsigned short _DBIT_FREECELL = 0;
const unsigned short _DBIT_PLAYAREA = 2;
const unsigned short _DBIT_HOMEROW = 1;
const unsigned short _DBIT_PLAYAREA_FULL = 3;


class GameBoard
{
    const int TOP_MARGIN = 3;
    const int LEFT_MARGIN = 3;
    const int TEXT_MARGIN = 3;
    const int ROW_MARGIN = 3;
    const int CARD_WIDTH = 10;
    const int CARD_HEIGHT = 8;
    const char CARD_BORDER = '.';
    wchar_t * CARD_TOP = L"\u2550";
    const wchar_t *CARD_SIDES = L"\u2551";
    const wchar_t* CARD_TOPL = L"\u2554";
    const wchar_t* CARD_TOPR = L"\u2557";
    const wchar_t* CARD_BOTL = L"\u255A";
    const wchar_t* CARD_BOTR = L"\u255D";
    const wchar_t* SEL_CARD_BORDER = L"\u2551";
public:
    GameBoard();
    GameBoard(const GameBoard & cp);
    ~GameBoard();
    GameBoard & operator = (const GameBoard & rhs);
    
    Card RemoveFromPlayArea(int row);
    Card RemoveFromFreeCells(int row);
    Card RemoveFromHomeCells(int row);
    
    void ForceToPlayArea(int row, Card card);
	void DebugPlaceCard();
    
    bool PutToPlayArea(int row, Card card);
    bool PutToFreeCells(int row, Card card);
    void PutToHomeCells(int row, Card card);
    
    void Update(DisplayManager & dm);
	bool CheckWinCondition();
	void SetWinCond(int);
    
    void DrawStatics(DisplayManager & dm);
    void DrawCard(DisplayManager & dm, int row, int col, Card & card);
    void DrawSelectedCard(DisplayManager & dm, int row, int col, Card & card);
    
    bool GetDBit(unsigned short area, unsigned short row);
    
    void SelUp();
    void SelDown();
    void SelLeft();
    void SelRight();
    void Notify();
    
    bool PickUpCard();
private:
    Array<Card> _freecells;
    Array<StackL<Card>> _playarea;
    Array<StackA<Card>> _homecells;
    
    bool _dbit[4][8];
    int _card_select;
    
    StackA<Card> _pickup_cards;
    int pickup_row;

	bool _homecell_filled[4];
};

#endif /* GameBoard_hpp */
