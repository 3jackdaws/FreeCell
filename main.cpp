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

#include <io.h>
#include <fcntl.h>


int main(int argc, const char * argv[]) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	setlocale(LC_ALL, "");
	system("MODE CON COLS=100 LINES=60");
	//cout << (char)4 << endl;
	FreeCell freecell(1);
    freecell.StartNewGame();
	
    return 0;
}
