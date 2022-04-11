#include "Warrior.h"
#include <conio.h>
#include "Board.h"
#include <iostream>
//-----------------------------------------------------------------------------------------------------------------------------------------------
//constructor func of warrior
Warrior::Warrior() :m_wantedLocation({ 0,0 }), m_hidenChar(Empty_tile) {}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// this func gets the board and an integer. 
// makes a move if player is warrior, integer is direction, and move is valid.
void Warrior::move(Board& board, int& c)
{
	c = _getch();
	if (board.isDirecKey(c)) {// second call to getch, so that c can hold arrow key.
		//make a step
		//update to next cell of current cell
		m_wantedLocation = board.getKeyDir(c, getLocation());
		//if tile type is valid for warrior
		if (isValid(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col))) {
			
			// replace warrior with hidenchar
			board.setCellInBoard(m_hidenChar, getLocation());
			if (board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col) == Orc_tile) 
				m_hidenChar = Key_tile;

			//restore
			else
				setHiddenChar(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col));
			//update location of warrior
			setLocation(m_wantedLocation.m_row, m_wantedLocation.m_col);
			//update Warrior in board
			board.setCellInBoard(WARRIOR, m_wantedLocation);
			//moves warrior to teleport's partner cell
			if (m_hidenChar == Teleport_tile) {
				board.teleportMove(m_location, m_wantedLocation, WARRIOR, m_hidenChar);
			};
			board.updateCounter();
			board.printBoard();
		}
	}
}


Location Warrior::getLocation() const
{
	return m_location;
}


void Warrior::setLocation(size_t col, size_t row)
{
	m_location = { col,row };
}

void Warrior::setHiddenChar(const char c)
{
	m_hidenChar = c;

}

char Warrior::getHiddenChar()
{
	return m_hidenChar;
}


bool Warrior::isValid(char type)
{
	
	switch (type)
	{
	case Tile_type::Wall_tile:
	case Tile_type::Fire_tile: 
	case Tile_type::Throne_tile:
	case Tile_type::Gate_tile:
	case Characters::MAGE:
	case Characters::THEIF:
	case Characters::KING:
		return false;
	}
	return true;
}