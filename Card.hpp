//
//  Card.hpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//



#ifndef Card_hpp
#define Card_hpp



enum Suit{
    HEARTS,
    SPADES,
    DIAMONDS,
    CLUBS,
    NULLSUIT
};

enum Rank{
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
    const char * _SuitText[4]{
        "HEARTS",
        "SPADES",
        "DIAMONDS",
        "CLUBS"
    };
    
    const char * _RankText[13]{
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
