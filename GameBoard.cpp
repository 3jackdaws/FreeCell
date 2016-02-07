//
//  GameBoard.cpp
//  FreeCell
//
//  Created by Ian Murphy on 2/4/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "GameBoard.hpp"

GameBoard::GameBoard() : _freecells(4), _homecells(4), _playarea(8), _card_select(0)
{
    
    for (int i = 0; i<4; i++)
    {
        _dbit[_DBIT_FREECELL][i] = false;
        
    }
    for (int i = 0; i<4; i++)
    {
        _dbit[_DBIT_HOMEROW][i] = false;
        
    }
    for (int i = 0; i<8; i++)
    {
        _dbit[_DBIT_PLAYAREA][i] = true;
        _dbit[_DBIT_PLAYAREA_FULL][i] = true;
    }
    for (int i = 0; i<4; i++)
    {
        _freecells[i] = Card(NULLSUIT, NULLRANK);
    }
    for (int i = 0; i<4; i++)
    {
        _homecells[i].Resize(52);
    }
    
    
}

GameBoard::GameBoard(const GameBoard & cp) : _freecells(cp._freecells), _homecells(cp._homecells), _playarea(cp._playarea)
{
    
}

GameBoard::~GameBoard()
{
    
}

GameBoard & GameBoard::operator = (const GameBoard & rhs)
{
    if(this != &rhs)
    {
        _freecells = rhs._freecells;
        _playarea = rhs._playarea;
        _homecells = rhs._homecells;
    }
    return *this;
}

Card GameBoard::RemoveFromPlayArea(int row)
{
    _dbit[_DBIT_PLAYAREA_FULL][row] = true;
    _dbit[_DBIT_PLAYAREA][row] = true;
    Card temp;
    try {
        temp = _playarea[row].Pop();
    } catch (Exception e) {
        
    }
    return temp;
}
Card GameBoard::RemoveFromFreeCells(int row)
{
    _dbit[_DBIT_FREECELL][row] = true;
    Card remove = _freecells[row];
    _freecells[row] = Card(NULLSUIT, NULLRANK);
    return remove;
}
Card GameBoard::RemoveFromHomeCells(int row)
{
    _dbit[_DBIT_HOMEROW][row] = true;
    return _homecells[row].Pop();
}

bool GameBoard::PutToPlayArea(int row, Card card)
{
    Card top = _playarea[row].Peek();
    int topsuitmod2 = top.Suit()%2;
    int cardsuitp1mod2 = (card.Suit()+1)%2;
    int toprank = top.Rank();
    int cardrankm1 = card.Rank()-1;
    if(top.Suit()%2 == (card.Suit()+1)%2 && top.Rank() == card.Rank() + 1)
    {
        _dbit[_DBIT_PLAYAREA][row] = true;
        _playarea[row].Push(card);
        return true;
    }
    else
        return false;
        
    
}
bool GameBoard::PutToFreeCells(int row, Card card)
{
    if(_freecells[row].Rank() == NULLRANK)
    {
        _freecells[row] = card;
        _dbit[_DBIT_FREECELL][row] = true;
        return true;
    }
    else
        return false;
        
}
void GameBoard::PutToHomeCells(int row, Card card)
{
    _dbit[_DBIT_HOMEROW][row] = true;
    _homecells[row].Push(card);
}

