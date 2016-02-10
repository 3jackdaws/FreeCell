/*************************************************************
* Author:		Ian Murphy
* Filename:		Card.cpp
* Date Created: 2/4/2016
* Modifications:	2/9/16 - Added documentation
*
**************************************************************/



#include "Card.hpp"

const char * Card::_SuitText[4]{
	"HEARTS",
	"SPADES",
	"DIAMONDS",
	"CLUBS"
};

const char * Card::_RankText[13]{
	"ACE",
	"TWO",
	"THREE",
	"FOUR",
	"FIVE",
	"SIX",
	"SEVEN",
	"EIGHT",
	"NINE",
	"TEN",
	"JACK",
	"QUEEN",
	"KING"
};
/**********************************************************************
* Purpose: This is a default ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      does nothing at all
*
************************************************************************/
Card::Card()
{
    
}

/**********************************************************************
* Purpose: This is a two argument ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      Instantiates a Card object with specified suit and rank
*
************************************************************************/
Card::Card(enum Suit s, enum Rank r) : _suit(s), _rank(r)
{
    
}

/**********************************************************************
* Purpose: This is a copy ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      copies the Card object
*
************************************************************************/
Card::Card(const Card & cp) : _rank(cp._rank), _suit(cp._suit)
{
    
}

/**********************************************************************
* Purpose: This is a d'tor
*
* Precondition:
*     None
*
* Postcondition:
*      does nothing at all
*
************************************************************************/
Card::~Card()
{
    
}

/**********************************************************************
* Purpose: Operator = overload
*
* Precondition:
*     both participlants must be instantiated objects
*
* Postcondition:
*      the left hand side object is equal to the right hand size object
*
************************************************************************/
Card & Card::operator=(const Card & rhs)
{
    if(this != &rhs)
    {
        _rank = rhs._rank;
        _suit = rhs._suit;
    }
    return *this;
}

/**********************************************************************
* Purpose: operator != overload.
*
* Precondition:
*     same as op = above
*
* Postcondition:
*      returns a true if the cards have identical data memebers because it was apparently impossible for the normal op = to confirm that
*
************************************************************************/
bool Card::operator != (const Card & rhs)
{
    if(_rank != rhs._rank || _suit != rhs._suit)
        return true;
    return false;
}

/**********************************************************************
* Purpose: Getter for _suit
*
* Precondition:
*     must object
*
* Postcondition:
*      returns the Suit
*
************************************************************************/
Suit Card::Suit()
{
    return _suit;
}

/**********************************************************************
* Purpose: Getter for _rank
*
* Precondition:
*     must object
*
* Postcondition:
*      returns the Rank
*
************************************************************************/
Rank Card::Rank()
{
    return _rank;
}

/**********************************************************************
* Purpose: Setter for _suit
*
* Precondition:
*     must object
*
* Postcondition:
*      sets the Suit
*
************************************************************************/
void Card::Suit(enum Suit s)
{
    _suit = s;
}

/**********************************************************************
* Purpose: Setter for _rank
*
* Precondition:
*     must object
*
* Postcondition:
*      sets the Rank
*
************************************************************************/
void Card::Rank(enum Rank r)
{
    _rank = r;
}

/**********************************************************************
* Purpose: Gets the text for the corresponding enum
*
* Precondition:
*     must object
*
* Postcondition:
*      returns the const char * to the correct text
*
************************************************************************/
const char * Card::RankText()
{
    return _RankText[_rank];
}

/**********************************************************************
* Purpose: Gets the text for the corresponding enum
*
* Precondition:
*     must object
*
* Postcondition:
*      returns the const char * to the correct text
*
************************************************************************/
const char * Card::SuitText()
{
    return _SuitText[_suit];
}
