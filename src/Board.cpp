#include "board.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

const auto ERROR = "cannot open file\n";

Board::Board(const std::string& fileName)
{
	openBoardFile(fileName);
	//fixing error
	std::vector<char> second(1, ' ');
	m_board.push_back(std::vector<char>());

}



//this func remove the row and cols of the board vector
void Board::removeBoardVec()
{
	m_board.clear();
	m_board.push_back(std::vector<char>());
}



//this func opens the input file ,its receives the name of the file and checks if opened successfully
void Board::openBoardFile(const std::string& fileName)
{
	m_file.open(fileName);
	if (!m_file) {
		std::cerr << ERROR;
		exit(EXIT_FAILURE);
	}
}


//this func return the input file by reference
std::ifstream& Board::getFile()
{
	return m_file;
}

//this func receive input file and the players class and then inserts the board into the m_board vector
//untill reading empty line (end of level) and Initializing the location of each player
void Board::readFile(std::ifstream& file, King& king, Theif& theif, Mage& mage, Warrior& warrior)
{
	std::string line;
	size_t j = 0;
	while (std::getline(file, line))// && line.size() != 0
	{
		if (isdigit(line[0]))
		{
			for (size_t i = 0; i<line.size(); i += 5) {
				size_t arr[2];
				arr[0] = line[i] -(size_t) 48;
				arr[1] = line[i +2] - (size_t) 48;
				
				Location loc = { arr[0],arr[1] };
				//std::cout << loc.m_col<<":" << loc.m_row<<std::endl;
				m_teleport.push_back(loc);
			}
			return;

		}

		for (size_t i = 0; i < line.size(); i++)
		{
			m_board.back().push_back(line[i]);
			if (line[i] == KING)
				king.setLocation(j, i);
			else if (line[i] == WARRIOR)
				warrior.setLocation(j, i);
			else if (line[i] == THEIF) {
				theif.setLocation(j, i);
			}
			else if (line[i] == MAGE)
				mage.setLocation(j, i);
		}
		m_board.push_back(std::vector<char>());
		j++;
	}
}

void Board::setIsTheifHasKey(const bool value)
{
	m_isTheifHasKey = value;
}

//A function that receives ascii value of direction key and location of current player
//this function returns the next location according to the direction
Location Board::getKeyDir(const size_t c, const Location& location) const
{
	switch (c)
	{
	case KB_Up :
		return { location.m_row - 1 , location.m_col };
	case KB_Down :
		return { location.m_row + 1,location.m_col};
	case KB_Left :
		return { location.m_row , location.m_col - 1 };
	case KB_Right: {
		return { location.m_row ,location.m_col + 1 };
	}
	}
	return location;
}

//this func checks if its direction key
bool Board::isDirecKey(const size_t c) const {
	switch (c) {
	case SpecialKeys::KB_Up: {return true; break; }
		
	case SpecialKeys::KB_Down: {return true; break; }
		
	case SpecialKeys::KB_Left: {return true; break; }
		
	case SpecialKeys::KB_Right: {return true; break; }
    default:
		return false;
	}
}

//this func receives char to change it into the given location in the board
void Board::setCellInBoard(const char value,const Location &location)
{
	m_board[location.m_row][location.m_col]=value;
}


//this func receives location and returns the char in the board
char Board::getCellInBoard(const size_t row,const size_t col) const
{
	return m_board[row][col];
}

//this func Increases the counter by one
void Board::updateCounter()
{
	m_counter++;
}

//this func prints the board of the game and the num of all players move and the current
//player and if the theif has key
void Board::printBoard() const
{
	std::system("cls");
	
	for (const auto& row : m_board)
	{
		for (const auto& col : row)
		{
			std::cout << col<<" ";
		}
		std::cout << "\n";
	}
	std::cout << "counter: " << m_counter << " player: " << getChar(getCurrIndex()) << "  Theif has key: " << ((m_isTheifHasKey) ? "yes" : "no") << std::endl;
}

//this func for teleport cell receives location and the sympole of the player and the hiddenChar
//and makes a step
void Board::teleportMove(Location& loc, Location& wantedLoc, const char player, char& hiddenChar)
{
	//store player symbole
	hiddenChar = player;
	//update to partner of current teleport
	loc = wantedLoc;
	setCellInBoard(hiddenChar, loc);
	hiddenChar = Teleport_tile;
	//find the location of partner of the teleport
	wantedLoc = getPartner(loc);
	//restore the current cell char
	setCellInBoard(hiddenChar, loc);
	hiddenChar = getCellInBoard(wantedLoc.m_row, wantedLoc.m_col);
	//update the location of the player
	loc = wantedLoc;
	//player in the other teleport
	setCellInBoard(player, wantedLoc);

}
//this func update the index of the players
void Board::updateCurrentPlayer()
{
	m_currIndex = (getCurrIndex() + 1) % 4;
}


//this func returns the index of the current player
size_t Board::getCurrIndex()const
{
	return m_currIndex;
}

//this func receives index and returns what the char of the cell in the board
char Board::getChar(const size_t index) const
{
	return m_players[index];
}


//this func looking for the partner of the relevant teleport and returns it
Location Board::getPartner(const Location &loc)const
{
	for (size_t i = 0;  i<m_teleport.size(); i++)
		if (loc.isSameLocation(m_teleport[i])) 
			return ((i % 2 == 0) ? m_teleport[i + 1] : m_teleport[i - 1]);
	return { 0,0 };
}

//clear teleport vector
void Board::clearTelepotVec()
{
	m_teleport.clear();
}