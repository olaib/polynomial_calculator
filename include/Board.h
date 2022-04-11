#pragma once
#include <string>
#include <vector>
#include <array>
#include "Warrior.h"
#include "Mage.h"
#include "King.h"
#include "Theif.h"
#include <fstream>
#include "Location.h"
//size of players
const auto PLAYERS_NUMBER = 4;

enum Characters : char {
	KING = 'K',
	WARRIOR = 'W',
	MAGE = 'M',
	THEIF = 'T',

};


enum Tile_type : char {
	Empty_tile = ' ',
	Wall_tile = '=',
	Gate_tile = '#',
	Fire_tile = '*',
	Orc_tile = '!',
	Key_tile = 'F',
	Teleport_tile = 'X',
	Throne_tile = '@',
};


enum Keys : int
{
	KB_Escape = 27,
	SpecialKey = 224,
};

enum SpecialKeys : int
{
	KB_Up = 72,
	KB_Down = 80,
	KB_Left = 75,
	KB_Right = 77,
	KB_P = 112,
};



class Board {
public:
	Board(const std::string& fileName);

	void openBoardFile(const std::string& fileName);
	std::ifstream& getFile();
	void readFile(std::ifstream& file, King& king, Theif& theif, Mage& mage, Warrior& warrior);
	void setIsTheifHasKey(const bool);
	Location getKeyDir(const size_t c, const Location& location) const;
	bool isDirecKey(const size_t c) const;
	void setCellInBoard(char value, const Location& location);
	char getCellInBoard(size_t row, size_t col) const;
	void updateCounter();
	void printBoard()const;
	void teleportMove(Location& loc, Location& wantedLoc, const char player, char& hiddenChar);
	void updateCurrentPlayer();
	size_t getCurrIndex()const;
	char getChar(const size_t index)const;
	void setTeleportCell(Location loc );
	Location getPartner(const Location& loc)const;
	//clear vector of telepots
	void clearTelepotVec();
	void removeBoardVec();

private:
	//vector to store the board of each level
	std::vector<std::vector<char>> m_board;
	//vector for players
	std::array<char, PLAYERS_NUMBER> m_players = { KING,WARRIOR,MAGE,THEIF };
	//locations of teleport of current level
	std::vector<Location> m_teleport;
	//current index of players vector
	size_t m_currIndex = 0;
	//counter for players move
	size_t m_counter=0;
	//for has key
	//input file
	std::ifstream m_file;
	bool m_isTheifHasKey = false;
};