void GameBoard::Update(DisplayManager & dm)
{
    //FREE CELLS UPDATE HERE
    for (int row = 0; row<4; row++)
    {
        if(_dbit[_DBIT_FREECELL][row])
        {
            _dbit[_DBIT_FREECELL][row] = false;
            if(_card_select == row)
                DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN+(row*CARD_WIDTH+row), _freecells[row]);
            else
                DrawCard(dm, TOP_MARGIN, LEFT_MARGIN+(row*CARD_WIDTH+row), _freecells[row]);
        }
        if(_pickup_cards.Size() > 0 && _card_select == row)
        {
            DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN+(row*CARD_WIDTH+row), _pickup_cards.Peek());
        }
    }
    //HOME CELLS UPDATE HERE
    for (int row = 0; row<4; row++)
    {
        if(_dbit[_DBIT_HOMEROW][row])
        {
            _dbit[_DBIT_HOMEROW][row] = false;
            if(_card_select == row+4)
                DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN+50+(row*CARD_WIDTH+row), _homecells[row].Peek());
            else
                DrawCard(dm, TOP_MARGIN, LEFT_MARGIN+50+(row*CARD_WIDTH+row), _homecells[row].Peek());
        }
        if(_pickup_cards.Size() > 0 && _card_select == row+4)
        {
            DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN+(row*CARD_WIDTH+row), _pickup_cards.Peek());
        }
    }
    //UPDATE PLAYAREA
    for (int row = 0; row<8; row++)
    {
        if(_dbit[_DBIT_PLAYAREA][row])          //if a card has been added
        {
            _dbit[_DBIT_PLAYAREA][row] = false; //set the flag back
            int stack_size = _playarea[row].Size();
            int number_to_update = 0;
            
            if(_dbit[_DBIT_PLAYAREA_FULL][row])
            {
                _dbit[_DBIT_PLAYAREA_FULL][row] = false;
                number_to_update = _playarea[row].Size();
                dm.Rect(TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT, LEFT_MARGIN+(row*CARD_WIDTH+row), CARD_WIDTH, BUFFER_HEIGHT-CARD_HEIGHT-5, ' ');
            }//if the whole stack needs to be updated
            else
            {
                number_to_update = 1;
            }
            StackA<Card> tempStack(_playarea[row].Size());
            for (int i = 0; i<number_to_update; i++)
            {
                tempStack.Push(_playarea[row].Pop());
            }
            int i = 0;
            for (i = stack_size-number_to_update; i<stack_size; i++)
            {
                Card temp = tempStack.Pop();
                if(_card_select - 8  == row+i*8 && _pickup_cards.Size() == 0)
                    DrawSelectedCard(dm, TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT+2*i, LEFT_MARGIN+(row*CARD_WIDTH+row), temp);
                else
                    DrawCard(dm, TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT+2*i, LEFT_MARGIN+(row*CARD_WIDTH+row), temp);
                _playarea[row].Push(temp);
            }
            if(_pickup_cards.Size()>0 && _card_select>7 &&_card_select%8 == row)
            {
                StackA<Card> temps(_pickup_cards.Size());
                int pd_size = _pickup_cards.Size();
                for (int s = 0; s<pd_size; s++)
                {
                    Card temp = _pickup_cards.Pop();
                    DrawSelectedCard(dm, TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT+2*i+1, LEFT_MARGIN+(row*CARD_WIDTH+row), temp);
                    temps.Push(temp);
                    i++;
                }
                for (int s = 0; s<pd_size; s++)
                {
                    _pickup_cards.Push(temps.Pop());
                }
            }
        }
    }
    //UPDATE SELECTED CARD
    
}

bool GameBoard::GetDBit(unsigned short area, unsigned short row)
{
    return _dbit[area][row];
}

void GameBoard::DrawStatics(DisplayManager & dm)
{
    dm.Line( TOP_MARGIN+CARD_HEIGHT, LEFT_MARGIN, CARD_WIDTH*4+3, '-');
    dm.Line( TOP_MARGIN+CARD_HEIGHT, LEFT_MARGIN+50, CARD_WIDTH*4+3, '-');
    dm.Line( TOP_MARGIN+CARD_HEIGHT+ROW_MARGIN-1, LEFT_MARGIN, CARD_WIDTH*8+13, '-');
    char * free_cell_text = "FREE CELLS";
    char * home_row_text = "HOME CELLS";
    char * play_area_text = "PLAY AREA";
    int start = ((CARD_WIDTH*4+3)-10)/2;
    dm.Text(TOP_MARGIN+CARD_HEIGHT, start+LEFT_MARGIN, 12, free_cell_text);
    dm.Text(TOP_MARGIN+CARD_HEIGHT, start+LEFT_MARGIN+50, 12, home_row_text);
    dm.Text(TOP_MARGIN+CARD_HEIGHT+ROW_MARGIN-1, 45, 12, play_area_text);
}

