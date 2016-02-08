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

#include <windows.h>
#include "Deck.hpp"
#include "GameBoard.hpp"
#include "FreeCell.hpp"


int main(int argc, const char * argv[]) {
    FreeCell freecell;
    freecell.StartNewGame();
	
    return 0;
}
