//
//  Card.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "Card.hpp"

Card::Card()
{
    
}

Card::Card(enum Suit s, enum Rank r) : _suit(s), _rank(r)
{
    
}

Card::Card(const Card & cp) : _rank(cp._rank), _suit(cp._suit)
{
    
}

Card::~Card()
{
    
}

Card & Card::operator=(const Card & rhs)
{
    if(this != &rhs)
    {
        _rank = rhs._rank;
        _suit = rhs._suit;
    }
    return *this;
}

bool Card::operator != (const Card & rhs)
{
    if(_rank != rhs._rank || _suit != rhs._suit)
        return true;
    return false;
}

Suit Card::Suit()
{
    return _suit;
}

Rank Card::Rank()
{
    return _rank;
}

void Card::Suit(enum Suit s)
{
    _suit = s;
}

void Card::Rank(enum Rank r)
{
    _rank = r;
}

const char * Card::RankText()
{
    return _RankText[_rank];
}

const char * Card::SuitText()
{
    return _SuitText[_suit];
}
