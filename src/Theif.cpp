#include "Theif.h"
#include <conio.h>
#include "Board.h"
#include <iostream>
#include <thread>


//-----------------------------------------------------------------------------------------------------------------------------------------------
//constructor func of theif. initializes to default values
Theif::Theif() :m_wantedLocation({ 0,0 }), m_hidenChar(Empty_tile) {}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// this func gets the board and an integer. 
// makes a move if player is theif, integer is direction, and move is valid.
void Theif::move(Board& board, int& c)
{
	c = _getch();// second call to getch, so that c can hold arrow key.
	if (board.isDirecKey(c)) {//if c is arrow
		//make step
		//update m_wantedLocation to be the location of next cell
		m_wantedLocation = board.getKeyDir(c, m_location);
		if (isValid(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col))) {
			//store current cell
			board.setCellInBoard(m_hidenChar, m_location);
			if (board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col) == Key_tile)
				m_hidenChar = Empty_tile;
			//restore prev cell
			else
				m_hidenChar = board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col);

			//update location of Theif
			m_location = m_wantedLocation;

			//update Theif in board
			board.setCellInBoard(THEIF, m_wantedLocation);
			// cases when hidenchar will hold empty char
			if (m_hidenChar == Key_tile
				|| m_hidenChar == Gate_tile) {
				m_hidenChar = Empty_tile;
			}

			else if (m_hidenChar == Teleport_tile) {
				board.teleportMove(m_location, m_wantedLocation, THEIF, m_hidenChar);
			}
			board.updateCounter();
			//theifHasKey = m_hasKey;
			// m_hasKey=true;
			board.setIsTheifHasKey(m_hasKey);
			board.printBoard();
		}
	}

}


void Theif::setLocation(size_t col, size_t row)
{
	m_location = { col,row };
}



bool Theif::isValid(char type)
{
	switch (type)
	{
	case Tile_type::Wall_tile:
	case Tile_type::Fire_tile:
	case Tile_type::Orc_tile:
	case Tile_type::Throne_tile:
	case Characters::MAGE:
	case Characters::WARRIOR:
	case Characters::KING:
		return false;

	case Tile_type::Gate_tile:{
		if (m_hasKey) { // using key to enter gate, turns haskey to false
			m_hasKey = false;
			return true;
		}
		else //if !has key
			return false;
		}
	case Tile_type::Key_tile:
		m_hasKey = true;
	}
	return true;

}

bool Theif::getHasKey()const
{
	return  m_hasKey;
}



void Theif::setHiddenChar(const char c)
{
	m_hidenChar = c;
}

Location Theif::getLocation() const
{
	return m_location;
}