void GameBoard::DrawCard(DisplayManager & dm, int row, int col, Card & card)
{
    dm.Rect(row, col, CARD_WIDTH, CARD_HEIGHT, ' ');
    dm.Line(row, col+1, CARD_WIDTH-2, CARD_TOP);        //top edge
    dm.Line(row+CARD_HEIGHT-1, col+1, CARD_WIDTH-2, CARD_TOP);    //bottom edge
    dm.VertLine(row+1, col, CARD_HEIGHT-2, CARD_SIDES);
    dm.VertLine(row+1, col+CARD_WIDTH-1, CARD_HEIGHT-2, CARD_SIDES);
    dm.Write(row, col, CARD_TOPL);
    dm.Write(row, col+CARD_WIDTH-1, CARD_TOPR);
    dm.Write(row+CARD_HEIGHT-1, col, CARD_BOTL);
    dm.Write(row+CARD_HEIGHT-1, col+CARD_WIDTH-1, CARD_BOTR);
    
    if(card.Rank() != NULLRANK)
    {
        char abbrev[7] ={'\0'};
        if(card.Rank() == 0 || card.Rank()>8)
        {
            abbrev[0] = card.RankText()[0];
        }
        else
        {
            abbrev[0] = (char)(card.Rank()+0x31);
        }
        abbrev[1] = ' ';
        abbrev[2] = 'o';
        abbrev[3] = 'f';
        abbrev[4] = ' ';
        abbrev[5] = card.SuitText()[0];
        dm.Text(row+1, col+2, col+CARD_WIDTH, abbrev);
        dm.Text(row+TEXT_MARGIN, col+1, col+CARD_WIDTH, card.RankText());
        dm.Text(row+TEXT_MARGIN+1, col+1, col+CARD_WIDTH, "of");
        dm.Text(row+TEXT_MARGIN+2, col+1, col+CARD_WIDTH, card.SuitText());
    }
    
}
void GameBoard::ForceToPlayArea(int row, Card card)
{
    _dbit[_DBIT_PLAYAREA][row] = true;
    _playarea[row].Push(card);
}

void GameBoard::DrawSelectedCard(DisplayManager & dm, int row, int col, Card & card)
{
    
    dm.Rect(row, col, CARD_WIDTH, CARD_HEIGHT, ' ');
    dm.Line(row, col+1, CARD_WIDTH-2, SEL_CARD_BORDER);        //top edge
    dm.Line(row+CARD_HEIGHT-1, col+1, CARD_WIDTH-2, SEL_CARD_BORDER);    //bottom edge
    dm.VertLine(row+1, col, CARD_HEIGHT-2, SEL_CARD_BORDER);
    dm.VertLine(row+1, col+CARD_WIDTH-1, CARD_HEIGHT-2, SEL_CARD_BORDER);
    dm.Write(row, col, CARD_TOPL);
    dm.Write(row, col+CARD_WIDTH-1, CARD_TOPR);
    dm.Write(row+CARD_HEIGHT-1, col, CARD_BOTL);
    dm.Write(row+CARD_HEIGHT-1, col+CARD_WIDTH-1, CARD_BOTR);
    
    if(card.Rank() != NULLRANK)
    {
        char abbrev[7] ={'\0'};
        if(card.Rank() == 0 || card.Rank()>8)
        {
            abbrev[0] = card.RankText()[0];
        }
        else
        {
            abbrev[0] = (char)(card.Rank()+0x31);
        }
        abbrev[1] = ' ';
        abbrev[2] = 'o';
        abbrev[3] = 'f';
        abbrev[4] = ' ';
        abbrev[5] = card.SuitText()[0];
        dm.Text(row+1, col+2, col+CARD_WIDTH, abbrev);
        dm.Text(row+TEXT_MARGIN, col+1, col+CARD_WIDTH, card.RankText());
        dm.Text(row+TEXT_MARGIN+1, col+1, col+CARD_WIDTH, "of");
        dm.Text(row+TEXT_MARGIN+2, col+1, col+CARD_WIDTH, card.SuitText());
    }
    
}

