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
#define _CRTDBG_MAP_ALLOC

int main(int argc, const char * argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_setmode(_fileno(stdout), _O_U16TEXT);
	setlocale(LC_ALL, "");
	//SetConsoleCP(CP_UTF8);
	//std::wcout << L"\u2666" << endl;
	system("MODE CON COLS=100 LINES=60");
	std::string input;
	int rand_gamenumber = 0;
	while(toupper(input.c_str()[0]) != 'Q')
	{
		system("cls");
		std::wcout << "Enter gamenumber or leave empty for random game.\nReserved Gamenumbers: \n\t1 - Deal Unshuffled Deck\n\t2 - Easy" << endl;
		std::getline(std::cin, input);
		if (toupper(input.c_str()[0]) != 'Q')
		{
			FreeCell freecell(atoi(input.c_str()));
			freecell.StartNewGame();
		}
		
	}

	
    return 0;
}
