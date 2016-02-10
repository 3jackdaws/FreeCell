/*************************************************************
* Author:		Ian Murphy
* Filename:		GameBoard.cpp
* Date Created:	2/4/2016
* Modifications:	2/10/16 - Added documentation
*
**************************************************************/

#include "GameBoard.hpp"

/**********************************************************************
* Purpose: This is a default ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      sets up an gameboard object so that it isn't filled with garbage
*
************************************************************************/

GameBoard::GameBoard() : _freecells(4), _homecells(4), _playarea(8), _card_select(0)
{
    //this could be cleaner, but it's not ¯\_(ツ)_/¯
    for (int i = 0; i<8; i++)
    {
        _dbit[_DBIT_FREECELL][i] = true;
        
    }
    for (int i = 0; i<8; i++)
    {
        _dbit[_DBIT_HOMEROW][i] = true;
        
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
        _homecells[i].Resize(14);
		_homecells[i].Push(Card(NULLSUIT, NULLRANK));
		_homecell_filled[i] = false;
    }
    
    
}

/**********************************************************************
* Purpose: This is a copy ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      copies all dat
*
************************************************************************/
GameBoard::GameBoard(const GameBoard & cp) : _freecells(cp._freecells), _homecells(cp._homecells), _playarea(cp._playarea)
{
    
}

/**********************************************************************
* Purpose: This is a dtor.
*
* Precondition:
*     None
*
* Postcondition:
*      obliterates object
*
************************************************************************/
GameBoard::~GameBoard()
{
    
}

/**********************************************************************
* Purpose: This is a op = overload.
*
* Precondition:
*     None
*
* Postcondition:
*      copies basically
*
************************************************************************/
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

//Card GameBoard::RemoveFromPlayArea(int row)
//{
//    _dbit[_DBIT_PLAYAREA_FULL][row] = true;
//    _dbit[_DBIT_PLAYAREA][row] = true;
//    Card temp;
//    try {
//        temp = _playarea[row].Pop();
//    } catch (Exception e) {
//        
//    }
//    return temp;
//}
//Card GameBoard::RemoveFromFreeCells(int row)
//{
//    _dbit[_DBIT_FREECELL][row] = true;
//    Card remove = _freecells[row];
//    _freecells[row] = Card(NULLSUIT, NULLRANK);
//    return remove;
//}
//Card GameBoard::RemoveFromHomeCells(int row)
//{
//    _dbit[_DBIT_HOMEROW][row] = true;
//    return _homecells[row].Pop();
//}

//bool GameBoard::PutToPlayArea(int row, Card card)
//{
//    Card top = _playarea[row].Peek();
//    int topsuitmod2 = top.Suit()%2;
//    int cardsuitp1mod2 = (card.Suit()+1)%2;
//    int toprank = top.Rank();
//    int cardrankm1 = card.Rank()-1;
//    if(top.Suit()%2 == (card.Suit()+1)%2 && top.Rank() == card.Rank() + 1)
//    {
//        _dbit[_DBIT_PLAYAREA][row] = true;
//        _playarea[row].Push(card);
//        return true;
//    }
//    else
//        return false;
//        
//    
//}
//bool GameBoard::PutToFreeCells(int row, Card card)
//{
//    if(_freecells[row].Rank() == NULLRANK)
//    {
//        _freecells[row] = card;
//        _dbit[_DBIT_FREECELL][row] = true;
//        return true;
//    }
//    else
//        return false;
//        
//}
//void GameBoard::PutToHomeCells(int row, Card card)
//{
//    _dbit[_DBIT_HOMEROW][row] = true;
//    _homecells[row].Push(card);
//}

