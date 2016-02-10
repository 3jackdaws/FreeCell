/*************************************************************
* Author:		Ian Murphy
* Filename:		main.cpp
* Date Created:	2/6/2016
* Modifications:	2/9/2016 - Added documentation
*
**************************************************************\

/*************************************************************
*
* Lab 3 - FreeCell
*
* Overview:
*	This program allows a user to play freecell in the console.
*
* Input:
*	Input consists of keyboard commands that correspond to certain actions.  The program will alert users to possible inputs and changes to the game state.
*
* Output:
*	The program outputs the state of the freecell gameboard after most inputs.  Output is to the console.
*
************************************************************/
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
	std::wcout << sizeof(Card) << endl;
	
    return 0;
}