void GameBoard::SelUp()
{
    if(_pickup_cards.Size() > 0 && _card_select>=8)
    {
        Notify();
        _card_select = _card_select%8;
        Notify();
    }
    else if(_card_select>=8)
    {
        Notify();
        _card_select-=8;
        Notify();
    }
    
}
void GameBoard::SelDown()
{
    int t1 = _playarea[_card_select%8].Size();
    int t2 = _playarea[_card_select%8].Size()*8;
    int t3 = _card_select+8;
    int row = _card_select%8;
    if((_card_select<8 && _playarea[_card_select%8].Size()>0) || _playarea[row].Size()*8+row>=_card_select+8)
    {
        Notify();
        _card_select+=8;
        Notify();
    }
}
void GameBoard::SelLeft()
{
    int row = _card_select%8;
    if(row > 0)
    {
        Notify();
        _card_select--;
        Notify();
        if(_playarea[row-1].Size()*8+row+1 < _card_select+1)
            _card_select = _playarea[row-1].Size()*8+row+1;
    }
    
}
void GameBoard::SelRight()
{
    int row = _card_select%8;
    if(row < 7)
    {
        Notify();
        _card_select++;
        Notify();
        if(_playarea[row+1].Size()*8+row+1 < _card_select-1)
            _card_select = _playarea[row+1].Size()*8+row+1;
    }
    
}

void GameBoard::Notify()
{
    if(_card_select<8)
    {
        int test1 = _card_select/4;
        int test2 = _card_select%4;
        _dbit[_card_select/4][_card_select%4] = true;
    }
    else
    {
        int test = _card_select%8;
        _dbit[_DBIT_PLAYAREA][_card_select%8] = true;
        _dbit[_DBIT_PLAYAREA_FULL][_card_select%8] = true;
    }
}

bool GameBoard::PickUpCard()
{
    int row = _card_select%8;
    bool rval = false;
    
    if(_card_select < 4)        //SELECT FROM HOME ROW
    {
        if(_pickup_cards.Size() == 1)
        {
            if(_freecells[row].Rank() == NULLRANK)     //if A card is picked up and the cell is empty
            {
                _freecells[row] = _pickup_cards.Pop();
                _dbit[_DBIT_FREECELL][row] = true;
            }
            
        }
        else if (_pickup_cards.Size() == 0)
        {
            _pickup_cards.Resize(1);
            _pickup_cards.Push(_freecells[row]);
            _freecells[row] = Card(NULLSUIT, NULLRANK);
            _dbit[_DBIT_FREECELL][row] = true;
        }
        
    }
    else if(_card_select < 8)
    {
        
    }
    else
    {
        if(_pickup_cards.Size() == 0)
        {
            int col = (_card_select/8)-1;
            _pickup_cards.Resize(_playarea[row].Size()-col);
            
            int pa_size = _playarea[row].Size();
            bool _error_ = false;
            for (int i = 0; i<pa_size-col && !_error_; i++)
            {
                Card temp =_playarea[row].Pop();
                if(_pickup_cards.Size() == 0 || (temp.Suit()%2 == (_pickup_cards.Peek().Suit()+1)%2 && temp.Rank() == _pickup_cards.Peek().Rank() + 1))
                    _pickup_cards.Push(temp);
                else
                    _error_=true;
            }
            if(_error_)
            {
                for (int i = _pickup_cards.Size(); i>0; i--)
                {
                    _playarea[row].Push(_pickup_cards.Pop());
                }
                rval = false;
            }
        }
        else
        {
            Card top = _playarea[row].Peek();
            Card card = _pickup_cards.Peek();
            if(top.Suit()%2 == (card.Suit()+1)%2 && top.Rank() == card.Rank() + 1)
            {
                int size_of_stack = _pickup_cards.Size();
                for (int i = 0; i<size_of_stack; i++)
                {
                    _playarea[row].Push(_pickup_cards.Pop());
                }
            }
        }
    }
   
    Notify();
    
    if(_pickup_cards.Size() > 0)
    {
        pickup_row = row;
        rval = true;
    }
    return rval;
}