/**********************************************************************
* Purpose: Updates the displaybuffer in the display manager class by calling DM methods depending on cell states.
*
* Precondition:
*     There should be changes otherwise the Update method wont do anything
*
* Postcondition:
*      writes all changes to the display buffer
*
************************************************************************/
void GameBoard::Update(DisplayManager & dm)
{
    //FREE CELLS UPDATE HERE
    for (int row = 0; row<4; row++)		//for every free cell
    {
        if(_dbit[_DBIT_FREECELL][row])		//if there was a change to that cell
        {
            _dbit[_DBIT_FREECELL][row] = false;
            if(_card_select == row)		//if that card is "selected"
                DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN+(row*CARD_WIDTH+row), _freecells[row]);		//highlight it
            else
                DrawCard(dm, TOP_MARGIN, LEFT_MARGIN+(row*CARD_WIDTH+row), _freecells[row]);
			if (_pickup_cards.Size() > 0 && _card_select == row)		//might be redundant
			{
				DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN + (row*CARD_WIDTH + row), _pickup_cards.Peek());
			}
        }
        
    }
    //HOME CELLS UPDATE HERE
    for (int row = 0; row<4; row++)		//foreach cell
    {
        if(_dbit[_DBIT_HOMEROW][row])		//if changed
        {
            _dbit[_DBIT_HOMEROW][row] = false;
			SetWinCond(row);				//check if the player has won
            if(_card_select == row+4)
                DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN+50+(row*CARD_WIDTH+row), _homecells[row].Peek());
            else
                DrawCard(dm, TOP_MARGIN, LEFT_MARGIN+50+(row*CARD_WIDTH+row), _homecells[row].Peek());
			if (_pickup_cards.Size() > 0 && _card_select == row + 4)
			{
				DrawSelectedCard(dm, TOP_MARGIN, LEFT_MARGIN + 50+(row*CARD_WIDTH + row), _pickup_cards.Peek());
			}
        }
        
    }
    //UPDATE PLAYAREA
    for (int row = 0; row<8; row++)			//for every playcell
    {
        if(_dbit[_DBIT_PLAYAREA][row])          //if a card has been added
        {
            _dbit[_DBIT_PLAYAREA][row] = false; //set the flag back
            int stack_size = _playarea[row].Size();
            int number_to_update = 0;
            
            if(_dbit[_DBIT_PLAYAREA_FULL][row])		//if the whole stack needs to be redrawn, ex. top card is removed
            {
                _dbit[_DBIT_PLAYAREA_FULL][row] = false;
                number_to_update = _playarea[row].Size();		//see how many cards need to be updated
                dm.Rect(TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT, LEFT_MARGIN+(row*CARD_WIDTH+row), CARD_WIDTH, BUFFER_HEIGHT-TOP_MARGIN-ROW_MARGIN, L" ");	//obliterate that area
            }
            else
            {
                number_to_update = 1;
            }
            StackA<Card> tempStack(_playarea[row].Size());
            for (int i = 0; i<number_to_update; i++)	//pop all the updated cards off the stack
            {
                tempStack.Push(_playarea[row].Pop());
            }
            int i = 0;
            for (i = stack_size-number_to_update; i<stack_size; i++)	//display all the popped cards
            {
                Card temp = tempStack.Pop();
                if(_card_select - 8  == row+i*8 && _pickup_cards.Size() == 0)
                    DrawSelectedCard(dm, TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT+2*i, LEFT_MARGIN+(row*CARD_WIDTH+row), temp);
                else
                    DrawCard(dm, TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT+2*i, LEFT_MARGIN+(row*CARD_WIDTH+row), temp);
                _playarea[row].Push(temp);
            }
			if (_playarea[row].Size() == 0)		//if there isnt anything there, draw a NULL card
			{
				if (_card_select > 7 && _card_select % 8 == row)
				{
					DrawSelectedCard(dm, TOP_MARGIN + ROW_MARGIN + CARD_HEIGHT, LEFT_MARGIN + (row*CARD_WIDTH + row), Card(NULLSUIT, NULLRANK));
				}
				else
				{
					DrawCard(dm, TOP_MARGIN + ROW_MARGIN + CARD_HEIGHT, LEFT_MARGIN + (row*CARD_WIDTH + row), Card(NULLSUIT, NULLRANK));
				}
			}
            if(_pickup_cards.Size()>0 && _card_select>7 &&_card_select%8 == row)		//if the card select is RIGHT THERE and there is a held stack
            {
                StackA<Card> temps(_pickup_cards.Size());
                int pd_size = _pickup_cards.Size();
                for (int s = 0; s<pd_size; s++)		//display all the held cards on that stack
                {
                    Card temp = _pickup_cards.Pop();
                    DrawSelectedCard(dm, TOP_MARGIN+ROW_MARGIN+CARD_HEIGHT+2*i+1, LEFT_MARGIN+(row*CARD_WIDTH+row), temp);
                    temps.Push(temp);
                    i++;
                }
                for (int s = 0; s<pd_size; s++)
                {
                    _pickup_cards.Push(temps.Pop());	//give them back
                }
            }
			
        }
    }
}

