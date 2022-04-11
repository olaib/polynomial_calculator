#include "King.h"
#include <conio.h>
#include "Board.h"
#include <iostream>
#include <thread>

//-----------------------------------------------------------------------------------------------------------------------------------------------
//constructor func of king
King::King() :m_location({0,0}) , m_wantedLocation ({ 0,0 }){}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// this func gets the board and an integer. 
//  makes a move if player is king, integer is direction, and move is valid.
void King::move(Board& board,int& c)
{
	c = _getch();// second call to getch, so that c can hold arrow key.
	if (board.isDirecKey(c)) { //if c is an arrow
		//make step
		//update to next cell of current cell
		m_wantedLocation = board.getKeyDir(c, getLocation());
		if (isValid(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col))) {
			//store current cell
			board.setCellInBoard(m_hidenChar, getLocation());
			//restore
			setHiddenChar(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col));
			//update location of king
			setLocation(m_wantedLocation.m_row, m_wantedLocation.m_col);
			//update king in board
			board.setCellInBoard(KING, m_wantedLocation);
			//moves king to teleport's partner cell
			if (m_hidenChar == Teleport_tile) {
				board.teleportMove(m_location,m_wantedLocation,KING,m_hidenChar);
			};
			board.updateCounter();
			board.printBoard();
		}
	}
}


Location King::getLocation() const
{
	return m_location;
}


void King::setLocation(size_t col,size_t row)
{
	m_location = { col,row };
}

void King::setHiddenChar(const char c)
{
	m_hidenChar = c;
}

char King::getHiddenChar()const
{
	return m_hidenChar;
}


bool King::isValid(const char type) const
{
	switch (type)
	{
	case Tile_type::Wall_tile:
	case Tile_type::Fire_tile:
	case Tile_type::Gate_tile:
	case Tile_type::Orc_tile:
	case Characters::MAGE:
	case Characters::WARRIOR:
	case Characters::THEIF:
		return false;
	}
	
	
	return true;
	
}
