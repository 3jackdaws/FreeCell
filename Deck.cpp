/*************************************************************
* Author:		Ian Murphy
* Filename:		Array.h
* Date Created:	2/04/2016
* Modifications:	2/9/16 - Added documentation
*
**************************************************************/

#include "Deck.hpp"



/**********************************************************************
* Purpose: This is the only ctor, an empty deck is useless.
*
* Precondition:
*     None
*
* Postcondition:
*      fills a deck with 52 Cards. Why does it have a size argument? Holdover from C, idk
*
************************************************************************/
Deck::Deck(int size) : _deck(DECK_SIZE), _size(DECK_SIZE), _top_of_deck(0)
{
	//IDGAF about your deck size
	for (int rank = 0; rank < 13; rank++)
	{
		for (int suit = 0; suit < 4; suit++)
		{
			_deck[DECK_SIZE-1 - ((suit * 13) + rank)] = Card((Suit)suit, (Rank)rank);	//put da cards in the deck
		}
	}
}

/**********************************************************************
* Purpose: This is a copy ctor.
*
* Precondition:
*     obvious copy ctor stuff
*
* Postcondition:
*      No one reads this, but copy c'tor stuff
*
************************************************************************/
Deck::Deck(const Deck & cp) : _deck(cp._deck), _size(cp._size), _top_of_deck(cp._top_of_deck)
{
    
}

/**********************************************************************
* Purpose: This is a d'tor.
*
* Precondition:
*     None
*
* Postcondition:
*      object destruction
*
************************************************************************/
Deck::~Deck()
{
    
}

/**********************************************************************
* Purpose: Op = overload
*
* Precondition:
*     must have objects hsfj halsfjhnalsnvfca,.msdncd
*
* Postcondition:
*      basically a copy c'tor only can be used on instance objects
*
************************************************************************/
Deck & Deck::operator=(const Deck &rhs)
{
    if(this != &rhs)
    {
        _deck = rhs._deck;
        _size = rhs._size;
        _top_of_deck = rhs._top_of_deck;
    }
    return *this;
}

/**********************************************************************
* Purpose: Takes a card off the top of the deck.
*
* Precondition:
*     deck needs to have cards, but that happens in the c'tor so nothing really
*
* Postcondition:
*      returns the top card by value
*
************************************************************************/
Card Deck::Draw()
{
    if(_size <= 0)
        throw Exception("No cards in deck");
    _size--;
    return _deck[_top_of_deck++];
}

void Deck::Init(int seed)
{
    srand(seed);
    
    int rnum = 0;
    for (int i = 0; i<DECK_SIZE; i++)
    {
        rnum = rand()%(DECK_SIZE);
        Card hold = _deck[rnum];
        _deck[rnum] = _deck[i];
        _deck[i] = hold;
    }
}