/**********************************************************************
* Purpose: This will draw the static elemetns of the board.
*
* Precondition:
*     dm must be instantiated
*
* Postcondition:
*      draws the static elements
*
************************************************************************/
void GameBoard::DrawStatics(DisplayManager & dm)
{
    dm.Line( TOP_MARGIN+CARD_HEIGHT, LEFT_MARGIN, CARD_WIDTH*4+3, L"-");
    dm.Line( TOP_MARGIN+CARD_HEIGHT, LEFT_MARGIN+50, CARD_WIDTH*4+3, L"-");
    dm.Line( TOP_MARGIN+CARD_HEIGHT+ROW_MARGIN-1, LEFT_MARGIN, CARD_WIDTH*8+13, L"-");
    char * free_cell_text = "FREE CELLS";
    char * home_row_text = "HOME CELLS";
    char * play_area_text = "PLAY AREA";
    int start = ((CARD_WIDTH*4+3)-10)/2;
    dm.Text(TOP_MARGIN+CARD_HEIGHT, start+LEFT_MARGIN, 12, free_cell_text);
    dm.Text(TOP_MARGIN+CARD_HEIGHT, start+LEFT_MARGIN+50, 12, home_row_text);
    dm.Text(TOP_MARGIN+CARD_HEIGHT+ROW_MARGIN-1, 45, 12, play_area_text);
	dm.Text(0, 0, 100, "Use W/A/S/D to move, SPACE to select a card or stack to pickup, and SPACE to place a card or stack.");
	dm.Text(1, 0, 100, "Q will quit the game.  Use F to force place a card on any stack.  THIS WILL BREAK THE GAME.");
}

/**********************************************************************
* Purpose: Draws a predefined card shape to the board at row, col.
*
* Precondition:
*     card has to be a card object
*
* Postcondition:
*      Draws that card, mane, if it has a value it will even put text on it
*
************************************************************************/
void GameBoard::DrawCard(DisplayManager & dm, int row, int col, Card & card)
{
	dm.ColorBackground(row, col, CARD_WIDTH, CARD_HEIGHT, 0x0007);		//get right color
    dm.Rect(row, col, CARD_WIDTH, CARD_HEIGHT, L" ");					//clear the area
	
    dm.Line(row, col+1, CARD_WIDTH-2, CARD_TOP);        //top edge
    dm.Line(row+CARD_HEIGHT-1, col+1, CARD_WIDTH-2, CARD_TOP);    //bottom edge
    dm.VertLine(row+1, col, CARD_HEIGHT-2, CARD_SIDES);				//left and right edge
    dm.VertLine(row+1, col+CARD_WIDTH-1, CARD_HEIGHT-2, CARD_SIDES);
    dm.Write(row, col, CARD_TOPL);
    dm.Write(row, col+CARD_WIDTH-1, CARD_TOPR);				//corners
    dm.Write(row+CARD_HEIGHT-1, col, CARD_BOTL);
    dm.Write(row+CARD_HEIGHT-1, col+CARD_WIDTH-1, CARD_BOTR);
	
    if(card.Rank() != NULLRANK)				//if a real card
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
		DrawSuit(dm, row+1, col+7, card.Suit());
        //abbrev[5] = card.SuitText()[0];
		int color = 0x0007;
		if (card.Suit() % 2 == 0)
			color = FOREGROUND_RED;
		dm.ColorBackground(row + 1, col + 2, CARD_WIDTH - 4, 1, color);
        dm.Text(row+1, col+2, CARD_WIDTH, abbrev);
		
        dm.Text(row+TEXT_MARGIN, col+1, CARD_WIDTH, card.RankText());
        dm.Text(row+TEXT_MARGIN+1, col+1, CARD_WIDTH, "of");
        dm.Text(row+TEXT_MARGIN+2, col+1, CARD_WIDTH, card.SuitText());
    }
	
}

