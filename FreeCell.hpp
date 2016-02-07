//
//  FreeCell.hpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef FreeCell_hpp
#define FreeCell_hpp

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
#include "GameBoard.hpp"
#include <string>

class FreeCell
{
public:
    FreeCell(int gamenumber = 4777483);
    FreeCell(const FreeCell & cp);
    ~FreeCell();
    FreeCell & operator = (const FreeCell & rhs);
    
    void StartNewGame();
private:
    void Deal(DisplayManager & dm);
    void StartGameUI();
    void WriteError(DisplayManager & dm);
    GameBoard _board;
    Deck _deck;
    bool _gameover;
    std::string _error_msg;
};

#endif /* FreeCell_hpp */
