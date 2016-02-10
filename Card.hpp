/*************************************************************
* Author:		Ian Murphy
* Filename:		CArd.hpp
* Date Created:	2/4/16
* Modifications: 2/9/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: Card
*
* Purpose: This class is a representation of Card.  It does card stuff, but cards dont do anything so it just stores data
*
* Manager functions:
	Obvious Standard stuff
* 	Card();
    Card(Suit s, Rank r);
    Card(const Card & cp);
    ~Card();
    Card & operator = (const Card & rhs);
    bool operator != (const Card & rhs);
*
* Methods:
*	void Rank(Rank r);
		sets the rank
    void Suit(Suit s);
		sets the suit
    enum Rank Rank();
		returns the rank
    enum Suit Suit();
		returns the suit
    const char * RankText();
		returns the rank text
    const char * SuitText();
		returns the suit text
*		...
*************************************************************************/
#ifndef Card_hpp
#define Card_hpp



enum Suit : unsigned char{
    HEARTS,
    SPADES,
    DIAMONDS,
    CLUBS,
    NULLSUIT
};

enum Rank : unsigned char{
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    NULLRANK
};



class Card
{
	static const char * _SuitText[4];
    
	const static const char * _RankText[13];
    
public:
    Card();
    Card(Suit s, Rank r);
    Card(const Card & cp);
    ~Card();
    Card & operator = (const Card & rhs);
    bool operator != (const Card & rhs);
    
    void Rank(Rank r);
    void Suit(Suit s);
    enum Rank Rank();
    enum Suit Suit();
    const char * RankText();
    const char * SuitText();
    
private:
    enum Rank _rank;
    enum Suit _suit;
    
};

#endif /* Card_hpp */