/**********************************************************************
* Purpose: Forces a card to the playarea.
*
* Precondition:
*     None
*
* Postcondition:
*      oh look, a jack of hearts is now on top of a two
*
************************************************************************/
void GameBoard::ForceToPlayArea(int row, Card card)
{
    _dbit[_DBIT_PLAYAREA][row] = true;
    _playarea[row].Push(card);
}

/**********************************************************************
* Purpose: Draws a card with a pretty border.
*
* Precondition:
*     None
*
* Postcondition:
*      card now has a green border
*
************************************************************************/
void GameBoard::DrawSelectedCard(DisplayManager & dm, int row, int col, Card & card)
{
	DrawCard(dm, row, col, card);
	dm.ColorBackground(row, col, CARD_WIDTH, 1, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//top
	dm.ColorBackground(row, col, 1, CARD_HEIGHT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//left
	dm.ColorBackground(row+CARD_HEIGHT-1, col, CARD_WIDTH, 1, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	dm.ColorBackground(row, col+CARD_WIDTH-1, 1, CARD_HEIGHT-1, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	//dm.ColorBackground(row+1, col+1, CARD_WIDTH-2, CARD_HEIGHT-2, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	
}

/**********************************************************************
* Purpose: Move card select to Card above.
*
* Precondition:
*     None
*
* Postcondition:
*      card select go up
*
************************************************************************/
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

/**********************************************************************
* Purpose: Move card select to Card below.
*
* Precondition:
*     None
*
* Postcondition:
*      card select go down
*
************************************************************************/
void GameBoard::SelDown()
{
    int t1 = _playarea[_card_select%8].Size();
    int t2 = _playarea[_card_select%8].Size()*8;
    int t3 = _card_select+8;
    int row = _card_select%8;
	/*if((_card_select<8 && _playarea[_card_select%8].Size()>0) || _playarea[row].Size()*8+row>=_card_select+8)*/
	if (_card_select<8  || _playarea[row].Size() * 8 + row >= _card_select + 8)
    {
        Notify();
        _card_select+=8;
        Notify();
    }
}

/**********************************************************************
* Purpose: Move card select to Card left.
*
* Precondition:
*     None
*
* Postcondition:
*      card select go left
*
************************************************************************/
void GameBoard::SelLeft()
{
    int row = _card_select%8;
    if(row > 0)
    {
        Notify();
        _card_select--;
        Notify();
		if (_card_select > 7)
		{
			if (_playarea[row - 1].Size() * 8 + row - 1 < _card_select)
				_card_select = _playarea[row - 1].Size() * 8 + row - 1;
			if (_playarea[row - 1].Size() == 0)
				_card_select = row + 7;
		}
    }
    
}

/**********************************************************************
* Purpose: Move card select to Card right.
*
* Precondition:
*     None
*
* Postcondition:
*      card select go right
*
************************************************************************/
void GameBoard::SelRight()
{
    int row = _card_select%8;
    if(row < 7)
    {
        Notify();
        _card_select++;
        Notify();
		if (_card_select > 7)
		{
			if (_playarea[row + 1].Size() * 8 + row + 1 < _card_select - 1)
				_card_select = _playarea[row + 1].Size() * 8 + row + 1;
			if (_playarea[row + 1].Size() == 0)
				_card_select = row + 9;
		}
        
    }
    
}

/**********************************************************************
* Purpose: Tell the update method that it should redraw the stack at the location.
*
* Precondition:
*     None
*
* Postcondition:
*      the dirty bit for whatever is updated
*
************************************************************************/
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

/**********************************************************************
* Purpose: Figure out from dozens of different states if a card or stack can be picked up or placed back down.
*
* Precondition:
*     None
*
* Postcondition:
*		Who knows.  Card is pciked up or placed down, or nothing or a stack is picked up or placed back down or nothing.  
		This method won't warn you why you cannot do something because you're an adult
*
************************************************************************/
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
				pickup_row = -1;
                _dbit[_DBIT_FREECELL][row] = true;
            }
            
        }
        else if (_pickup_cards.Size() == 0 && _freecells[row].Rank() != NULLRANK)
        {
            _pickup_cards.Resize(1);
            _pickup_cards.Push(_freecells[row]);
            _freecells[row] = Card(NULLSUIT, NULLRANK);
            _dbit[_DBIT_FREECELL][row] = true;
        }
        
    }
    else if(_card_select < 8)
    {
		row %= 4;
		if (_pickup_cards.Size() == 1)
		{
			if (_homecells[row].Peek().Rank() == NULLRANK && _pickup_cards.Peek().Rank() == ACE)
			{
				_homecells[row].Push(_pickup_cards.Pop());
			}
			else if (_homecells[row].Peek().Suit() == _pickup_cards.Peek().Suit() && _homecells[row].Peek().Rank() == _pickup_cards.Peek().Rank() - 1)
			{
				_homecells[row].Push(_pickup_cards.Pop());
			}
		}
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
				{
					_error_=true;
					_playarea[row].Push(temp);
				}
                    
            }
            if(_error_)
            {
                for (int i = _pickup_cards.Size(); i>0; i--)
                {
                    _playarea[row].Push(_pickup_cards.Pop());
                }
                rval = false;
            }
			else
				pickup_row = row;
        }
        else
        {
			//CALC NUMBER OF MOVES
			int num_moves = 1, num_open_playarea = 0;
			for (int i = 0; i < 4; i++)
			{
				if (_freecells[i].Suit() == NULLSUIT)
					num_moves++;
			}
			for (int i = 0; i < 8; i++)
			{
				if (_playarea[i].Size() == 0)
					num_open_playarea++;
			}
			num_moves = num_moves * pow(2, num_open_playarea);
			//What is going on here?  I've long since lost track.
			//Basically, this is when the user is allowed to put a card back down in the playcells
			//This is almost my favorite line of code in this program
			if (row == pickup_row || (num_moves >= _pickup_cards.Size() && ( _playarea[row].Size() == 0 || (Card(_playarea[row].Peek()).Suit() % 2 == (_pickup_cards.Peek().Suit() + 1) % 2 && Card(_playarea[row].Peek()).Rank() == _pickup_cards.Peek().Rank() + 1))))
			{																								//wow, a use for that Card copy ctor
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
        rval = true;
    }
    return rval;
}

