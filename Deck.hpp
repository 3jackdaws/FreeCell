/*************************************************************
* Author:		Ian Murphy
* Filename:		Deck.hpp
* Date Created:	2/4/2016
* Modifications:	2/4/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: Deck
*
* Purpose: This class implements a stack of cards.  A consumer can draw from the top of the stack like a deck.
*
* Manager functions:
* 	Deck(int size = DECK_SIZE);
    Deck(const Deck & cp);
    ~Deck();
    Deck & operator = (const Deck & rhs);
*
* Methods:
*	Draw()
	draws and returns a card by value
	Init()
		Shuffles the deck based on a provided seed.
*		...
*************************************************************************/

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include "Card.hpp"
#include "StackA.h"

class Card;
const unsigned short DECK_SIZE = 52;

class Deck
{
public:
    Deck(int size = DECK_SIZE);
    Deck(const Deck & cp);
    ~Deck();
    Deck & operator = (const Deck & rhs);
    
    Card Draw();
    void Init(int seed);
private:
    Array<Card> _deck;
    int _top_of_deck;
    int _size;
};
#endif /* Deck_hpp */
