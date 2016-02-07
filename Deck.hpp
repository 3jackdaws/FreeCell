//
//  Deck.hpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

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
    Deck(int size = DECK_SIZE, int seed = 1234567890);
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
