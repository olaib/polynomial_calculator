#include "Mage.h"
#include <conio.h>
#include "Board.h"
#include <iostream>
#include <thread>

//-----------------------------------------------------------------------------------------------------------------------------------------------
//constructor func of mage.
Mage::Mage() :m_wantedLocation({ 0,0 }), m_hidenChar(Empty_tile) {}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// this func gets the board and an integer. 
// makes a move if player is mage, integer is direction, and move is valid.
void Mage::move(Board& board, int& c)
{
	c = _getch();
	if (board.isDirecKey(c)) {
		//make step
		//update to next cell of current cell
		m_wantedLocation = board.getKeyDir(c, getLocation());
		if (isValid(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col))) {
			//store current cell
			board.setCellInBoard(m_hidenChar, getLocation());
			//restore
			setHiddenChar(board.getCellInBoard(m_wantedLocation.m_row, m_wantedLocation.m_col));
			//update location of Mage
			setLocation(m_wantedLocation.m_row, m_wantedLocation.m_col);
			//update Mage in board
			board.setCellInBoard(MAGE, m_wantedLocation);
			//if fire_tile : kill the fire
			if (m_hidenChar== Fire_tile)
				m_hidenChar = Empty_tile;


			if (m_hidenChar == Teleport_tile) {
				board.teleportMove(m_location, m_wantedLocation, MAGE, m_hidenChar);
			}
			}
			board.updateCounter();
			board.printBoard();
		}
	}


Location Mage::getLocation() const
{
	return m_location;
}


void Mage::setLocation(size_t col, size_t row)
{
	m_location = { col,row };
}

void Mage::setHiddenChar(char c)
{
	m_hidenChar = c;
}


bool Mage::isValid(char type) const
{
	switch (type)
	{
	case Tile_type::Wall_tile:
	case Tile_type::Gate_tile:
	case Tile_type::Orc_tile:
	case Characters::KING:
	case Characters::WARRIOR:
	case Characters::THEIF:
		return false;
	}


	return true;

}