/**********************************************************************
* Purpose: Ram that card onto that stack.
*
* Precondition:
*     None
*
* Postcondition:
*      stack now contains card
*
************************************************************************/
void GameBoard::DebugPlaceCard()
{
	int row = _card_select % 8;
	if (_pickup_cards.Size() == 0)
	{
		_pickup_cards.Resize(1);
		_pickup_cards.Push(_playarea[row].Pop());
	}
	else
	{
		_playarea[row].Push(_pickup_cards.Pop());
	}
}

/**********************************************************************
* Purpose: Sets the homecell stack full bool if the homecell is full.
*
* Precondition:
*     None
*
* Postcondition:
*      bool is changed
*
************************************************************************/
void GameBoard::SetWinCond(int row)
{
	if (_homecells[row].Size() == 14)	//full suit and empty card
	{
		_homecell_filled[row] = true;
	}
}

/**********************************************************************
* Purpose: Displays a prompt asking the user if they want to quit to menu
*
* Precondition:
*     None
*
* Postcondition:
*      can either cause the game to end, or not
*
************************************************************************/
bool GameBoard::QuitGamePrompt(DisplayManager & dm)
{
	dm.Rect(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 20, 10, L" ");
	dm.Line(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 20, CARD_TOP);
	dm.Line(BUFFER_HEIGHT + 0 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 20, CARD_TOP);
	dm.VertLine(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 10, CARD_SIDES);
	dm.VertLine(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 10 - BUFFER_WIDTH / 2, 10, CARD_SIDES);
	
	dm.Write(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, CARD_TOPL);
	dm.Write(BUFFER_HEIGHT + 0 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, CARD_BOTL);
	dm.Write(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 10 - BUFFER_WIDTH / 2, CARD_TOPR);
	dm.Write(BUFFER_HEIGHT + 0 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 10 - BUFFER_WIDTH / 2, CARD_BOTR);
	dm.Text(BUFFER_HEIGHT - 7 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 5 - BUFFER_WIDTH / 2, 12, "Quit Game?");
	dm.Text(BUFFER_HEIGHT - 5 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 5 - BUFFER_WIDTH / 2, 12, "Yes    No");
	int choice = 0;
	char d = '\0';
	while (d != 1)
	{
		dm.ColorBackground(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 22, 20, 0x0007);
		if (choice == 1)
		{
			dm.ColorBackground(BUFFER_HEIGHT - 5 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 5 - BUFFER_WIDTH / 2, 3, 1, BACKGROUND_BLUE | 0x0007);
		}
		else
		{
			dm.ColorBackground(BUFFER_HEIGHT - 5 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 2 - BUFFER_WIDTH / 2, 2, 1, BACKGROUND_BLUE | 0x0007);
		}
		dm.Display();
		d = getch();
		switch (d)
		{
		case 'a':
			++choice %= 2;	//this might be my favorite line of code in this project
			break;
		case 'd':
			++choice %= 2;
			break;
		case ' ':
			d = 1;
		default:;
		}
	}
	if (choice == 1)
		return true;
	RefreshAll();
	dm.Rect(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 22, 22, L" ");
	return false;
}

