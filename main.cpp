//
//  main.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/2/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//




#include <iostream>
using std::cout;
using std::endl;

//#include "DisplayManager.hpp"
#include "Deck.hpp"
#include "GameBoard.hpp"
#include "FreeCell.hpp"
#include <curses.h>

int main(int argc, const char * argv[]) {
    FreeCell freecell;
    freecell.StartNewGame();
    
//    DisplayManager dm;
//    dm.Fill(' ');
//    
//    Deck mydeck;
//    
//    mydeck.Init(2999378);
//    Card temp = mydeck.Draw();
//    
//    GameBoard mygame;
//    
//    Card jk(HEARTS, JACK);
//    Card tw(CLUBS, TWO);
//    Card qu(SPADES, QUEEN);
//    Card tn(DIAMONDS, TEN);
//    mygame.PutToFreeCells(0, jk);
//    mygame.PutToFreeCells(1, tw);
//    mygame.PutToFreeCells(2, qu);
//    mygame.PutToFreeCells(3, tn);
//    
//    mygame.PutToHomeCells(0, jk);
//    mygame.PutToHomeCells(1, tw);
//    mygame.PutToHomeCells(2, qu);
//    mygame.PutToHomeCells(3, tn);
//    mygame.DrawStatics(dm);
//    char i;
//    bool deletemode = false;
//    while(true)
//    {
//        mygame.Update(dm);
//        dm.Display();
//        std::cin>>i;
//        if(i == 'd')
//        {
//            deletemode ? deletemode = false: deletemode = true;
//        }
//        else if(i == 'c')
//        {
//            
//        }
//        else
//        {
//            if(deletemode)
//            {
//                mygame.RemoveFromPlayArea(atoi(&i)%8);
//            }
//            else
//                mygame.PutToPlayArea(atoi(&i)%8, mydeck.Draw());
//        }
//        
//    }
    return 0;
}
