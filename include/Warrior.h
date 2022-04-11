#pragma once
#include "Location.h"
class Board;

class Warrior {
public:

	Warrior();
	void move(Board& board, int& c);// makes move if valid
	bool isValid(char type);// check if warrior can step on type tile in cell
	Location getLocation() const;
	void setLocation(size_t col, size_t row);
	void setHiddenChar(const char c);
	char getHiddenChar();
private:
	Location m_location = {0,0};//holds location of warrior
	Location m_wantedLocation;// cell that warrior goes next if valid
	char m_hidenChar;// saves char to replace in board
};