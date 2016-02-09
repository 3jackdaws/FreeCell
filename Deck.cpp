//
//  Deck.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "Deck.hpp"

Deck::Deck(int size) : _deck(size), _size(DECK_SIZE), _top_of_deck(0)
{
	//IDGAF about your deck size
	for (int rank = 0; rank < 13; rank++)
	{
		for (int suit = 0; suit < 4; suit++)
		{
			_deck[DECK_SIZE-1 - ((suit * 13) + rank)] = Card((Suit)suit, (Rank)rank);
		}
	}
}

Deck::Deck(const Deck & cp) : _deck(cp._deck), _size(cp._size), _top_of_deck(cp._top_of_deck)
{
    
}

Deck::~Deck()
{
    
}

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