/**********************************************************************
* Purpose: Do win?
*
* Precondition:
*     None
*
* Postcondition:
*      maybe end game, maybe no
*
************************************************************************/
bool GameBoard::CheckWinCondition()
{
	if (_homecell_filled[0] && 
		_homecell_filled[1] && 
		_homecell_filled[2] && 
		_homecell_filled[3])
	{
		return true;
	}
	return false;

}

/**********************************************************************
* Purpose: Tells the entire playarea to refresh
*
* Precondition:
*     None
*
* Postcondition:
*      do it
*
************************************************************************/
void GameBoard::RefreshAll()
{
	for (int i = 0; i < 8; i++)
	{
		_dbit[_DBIT_PLAYAREA_FULL][i] = true;
		_dbit[_DBIT_PLAYAREA][i] = true;
	}
}

/**********************************************************************
* Purpose: Draws the specific suit symbol.
*
* Precondition:
*     None
*
* Postcondition:
*      card select go up
*
************************************************************************/
void GameBoard::DrawSuit(DisplayManager & dm, int row, int col, Suit suit)
{


	switch (suit)
	{
	case HEARTS:
		dm.Write(row, col, L"\u2665");
		break;
	case DIAMONDS:
		dm.Write(row, col, L"\u2666");
		break;
	case CLUBS:
		dm.Write(row, col, L"\u2663");
		break;
	case SPADES:
		dm.Write(row, col, L"\u2660");
		break;
	}

}

/**********************************************************************
* Purpose: Congratulations!
*
* Precondition:
*     None
*
* Postcondition:
*      Display buffer is permanently changed
*
************************************************************************/
void GameBoard::WinSplash(DisplayManager & dm)
{
	dm.Rect(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 20, 10, L" ");
	dm.Line(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 20, CARD_TOP);
	dm.Line(BUFFER_HEIGHT + 0 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 20, CARD_TOP);
	dm.VertLine(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 10, CARD_SIDES);
	dm.VertLine(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 10 - BUFFER_WIDTH / 2, 10, CARD_SIDES);

	dm.Write(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, CARD_TOPL);
	dm.Write(BUFFER_HEIGHT + 0 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, CARD_BOTL);
	dm.Write(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 10 - BUFFER_WIDTH / 2, CARD_TOPR);
	dm.Write(BUFFER_HEIGHT + 0 - BUFFER_HEIGHT / 2, BUFFER_WIDTH + 10 - BUFFER_WIDTH / 2, CARD_BOTR);
	dm.Text(BUFFER_HEIGHT - 7 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 8 - BUFFER_WIDTH / 2, 16, "Congratulations!");
	dm.ColorBackground(BUFFER_HEIGHT - 10 - BUFFER_HEIGHT / 2, BUFFER_WIDTH - 10 - BUFFER_WIDTH / 2, 21, 10, 0x000F);
}